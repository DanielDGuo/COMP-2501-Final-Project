#include "stationary_enemy.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	/*
		Stationary inherits from EnemyGameObject
		It overrides EnemyGameObject's update method, so that you can check for input to change the velocity of the player
	*/

	Stationary::Stationary(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec3& targetLoc)
		: EnemyGameObject(position, geom, shader, texture, 15) {
		this->targetLoc = targetLoc;
		score = 3;
	}

	void Stationary::Update(double delta_time) {
		EnemyGameObject::Update(delta_time);
		if (health <= 0) { return; }
		if (glm::distance(position_, targetLoc) > 0.2f) {
			glm::mat4 trans = glm::mat4(1.0f);
			glm::vec3 newLoc = glm::normalize(glm::vec3(-(position_.x - targetLoc.x), -(position_.y - targetLoc.y), 0.0f));
			newLoc *= delta_time * 1.0f;
			trans = glm::translate(trans, newLoc);
			position_.x = (trans * glm::vec4(position_, 1.0f)).x;
			position_.y = (trans * glm::vec4(position_, 1.0f)).y;
		}
		else {
			arrived = true;
		}

	}

	void Stationary::fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader* sprite_shader_, GLuint tex) {
		if (arrived && lastFireTime + 3.0f < glfwGetTime() && health > 0) {
			lastFireTime = glfwGetTime();
			glm::vec3 dir = glm::normalize(playerLoc - position_);
			float rotAngle = glm::atan(dir.y, dir.x);

			enemy_bullets_.push_back(new BulletGameObject(position_, sprite_, sprite_shader_, tex, rotAngle, 5, true));
		}
	}

} // namespace game
