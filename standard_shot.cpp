#include "standard_shot.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	StandardShot::StandardShot(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy)
		: BulletGameObject(position, geom, shader, texture, direction, dam, enemy)
	{

	}

	void StandardShot::Activate()
	{
		//Double the damage of the shot
		damage *= 2;
	}
}