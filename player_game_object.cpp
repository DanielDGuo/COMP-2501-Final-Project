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
		: GameObject(position, geom, shader, texture, 15) {
		numCollectibles = 0;
		invincible = false;
		invincibleStartTime = -99;
		weapon = 0;
		numWeapons = 2;
	}

	// Update function for moving the player object around
	void PlayerGameObject::Update(double delta_time) {
		// Call the parent's update method to move the object in standard way, if desired
		GameObject::Update(delta_time);

		//reset the rotation to be between 0 and 2pi
		if (rotAngle > 2 * 3.1415) {
			rotAngle -= 2 * 3.1415;
		}
		if (rotAngle < 0) {
			rotAngle += 2 * 3.1415;
		}
		if (numCollectibles == 5) {
			numCollectibles = 0;
			invincibleStartTime = glfwGetTime();
			invincible = true;
		}
		if (invincibleStartTime + 10 <= (int)glfwGetTime()) {
			invincible = false;
		}
	}

	void PlayerGameObject::SwitchWeapons()
	{
		++weapon;
		if (weapon >= numWeapons || weapon < 0)
		{
			weapon = 0;
		}
	}
} // namespace game
