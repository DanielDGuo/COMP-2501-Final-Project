#include "boss_middle.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	/*
		Moving inherits from EnemyGameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	BossMiddle::BossMiddle(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, GameObject* p)
		: EnemyGameObject(position, geom, shader, texture, 50) {
		parent = p;
		/*
		targetLoc = parent->GetPosition();
		targetLoc += glm::vec3(0, 2, 0);
		*/
		playerLoc = glm::vec3(0.0f, 0.0f, 0.0f);
		arrived = false;
	}

	void BossMiddle::Update(double delta_time) {
		EnemyGameObject::Update(delta_time);
		if (health <= 0) {
			return;
		}
		//always appear over the player
		position_.y = parent->GetPosition().y + 3;

		//move towards targetLoc
		/*if (glm::distance(position_, targetLoc) > 1.0f && arrived == false) {
			EnemyGameObject::Update(delta_time);
			glm::mat4 trans = glm::mat4(1.0f);
			glm::vec3 newLoc = glm::normalize(glm::vec3(-(position_.x - targetLoc.x), -(position_.y - targetLoc.y), 0.0f));
			newLoc *= delta_time * 1.0f;
			trans = glm::translate(trans, newLoc);
			position_.x = (trans * glm::vec4(position_, 1.0f)).x;
			position_.y = (trans * glm::vec4(position_, 1.0f)).y;

		}else{
			*/
			//move relative to the player
		/*
		glm::vec3 movement = glm::vec3(glm::sin(glfwGetTime()), 0, 0);
		movement *= 0.008;
		std::cout << movement.x << std::endl;
		glm::mat4 trans = glm::translate(glm::mat4(1), movement);
		position_.x = (trans * glm::vec4(position_, 1.0f)).x;
		position_.y = (trans * glm::vec4(position_, 1.0f)).y;
		*/

		//move left and right in a sinusoidal(how do you spell) pattern
		position_.x += glm::sin(glfwGetTime())/500;

		if (position_.x < parent->GetPosition().x - 3) {
			position_.x = parent->GetPosition().x - 3;
		}
		if (position_.x > parent->GetPosition().x + 3) {
			position_.x = parent->GetPosition().x + 3;
		}
		//}
	}

	void BossMiddle::fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader* sprite_shader_, GLuint tex) {
		//only the edges fire
	}

} // namespace game
