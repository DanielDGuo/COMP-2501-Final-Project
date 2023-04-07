#ifndef PLAYER_PARTICLES_H_
#define PLAYER_PARTICLES_H_

#include "geometry.h"

#define NUM_PARTICLES 4000

namespace game {

    // A set of particles that can be rendered
    class PlayerParticles : public Geometry {

        public:
            PlayerParticles(void);

            // Create the geometry (called once)
            void CreateGeometry(void);

            // Use the geometry
            void SetGeometry(GLuint shader_program);

    }; // class Particles
} // namespace game

#endif // PLAYER_PARTICLES_H_
