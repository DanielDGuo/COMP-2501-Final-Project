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
		rotAngle = direction - 3.1415/2;
		velocity_ = glm::vec3(cos(direction), sin(direction), 0.0f);
		velocity_ *= 8;
		damage = dam;
		enemyBullet = enemy;
		scalex = 0.5;
		scaley = 0.5;
		timeSinceLastRicochet = 1.0;
	}

	void BulletGameObject::Update(double delta_time) {
		GameObject::Update(delta_time);

		timeSinceLastRicochet += delta_time;

		if (glfwGetTime() >= spawnTime + 3) {
			delObj = true;
		}
	}

	void BulletGameObject::Ricochet(GameObject* obj)
	{
		std::cout << timeSinceLastRicochet << std::endl;
		if (timeSinceLastRicochet > 0.5)
		{
			timeSinceLastRicochet = 0;
			glm::vec3 objPos = obj->GetPosition();
			float objAngle = obj->getRotation();
			float normalAngle = objAngle - 3.1415/2;

			// Set up vectors for the bullet, the object, and its normal
			double length = sqrt(pow(velocity_.x, 2) + pow(velocity_.y, 2));
			velocity_ /= length;
			std::cout << "Bul Vec: (" << velocity_.x << ", " << velocity_.y << ")" << std::endl;
			std::cout << "Length (vel): " << length << std::endl;

			glm::vec3 objVector;
			objVector.x = sin(objAngle);
			objVector.y = cos(objAngle);
			objVector.z = 0.0f;
			std::cout << "Obj Vec: (" << objVector.x << ", " << objVector.y << ")" << std::endl;

			glm::vec3 normalVector;
			normalVector.x = sin(normalAngle);
			normalVector.y = cos(normalAngle);
			normalVector.z = 0.0f;
			std::cout << "Nor Vec: (" << normalVector.x << ", " << normalVector.y << ")" << std::endl;

			//Calculate the new angle for the bullet
			float dot = glm::dot(velocity_, normalVector);
			float angleDif = acos(dot);

			//Determine which side of the normal the bullet is on and update the bullet's angle accordingly
			dot = glm::dot(velocity_, objVector);
			float direction = 0.0f;
			if (dot > 0)
			{
				direction = normalAngle + angleDif;
			}
			else
			{
				direction = normalAngle - angleDif;
			}

			//Update the bullet's velocity using the new angle
			velocity_ = glm::vec3(cos(direction), sin(direction), 0.0f);
			velocity_ *= length;
			rotAngle = direction - 3.1415/2;

			//Activate the bullet's effect
			if (!ricocheted)
			{
				ricocheted = true;
				Activate();
			}
		}
	}

	void BulletGameObject::Activate()
	{

	}

} // namespace game
