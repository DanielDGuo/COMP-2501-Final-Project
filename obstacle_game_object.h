#ifndef OBSTACLE_GAME_OBJECT_H_
#define OBSTACLE_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class ObstacleObject : public GameObject {

    public:
        ObstacleObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, float length, float rot);

        // Update function
        void Update(double delta_time) override;
    }; // class TempGameObject

} // namespace game

#endif // OBSTACLE_GAME_OBJECT_H_