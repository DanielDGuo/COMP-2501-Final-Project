#include "boss_edge.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	/*
		Moving inherits from EnemyGameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	BossEdge::BossEdge(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, BossMiddle* p, bool isLeft)
		: EnemyGameObject(position, geom, shader, texture, 10) {
		parent = p;
		targetLoc = parent->GetPosition();
		targetLoc += glm::vec3(1, 0, 0);
		playerLoc = glm::vec3(0.0f, 0.0f, 0.0f);
		arrived = false;
		leftWing = isLeft;
	}

	void BossEdge::Update(double delta_time) {
		EnemyGameObject::Update(delta_time);

		//dies when the parent dies
		if (parent->getHealth() <= 0) {
			health = 0;
			return;
		}
		//offset from the boss
		float offset = 1.5;
		position_ = parent->GetPosition();
		if (leftWing) {
			position_.x -= offset;
		}
		else {
			position_.x += offset;
		}
	}

	void BossEdge::fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader* sprite_shader_, GLuint tex) {
		/*if (lastFireTime + 3.0f < glfwGetTime() && health > 0) {
			lastFireTime = glfwGetTime();
			glm::vec3 dir = glm::normalize(playerLoc - position_);
			float rotAngle = glm::atan(dir.y, dir.x);

			enemy_bullets_.push_back(new BulletGameObject(position_, sprite_, sprite_shader_, tex, rotAngle, 3, true));
		}*/

		//fire downwards 4 times a second
		if (lastFireTime + 0.25f < glfwGetTime() && health > 0) {
			lastFireTime = glfwGetTime();
			glm::vec3 dir = glm::vec3(0, -1, 0);
			float rotAngle = glm::atan(dir.y, dir.x);
			//3 damage bullets
			enemy_bullets_.push_back(new BulletGameObject(position_, sprite_, sprite_shader_, tex, rotAngle, 3, true));
		}
	}

} // namespace game
