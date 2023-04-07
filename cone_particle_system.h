#ifndef CONE_PARTICLE_SYSTEM_H_
#define CONE_PARTICLE_SYSTEM_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class ConeParticleSystem : public GameObject {

        public:
            ConeParticleSystem(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture, GameObject *parent);

            void Update(double delta_time) override;

            void Render(glm::mat4 view_matrix, double current_time);

            GameObject* getParent(){ return parent_; };

        private:
            GameObject *parent_;

    }; // class ConeParticleSystem

} // namespace game

#endif // CONE_PARTICLE_SYSTEM_H_
