#ifndef OBSTACLE_GAME_OBJECT_H_
#define OBSTACLE_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class ObstacleObject : public GameObject {

    public:
        ObstacleObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, const glm::vec3& start, const glm::vec3& end, float length, float rot);

        // Update function
        void Update(double delta_time) override;

        //Getters for the start and end positions
        inline glm::vec3& getStartPos(void) { return startPos; }
        inline glm::vec3& getEndPos(void) { return endPos; }
    
    protected:
        glm::vec3 startPos;
        glm::vec3 endPos;
        float timeSinceCreation;
    }; // class TempGameObject

} // namespace game

#endif // OBSTACLE_GAME_OBJECT_H_