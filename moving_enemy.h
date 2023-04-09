#ifndef MOVING_ENEMY_H
#define MOVING_ENEMY_H

#include "enemy_game_object.h"

/*
	This enemy spawns off screen, and tries to get within 1 unit to its target location. 
	Upon reaching that point, the enemy rotates around it and fires bullets at the player location.
	This enemy has 5 health
*/

namespace game {

	// Inherits from GameObject
	class Moving : public EnemyGameObject {

	public:
		Moving(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec3& targetLoc);

		void Update(double delta_time) override;

		inline void setTargetLoc(glm::vec3& newTarget) { targetLoc = newTarget; };

	private:
		glm::vec3 targetLoc;
		bool arrived;
	}; // class Moving

} // namespace game

#endif // MOVING_ENEMY_H
