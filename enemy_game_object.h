#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

	// Inherits from GameObject
	class EnemyGameObject : public GameObject {

	public:
		EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, int health);

		virtual void Update(double delta_time) override;

		inline void setPlayerLoc(glm::vec3& playerPos) { playerLoc = playerPos; };

	protected:
		// location of player for some derived classes
		glm::vec3 playerLoc;
	}; // class EnemyGameObject

} // namespace game

#endif // ENEMY_GAME_OBJECT_H_
