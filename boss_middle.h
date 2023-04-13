#ifndef BOSS_MIDDLE_H
#define BOSS_MIDDLE_H

#include "enemy_game_object.h"

/*
	This enemy spawns off screen, and tries to get within 1 unit to its target location. 
	Upon reaching that point, the enemy rotates around it and fires bullets at the player location.
	This enemy has 5 health
*/

namespace game {

	// Inherits from GameObject
	class BossMiddle : public EnemyGameObject {

	public:
		BossMiddle(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, GameObject* parent);

		void Update(double delta_time) override;

		inline void setTargetLoc(glm::vec3& newTarget) { targetLoc = newTarget; };

		void fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader* sprite_shader_, GLuint tex) override;
		//takes double damage if bullets hit the middle
		inline void setHealth(int h) override { health = health - 2 * (health - h); };
		//takes normal damage if bullets hit edge
		inline void setHealthEdge(int h) { health =  h; };


	private:
		glm::vec3 targetLoc;
		GameObject* parent;
	}; // class Moving

} // namespace game

#endif // MOVING_ENEMY_H
