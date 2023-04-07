#ifndef TEMP_GAME_OBJECT_H_
#define TEMP_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class TempGameObject : public GameObject {

        public:
            TempGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture, int lifespan);

            // Update function for moving the player object around
            void Update(double delta_time) override;

            inline void setPlayerExplosion(bool p) { playerExplosion = p; }
            inline bool getPlayerExplosion() { return playerExplosion; }
    protected:
        int spawnTime;
        int lifespan;
        bool playerExplosion;
    }; // class TempGameObject

} // namespace game

#endif // TEMP_GAME_OBJECT_H_
