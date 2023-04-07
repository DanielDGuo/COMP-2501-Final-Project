#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "game_object.h"

namespace game {

	GameObject::GameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, int hp)
	{

		// Initialize all attributes
		position_ = position;
		scalex = 1.0;
		scaley = 1.0;
		velocity_ = glm::vec3(0.0f, 0.0f, 0.0f); // Starts out stationary
		rotAngle = 0;
		geometry_ = geom;
		shader_ = shader;
		texture_ = texture;
		delObj = false;
		health = hp;
		timeOfDeath = NULL;
	}

	GameObject::GameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
	{

		// Initialize all attributes
		position_ = position;
		scalex = 1.0;
		scaley = 1.0;
		velocity_ = glm::vec3(0.0f, 0.0f, 0.0f); // Starts out stationary
		rotAngle = 0;
		geometry_ = geom;
		shader_ = shader;
		texture_ = texture;
		delObj = false;
		health = -1;
		timeOfDeath = NULL;
	}


	void GameObject::Update(double delta_time) {

		// Update object position with Euler integration
		position_ += velocity_ * ((float)delta_time);
		if (health <= 0) {
			//instead of requestion deletion, set deceased in the frag shader to true to greyscale, and log the time of death
			shader_->SetUniform1i("deceased", 1);
			if(timeOfDeath == NULL){
				timeOfDeath = glfwGetTime();
			}
		}
		else {
			//revert the greyscaling if needed
			shader_->SetUniform1i("deceased", 0);
		}

		//delete after 5 seconds
		if (timeOfDeath != NULL && timeOfDeath + 5 <= glfwGetTime()) {
			delObj = true;
		}
	}


	void GameObject::Render(glm::mat4 view_matrix, double current_time) {

		// Set up the shader
		shader_->Enable();

		// Set up the view matrix
		shader_->SetUniformMat4("view_matrix", view_matrix);

		// Setup the scaling matrix for the shader
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scalex, scaley, 1.0));

		// Set up the rotation matrix for the shader
		glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), rotAngle, glm::vec3(0, 0, 1));

		// Set up the translation matrix for the shader
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

		// Setup the transformation matrix for the shader
		glm::mat4 transformation_matrix = translation_matrix * rotation_matrix * scaling_matrix;

		// Set the transformation matrix in the shader
		shader_->SetUniformMat4("transformation_matrix", transformation_matrix);

		// Set up the geometry
		geometry_->SetGeometry(shader_->GetShaderProgram());

		// Bind the entity's texture
		glBindTexture(GL_TEXTURE_2D, texture_);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, geometry_->GetSize(), GL_UNSIGNED_INT, 0);
	}

} // namespace game
