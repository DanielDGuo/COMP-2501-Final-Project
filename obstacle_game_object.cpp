#include "obstacle_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace game {

	ObstacleObject::ObstacleObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, const glm::vec3& start, const glm::vec3& end, float length, float rot)
		: GameObject(position, geom, shader, texture, 3) 
	{
		scalex = length;
		scaley = 0.1;
		rotAngle = rot;
		startPos = start;
		endPos = end;
		timeSinceCreation = 0.0f;
	}

	void ObstacleObject::Update(double delta_time) {
		timeSinceCreation += delta_time;

		if (timeSinceCreation >= 10)
		{
			setDelStatus(true);
		}
	}
} // namespace game
