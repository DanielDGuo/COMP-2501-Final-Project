#ifndef BULLET_PARTICLES_H_
#define BULLET_PARTICLES_H_

#include "geometry.h"

#define NUM_PARTICLES 4000

namespace game {

    // A set of particles that can be rendered
    class BulletParticles : public Geometry {

        public:
            BulletParticles();

            // Create the geometry (called once)
            void CreateGeometry(void);

            // Use the geometry
            void SetGeometry(GLuint shader_program);
       
    }; // class Particles
} // namespace game

#endif // BULLET_PARTICLES_H_
