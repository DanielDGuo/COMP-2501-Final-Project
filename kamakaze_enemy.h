#ifndef KAMAKAZE_ENEMY_H_
#define KAMAKAZE_ENEMY_H_

#include "enemy_game_object.h"

/*
	This enemy spawns off screen, and tries tries to move towards the player at any given moment. 
	This enemy has 1 health
*/

namespace game {

	// Inherits from EnemyGameObject
	class Kamakaze : public EnemyGameObject {

	public:
		Kamakaze(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time) override;

		void fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader* sprite_shader_, GLuint tex) override;
	private:
	}; // class Kamakaze

} // namespace game

#endif // KAMAKAZE_ENEMY_H_
