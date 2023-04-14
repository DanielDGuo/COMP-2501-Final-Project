#ifndef TRIPLE_SHOT_H_
#define TRIPLE_SHOT_H_

#include "game_object.h"
#include "bullet_game_object.h"

namespace game {

	// Inherits from BulletGameObject
	class TripleShot : public BulletGameObject {

	public:
		TripleShot(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy, bool activated);

		//Activates the unique effect of the given bullet
		void Activate(std::vector<BulletGameObject*>* bullets) override;

	}; // class TripleShot

} // namespace game

#endif // TRIPLE_SHOT_H_