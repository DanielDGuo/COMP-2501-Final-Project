#include "moving_enemy.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	/*
		Moving inherits from EnemyGameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	Moving::Moving(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec3& targetLoc)
		: EnemyGameObject(position, geom, shader, texture, 5) {
		this->targetLoc = targetLoc;
		playerLoc = glm::vec3(0.0f, 0.0f, 0.0f);
		arrived = false;
		score = 5;
	}

	void Moving::Update(double delta_time) {
		EnemyGameObject::Update(delta_time);

		if (health <= 0) { return; }

		//move towards targetLoc
		if (glm::distance(position_, targetLoc) > 1.0f && arrived == false) {
			EnemyGameObject::Update(delta_time);
			glm::mat4 trans = glm::mat4(1.0f);
			glm::vec3 newLoc = glm::normalize(glm::vec3(-(position_.x - targetLoc.x), -(position_.y - targetLoc.y), 0.0f));
			newLoc *= delta_time * 1.0f;
			trans = glm::translate(trans, newLoc);
			position_.x = (trans * glm::vec4(position_, 1.0f)).x;
			position_.y = (trans * glm::vec4(position_, 1.0f)).y;

		}else{//rotate around targetLoc
			arrived = true;
			glm::mat4 trans = glm::mat4(1.0f);

			glm::mat4 t1 = glm::translate(glm::mat4(1), -targetLoc);
			glm::mat4 r = glm::rotate(trans, glm::radians(float(delta_time) * 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 t2 = glm::translate(glm::mat4(1), targetLoc);

			trans = t2 * r * t1;

			position_.x = (trans * glm::vec4(position_, 1.0f)).x;
			position_.y = (trans * glm::vec4(position_, 1.0f)).y;
		}
	}

	void Moving::fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader* sprite_shader_, GLuint tex) {
		if (arrived && lastFireTime + 3.0f < glfwGetTime() && health > 0) {
			lastFireTime = glfwGetTime();
			glm::vec3 dir = glm::normalize(playerLoc - position_);
			float rotAngle = glm::atan(dir.y, dir.x);

			enemy_bullets_.push_back(new BulletGameObject(position_, sprite_, sprite_shader_, tex, rotAngle, 3, true));
		}
	}

} // namespace game
