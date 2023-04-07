#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

	// Inherits from GameObject
	class PlayerGameObject : public GameObject {

	public:
		PlayerGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time) override;

		inline void setNumCollectibles(int i) { numCollectibles = i; }
		inline int getNumCollectibles() { return numCollectibles; }
		inline bool getInvincible() { return invincible; };
	protected:
		int invincibleStartTime;
		//number of collectibles collected by object
		int numCollectibles;
		//toggles invincibility
		bool invincible;
	}; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
