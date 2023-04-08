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

	
} // namespace game
