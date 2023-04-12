#include "collectible_game_object.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace game {

/*
	TempameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

	CollectibleObject::CollectibleObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture, int t)
		: GameObject(position, geom, shader, texture, 1) {
		type = t;
	}

void CollectibleObject::Update(double delta_time) {
	shader_->SetUniform1i("deceased", 0);
	if (health <= 0) {
		delObj = true;
	}
}
} // namespace game
