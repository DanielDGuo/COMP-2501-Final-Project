#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

	// Inherits from GameObject
	class EnemyGameObject : public GameObject {

	public:
		EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, glm::vec3& targetLocm, int mode);

		void Update(double delta_time) override;

		inline bool getStationary() { return stationary; };
		inline void setTargetLoc(glm::vec3& newTarget) { targetLoc = newTarget; };
		inline void setPatrolling(bool isPatrolling) { patrolling = isPatrolling; };
		inline void setMoving(bool isMoving) { moving = isMoving; };

	private:
		bool stationary;
		bool patrolling;
		bool moving;
		glm::vec3 targetLoc;
	}; // class EnemyGameObject

} // namespace game

#endif // ENEMY_GAME_OBJECT_H_
