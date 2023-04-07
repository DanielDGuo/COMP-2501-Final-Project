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
	}

	void BulletGameObject::Update(double delta_time) {
		GameObject::Update(delta_time);

		if (glfwGetTime() >= spawnTime + 3) {
			delObj = true;
		}
	}

	void BulletGameObject::Ricochet(GameObject* obj)
	{
		ricocheted = true;
		glm::vec3 objPos = obj->GetPosition();
		float objAngle = obj->getRotation();
		float normalAngle = objAngle + 3.1415/2;

		// Set up vectors for the bullet, the object, and its normal
		glm::vec3 bulletVector = position_ - objPos;
		double length = sqrt(pow(bulletVector.x, 2) + pow(bulletVector.y, 2));
		bulletVector /= length;

		glm::vec3 objVector;
		objVector.x = sin(objAngle) + objPos.x;
		objVector.y = cos(objAngle) + objPos.y;
		objVector.z = 0;

		glm::vec3 normalVector;
		normalVector.x = sin(normalAngle) + objPos.x;
		normalVector.y = cos(normalAngle) + objPos.y;
		normalVector.z = 0;


		//Calculate the new angle for the bullet
		float dot = glm::dot(bulletVector, normalVector);
		float angleDif = acos(dot);

		//Determine which side of the normal the bullet is on and update the bullet's angle accordingly
		dot = glm::dot(bulletVector, objVector);
		if (dot > 0)
		{
			rotAngle = normalAngle + angleDif;
		}
		else
		{
			rotAngle = normalAngle - angleDif;
		}

		//Activate the bullet's effect
		Activate();
	}

	void BulletGameObject::Activate()
	{

	}

} // namespace game
