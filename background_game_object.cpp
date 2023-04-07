#include "background_game_object.h"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>

namespace game {

	/*
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	Background::Background(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture, 1) {
	}

	void Background::Update(double delta_time) {
	}

	void Background::Render(glm::mat4 view_matrix, double current_time) {

		// Set up the shader
		shader_->Enable();

		// Set up the view matrix
		shader_->SetUniformMat4("view_matrix", view_matrix);

		// Setup the scaling matrix for the shader
		glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scalex, scaley, 1.0));

		// Set up the translation matrix for the shader
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

		// Setup the transformation matrix for the shader
		glm::mat4 transformation_matrix = translation_matrix * scaling_matrix;

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
