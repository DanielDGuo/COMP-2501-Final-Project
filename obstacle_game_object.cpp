#include "obstacle_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace game {

	ObstacleObject::ObstacleObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float length, float rot)
		: GameObject(position, geom, shader, texture, 3) 
	{
		scalex = length;
		scaley = 0.1;
		rotAngle = rot;
	}

	void ObstacleObject::Update(double delta_time) {
		
	}
} // namespace game
