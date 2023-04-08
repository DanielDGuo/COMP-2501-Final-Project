#ifndef PARTICLE_SYSTEM_H_
#define PARTICLE_SYSTEM_H_

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class ParticleSystem : public GameObject {

    public:
        ParticleSystem(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, GameObject* parent, int t);
        ~ParticleSystem();
        void Update(double delta_time) override;

        void Render(glm::mat4 view_matrix, double current_time);


        void setSpawntime(double ct) { spawnTime = ct; }
    private:
        GameObject* parent_;
        int type;
        //0 is unknown
        //1 is player
        //2 is explosion
        //3 is bullet

        float spawnTime;
    }; // class ParticleSystem

} // namespace game

#endif // PARTICLE_SYSTEM_H_
