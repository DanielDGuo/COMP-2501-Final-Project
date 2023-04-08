#include "triple_shot.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	TripleShot::TripleShot(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy)
		: BulletGameObject(position, geom, shader, texture, direction, dam, enemy)
	{

	}

	void TripleShot::Activate()
	{
		//Create three new shots with 1/3 damage
	}
}