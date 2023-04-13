#ifndef TEXT_GAME_OBJECT_H_
#define TEXT_GAME_OBJECT_H_

#include <string>

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class TextGameObject : public GameObject {

    public:
        TextGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, GameObject* p, int t);

        // Text to be displayed
        std::string GetText(void) const;
        void SetText(std::string text);

        inline int getType() { return type; }

        // Render function for the text
        void Render(glm::mat4 view_matrix, double current_time) override;

    private:
        std::string text_;
        GameObject* parent_;
        int type;
        //0 is permanent text
        //1 is hp counter
        //2 is wall counter

    }; // class TextGameObject

} // namespace game

#endif // TEXT_GAME_OBJECT_H_
