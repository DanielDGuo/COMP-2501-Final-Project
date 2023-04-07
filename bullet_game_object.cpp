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
		// Calculate which side of the wall the bullet is on
		float normal = obj->getRotation() + 3.1415 / 2;
		float angleDif = acos((cos(rotAngle) * cos(normal)) + (sin(rotAngle) * sin(normal)));
		// Calculate which side of the normal the bullet is on
		damage *= 2;
	}

} // namespace game
