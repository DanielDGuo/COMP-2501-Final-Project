#include "enemy_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	/*
		EnemyGameObject inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	EnemyGameObject::EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec3& targetLoc, int mode)
		: GameObject(position, geom, shader, texture, 1) {
		if (mode == 0) {
			stationary = true;
			patrolling = false;
			moving = false;
		}
		else {
			stationary = false;
			patrolling = true;
			moving = false;
		}
		this->targetLoc = targetLoc;
	}

	void EnemyGameObject::Update(double delta_time) {
		GameObject::Update(delta_time);

		if (timeOfDeath != NULL) {
		}
		else if (stationary) {
		}
		else if (patrolling) {
			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::rotate(trans, glm::radians(0.05f), glm::vec3(0.0f, 0.0f, 1.0f));
			position_.x = (trans * glm::vec4(position_, 1.0f)).x;
			position_.y = (trans * glm::vec4(position_, 1.0f)).y;
		}
		else if (moving) {
			glm::mat4 trans = glm::mat4(1.0f);
			glm::vec3 newLoc = glm::normalize(glm::vec3(-(position_.x - targetLoc.x), -(position_.y - targetLoc.y), 1.0f));
			newLoc.x /= 3000;
			newLoc.y /= 3000;
			trans = glm::translate(trans, newLoc);
			position_.x = (trans * glm::vec4(position_, 1.0f)).x;
			position_.y = (trans * glm::vec4(position_, 1.0f)).y;
		}
	}

} // namespace game
