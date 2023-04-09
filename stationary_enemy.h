#ifndef STATIONARY_ENEMY_H_
#define STATIONARY_ENEMY_H_

#include "enemy_game_object.h"

/*
	This enemy spawns off screen, and tries to move to its target location.
	The enemy will then try to shoot bullets at the player location.
	This enemy spawns with 15 health
*/

namespace game {

	// Inherits from EnemyGameObject
	class Stationary : public EnemyGameObject {

	public:
		Stationary(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec3& targetLoc);

		void Update(double delta_time) override;

		void fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader sprite_shader_, GLuint tex) override;
	private:
		glm::vec3 targetLoc;
	}; // class EnemyGameObject

} // namespace game

#endif // STATIONARY_ENEMY_H_
