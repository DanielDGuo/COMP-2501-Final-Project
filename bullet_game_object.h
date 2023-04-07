#ifndef BULLET_GAME_OBJECT_H_
#define BULLET_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

	// Inherits from GameObject
	class BulletGameObject : public GameObject {

	public:
		BulletGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, bool enemy);

		void Update(double delta_time) override;

	private:
		//determines if it's an ally bullet
		bool enemyBullet;
		//timestamp of creation
		float spawnTime;
	}; // class BulletGameObject

} // namespace game

#endif // BULLET_GAME_OBJECT_H_
