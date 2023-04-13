#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

	// Inherits from GameObject
	class PlayerGameObject : public GameObject {

	public:
		PlayerGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

		void Update(double delta_time) override;

		//Cycles to the next weapon
		void SwitchWeapons();

		inline void setNumCollectibles(int i) { numCollectibles = i; }
		inline void setHealth(int h) { if (invincible && h < health) { return; } health = h; };
		inline int getNumCollectibles() { return numCollectibles; }
		inline bool getInvincible() { return invincible; };
		inline int getWeapon() { return weapon; }
	protected:
		int invincibleStartTime;
		//number of collectibles collected by object
		int numCollectibles;
		//toggles invincibility
		bool invincible;
		//selected weapon
		int weapon;
		//number of weapons
		int numWeapons;
		//time since weapon was last switched
		float timeSinceSwitch;
	}; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
