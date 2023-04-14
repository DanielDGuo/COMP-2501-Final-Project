#ifndef BULLET_GAME_OBJECT_H_
#define BULLET_GAME_OBJECT_H_

#include "game_object.h"
#include "obstacle_game_object.h"
#include <vector>

namespace game {

	// Inherits from GameObject
	class BulletGameObject : public GameObject {

	public:
		BulletGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy);

		void Update(double delta_time) override;

		//Activates the ricochet for the given bullet
		void Ricochet(ObstacleObject* obj);

		//Activates the unique effect of the given bullet
		virtual void Activate(std::vector<BulletGameObject*>* bullets);

		int getDamage() { return damage; }

	protected:
		//Bullet damage
		int damage;
		//determines if it's an ally bullet
		bool enemyBullet;
		//timestamp of creation
		float spawnTime;
		//Keeps track of time since the last ricochet
		float timeSinceLastRicochet;
		//Tracks whether the bullet has been activated
		bool activated;

	}; // class BulletGameObject

} // namespace game

#endif // BULLET_GAME_OBJECT_H_
