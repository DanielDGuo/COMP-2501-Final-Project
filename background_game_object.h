#ifndef BACKGROUND_GAME_OBJECT_H_
#define BACKGROUND_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class Background : public GameObject {

        public:
            Background(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

            // Update function for moving the player object around
            void Update(double delta_time) override;


    }; // class Background

} // namespace game

#endif // BACKGROUND_GAME_OBJECT_H_
