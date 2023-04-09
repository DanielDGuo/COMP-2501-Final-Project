#include "enemy_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp> 

namespace game {

	/*
		EnemyGameObject inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	EnemyGameObject::EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, int health)
		: GameObject(position, geom, shader, texture, health) {
		playerLoc = glm::vec3(0.0f, 0.0f, 0.0f);
		canFire = false;
	}

	void EnemyGameObject::Update(double delta_time) {
		GameObject::Update(delta_time);

		if (timeOfDeath != NULL) {
			// Enemy has died. End the update.
			return;
		}
	}

	void EnemyGameObject::fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader sprite_shader_, GLuint tex) {
		//default enemies do not fire bullets
	}

} // namespace game
