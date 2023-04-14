#include "triple_shot.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	TripleShot::TripleShot(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy, bool activated)
		: BulletGameObject(position, geom, shader, texture, direction, dam, enemy)
	{
		this->activated = activated;
	}

	void TripleShot::Activate(std::vector<BulletGameObject*>* bullets)
	{
		if (!activated)
		{
			//Set the shot to activated
			activated = true;

			//Reduce the damage of the bullet
			damage /= 3;

			//Get the direction of the bullet
			float direction = rotAngle + (3.1415 / 2);

			//Create two new bullets
			bullets->push_back(new TripleShot(position_, geometry_, shader_, texture_, direction - (3.1415 / 8), damage, enemyBullet, true));
			bullets->push_back(new TripleShot(position_, geometry_, shader_, texture_, direction + (3.1415 / 8), damage, enemyBullet, true));
		}
	}
}