#include "temp_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace game {

	/*
		TempameObject inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	TempGameObject::TempGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, int lifespan)
		: GameObject(position, geom, shader, texture, -1) {
		this->lifespan = lifespan;
		spawnTime = glfwGetTime();
		playerExplosion = false;
	}

	void TempGameObject::Update(double delta_time) {
		//requests deletion after lifespan amount of seconds
		GameObject::Update(delta_time);
		if ((int)glfwGetTime() >= spawnTime + lifespan) {
			delObj = true;
		}
		//disable the greyscaling
		shader_->SetUniform1i("deceased", 0);
	}
} // namespace game
