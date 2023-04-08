#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "geometry.h"

namespace game {

    /*
        GameObject is responsible for handling the rendering and updating of one object in the game world
        The update and render methods are virtual, so you can inherit them from GameObject and override the update or render functionality (see PlayerGameObject for reference)
    */
    class GameObject {

        public:
            // Constructor
            GameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, int health);
            // Constructor
            GameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

            // Update the GameObject's state. Can be overriden in children
            virtual void Update(double delta_time);

            // Renders the GameObject 
            virtual void Render(glm::mat4 view_matrix, double current_time);

            // Getters
            inline glm::vec3& GetPosition(void) { return position_; }
            inline float GetScalex(void) { return scalex; }
            inline float GetScaley(void) { return scaley; }
            inline glm::vec3& GetVelocity(void) { return velocity_; }
            inline bool getDelStatus() { return delObj; }
            inline int getHealth() { return health; };
            inline float getRotation() { return rotAngle; };
            inline float getTimeOfDeath() { return timeOfDeath; };
            float getLife() { return lifespan; }

            // Setters
            inline void SetPosition(const glm::vec3& position) { position_ = position; }
            inline void SetScale(float s) { scalex = s; scaley = s; }
            inline void SetScalex(float s) { scalex = s; }
            inline void SetScaley(float s) { scaley = s; }
            inline void SetVelocity(const glm::vec3& velocity) { velocity_ = velocity; }
            inline void SetTexture(const GLuint texture) { texture_ = texture; }
            inline void setHealth(int h) { health = h; };
            inline void setRotation(float r) { rotAngle = r; };
            inline void setDelStatus(bool d) { delObj = d; };
            void setLife(float l) { lifespan = l; }

        protected:
            // Object's Transform Variables
            glm::vec3 position_;
            float scalex;
            float scaley;
            glm::vec3 velocity_;
            float rotAngle;
            //request for deletion
            bool delObj;
            //keeps track of object health
            int health;

            float timeOfDeath;

            float lifespan = NULL;
            // Geometry
            Geometry *geometry_;
 
            // Shader
            Shader *shader_;

            // Object's texture reference
            GLuint texture_;

    }; // class GameObject

} // namespace game

#endif // GAME_OBJECT_H_
