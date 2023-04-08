#ifndef STANDARD_SHOT_H_
#define STANDARD_SHOT_H_

#include "game_object.h"
#include "bullet_game_object.h"

namespace game {

    // Inherits from BulletGameObject
    class StandardShot : public BulletGameObject {

	public:
		StandardShot(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float direction, int dam, bool enemy);

		//Activates the unique effect of the given bullet
		void Activate() override;

    }; // class StandardShot

} // namespace game

#endif // STANDARD_SHOT_H_