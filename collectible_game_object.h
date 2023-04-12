#ifndef COLLECTIBLE_GAME_OBJECT_H_
#define COLLECTIBLE_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class CollectibleObject : public GameObject {

        public:
            CollectibleObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, int t);

            // Update function
            void Update(double delta_time) override;
            int getType() { return type; }
    private:
        int type;
        //0 is invin
        //1 is health++
        //2 is wall ++

    }; // class TempGameObject

} // namespace game

#endif // COLLECTIBLE_GAME_OBJECT_H_
