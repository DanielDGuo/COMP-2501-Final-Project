#ifndef FLAVOUR_GAME_OBJECT_H_
#define FLAVOUR_GAME_OBJECT_H_

#include "game_object.h"

namespace game {

	// Inherits from GameObject
	class FlavourGameObject : public GameObject {

		public:
			FlavourGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, GameObject* parent);

			void Update(double delta_time) override;
			void Render(glm::mat4 view_matrix, double current_time) override;

		private:
			GameObject* parent_;

		}; // class ParticleSystem

	} // namespace game

#endif // FLAVOUR_GAME_OBJECT_H_
