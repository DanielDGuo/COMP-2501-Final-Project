#ifndef BOSS_EDGE_H
#define BOSS_EDGE_H

#include "enemy_game_object.h"
#include "boss_middle.h"

/*
	This enemy spawns off screen, and tries to get within 1 unit to its target location. 
	Upon reaching that point, the enemy rotates around it and fires bullets at the player location.
	This enemy has 5 health
*/

namespace game {

	// Inherits from GameObject
	class BossEdge : public EnemyGameObject {

	public:
		BossEdge(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, BossMiddle* parent, bool isLeft);

		void Update(double delta_time) override;

		inline void setTargetLoc(glm::vec3& newTarget) { targetLoc = newTarget; };

		void fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader* sprite_shader_, GLuint tex) override;

		inline void setHealth(int h) override { parent->setHealthEdge(parent->getHealth() - (health - h)); } ;
	private:
		glm::vec3 targetLoc;
		BossMiddle* parent;
		//signals if its on the left or right of the boss
		bool leftWing;
	}; // class Moving

} // namespace game

#endif // MOVING_ENEMY_H
