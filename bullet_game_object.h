#ifndef BULLET_GAME_OBJECT_H_
#define BULLET_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

	// Inherits from GameObject
	class BulletGameObject : public GameObject {

	public:
		BulletGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy);

		void Update(double delta_time) override;

		//Activates the ricochet for the given bullet
		void Ricochet(GameObject* obj);

		//Activates the unique effect of the given bullet
		virtual void Activate();

		int getDamage() { return damage; }

	private:
		//Bullet damage
		int damage;
		//determines if it's an ally bullet
		bool enemyBullet;
		//timestamp of creation
		float spawnTime;
		//determines if the bullet is in ricochet mode
		bool ricocheted;

	}; // class BulletGameObject

} // namespace game

#endif // BULLET_GAME_OBJECT_H_
