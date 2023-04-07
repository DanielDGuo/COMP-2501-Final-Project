#include "obstacle_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace game {

	/*
		TempameObject inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	ObstacleObject::ObstacleObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture, 1) {
	}

	void ObstacleObject::Update(double delta_time) {
		
	}
} // namespace game
