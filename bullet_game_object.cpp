#include "bullet_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace game {

	/*
		EnemyGameObject inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	BulletGameObject::BulletGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy)
		: GameObject(position, geom, shader, texture, 1) {
		spawnTime = glfwGetTime();
		rotAngle = direction - 3.1415 / 2;
		velocity_ = glm::vec3(cos(direction), sin(direction), 0.0f);
		velocity_ *= 8;
		damage = dam;
		enemyBullet = enemy;
		scalex = 0.5;
		scaley = 0.5;
		timeSinceLastRicochet = 1.0;
		activated = false;
	}

	void BulletGameObject::Update(double delta_time) {
		GameObject::Update(delta_time);

		timeSinceLastRicochet += delta_time;

		if (glfwGetTime() >= spawnTime + 3) {
			delObj = true;
		}
	}

	void BulletGameObject::Ricochet(ObstacleObject* obj)
	{
		if (timeSinceLastRicochet > 0.5)
		{
			timeSinceLastRicochet = 0;
			
			//turns the wall into a vector pointing in the direction of the wall
			glm::vec3 wall = glm::vec3(glm::cos(obj->getRotation()) , glm::sin(obj->getRotation()), 0);

			//gets the dot product of the bullet vector and the wall; i.e how much of the bullet's velocity
			//can be represented by the wall
			glm::vec3 wallSegment = wall * glm::dot(velocity_, wall);

			//subtracts the previously found dot product, producing a vector that is normal to the wall. 
			//It's then flipped, and the wall segment is added back in
			velocity_ = -(velocity_ - wallSegment) + wallSegment;

			//fixes the rotation
			rotAngle = glm::atan(velocity_.y, velocity_.x) - 3.1415/2;
		}
	}

	void BulletGameObject::Activate(std::vector<BulletGameObject*>* bullets)
	{

	}

} // namespace game
