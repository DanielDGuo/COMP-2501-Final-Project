#include "player_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <iostream>

namespace game {

	/*
		PlayerGameObject inherits from GameObject
		It overrides GameObject's update method, so that you can check for input to change the velocity of the player
	*/

	PlayerGameObject::PlayerGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture, 3) {
		numCollectibles = 0;
		invincible = false;
		invincibleStartTime = -99;
	}

	// Update function for moving the player object around
	void PlayerGameObject::Update(double delta_time) {
		// Call the parent's update method to move the object in standard way, if desired
		GameObject::Update(delta_time);
		if (numCollectibles == 5) {
			numCollectibles = 0;
			invincibleStartTime = glfwGetTime();
			invincible = true;
		}
		if (invincibleStartTime + 10 <= (int)glfwGetTime()) {
			invincible = false;
		}
	}
} // namespace game
