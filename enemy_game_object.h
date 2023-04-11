#ifndef ENEMY_GAME_OBJECT_H_
#define ENEMY_GAME_OBJECT_H_

#include <vector>
#include "game_object.h"
#include "bullet_game_object.h"

namespace game {

	// Inherits from GameObject
	class EnemyGameObject : public GameObject {

	public:
		EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, int health);

		virtual void Update(double delta_time) override;

		inline void setPlayerLoc(glm::vec3& playerPos) { playerLoc = playerPos; };

		virtual void fire(std::vector<BulletGameObject*>& enemy_bullets_, Geometry* sprite_, Shader* sprite_shader_, GLuint tex);

	protected:
		// location of player for some derived classes
		glm::vec3 playerLoc;
		// stores if the enemy can fire
		float lastFireTime;
		//if it has arrived at position or not
		bool arrived;

	}; // class EnemyGameObject

} // namespace game

#endif // ENEMY_GAME_OBJECT_H_
