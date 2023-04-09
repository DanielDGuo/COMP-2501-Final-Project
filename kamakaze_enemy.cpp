#include "kamakaze_enemy.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	/*
		Kamakaze inherits from EnemyGameObject
		It overrides EnemyGameObject's update method, so that you can check for input to change the velocity of the player
	*/

	Kamakaze::Kamakaze(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: EnemyGameObject(position, geom, shader, texture, 1) {
	}

	void Kamakaze::Update(double delta_time) {
		EnemyGameObject::Update(delta_time);
		glm::mat4 trans = glm::mat4(1.0f);
		glm::vec3 newLoc = glm::normalize(glm::vec3(-(position_.x - playerLoc.x), -(position_.y - playerLoc.y), 0.0f));
		newLoc *= delta_time * 1.0f;
		trans = glm::translate(trans, newLoc);
		position_.x = (trans * glm::vec4(position_, 1.0f)).x;
		position_.y = (trans * glm::vec4(position_, 1.0f)).y;
	}

} // namespace game
