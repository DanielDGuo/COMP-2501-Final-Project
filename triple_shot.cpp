#include "triple_shot.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	TripleShot::TripleShot(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy)
		: BulletGameObject(position, geom, shader, texture, direction, dam, enemy)
	{

	}

	void TripleShot::Activate(std::vector<BulletGameObject*>* bullets)
	{
		//Reduce the damage of the bullet
		damage /= 3;

		//Get the direction of the bullet
		float direction = rotAngle + (3.1415 / 2);

		//Create two new bullets
		bullets->push_back(new TripleShot(position_, geometry_, shader_, texture_, direction - (3.1415 / 8), damage, enemyBullet));
		bullets->push_back(new TripleShot(position_, geometry_, shader_, texture_, direction + (3.1415 / 8), damage, enemyBullet));
	}
}