#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#define NUM_TEXTURES 19
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "sprite.h"
#include "shader.h"
#include "game_object.h"
#include "collectible_game_object.h"
#include "enemy_game_object.h"
#include "player_game_object.h"
#include "temp_game_object.h"
#include "bullet_game_object.h"
#include "standard_shot.h"
#include "triple_shot.h"
#include "obstacle_game_object.h"
#include "flavour_game_object.h"
#include "cone_particle_system.h"
#include "background_game_object.h"
#include "kamakaze_enemy.h"
#include "moving_enemy.h"
#include "stationary_enemy.h"
#include "boss_middle.h"
#include "boss_edge.h"
#include "player_particles.h"
#include "bullet_particles.h"
#include "particles.h"
#include "particle_system.h"
#include "text_game_object.h"

#define CAMERA_ZOOM 0.25

#define MAX_WALLS 2
#define MIN_WALL_LENGTH 0.1
#define MAX_WALL_LENGTH 2

namespace game {

	// A class for holding the main game objects
	class Game {

	public:
		// Constructor and destructor
		Game(void);
		~Game();

		// Call Init() before calling any other method
		// Initialize graphics libraries and main window
		void Init(void);

		// Set up the game (scene, game objects, etc.)
		void Setup(void);

		// Run the game (keep the game active)
		void MainLoop(void);

	private:
		// Main window: pointer to the GLFW window structure
		GLFWwindow* window_;

		// Sprite geometry
		Geometry* sprite_;

		// Particle geometry for player related particles
		Geometry* player_particles_;

		// Particle geometry for explosion
		Geometry* explosionPart_;

		// Particle geometry for bullet particles
		Geometry* bullet_particles_;

		// Shader for rendering sprites in the scene
		Shader sprite_shader_;

		// Shader for rendering player particles
		Shader player_particle_shader_;

		// Shader for rendering explosion particles
		Shader particle_shader_;

		//shader for text
		Shader text_shader_;

		// Shader for rendering bullet particles
		Shader bullet_particle_shader_;

		// References to textures - increased by (DANIEL GUO)
		GLuint tex_[NUM_TEXTURES];

		// List of background game objects
		std::vector<GameObject*> background_game_objects_;

		// List of enemy game objects
		std::vector<EnemyGameObject*> enemy_game_objects_;
		bool summonedBoss;
		float lastSpawned;

		// List of player game objects
		std::vector<PlayerGameObject*> player_game_objects_;

		// List of collectible game objects
		std::vector<CollectibleObject*> collectible_game_objects_;

		// List of temporary game objects
		std::vector<TempGameObject*> temp_game_objects_;

		// List of ally bullet game objects
		std::vector<BulletGameObject*> ally_bullets_;

		// List of enemy bullet game objects
		std::vector<BulletGameObject*> enemy_bullets_;

		// List of obstacle game objects
		std::vector<ObstacleObject*> obstacles_;

		// List of player effects
		std::vector<GameObject*> player_effects;

		// List of bullet effects
		std::vector<ConeParticleSystem*> bullet_effects_;

		// List of hud objects
		std::vector<GameObject*> hud_objects;

		FlavourGameObject* blade;

		//keeps track of number of game state
		bool gameOver;

		// Keep track of time
		double current_time_;

		// Callback for when the window is resized
		static void ResizeCallback(GLFWwindow* window, int width, int height);

		// Set a specific texture
		void SetTexture(GLuint w, const char* fname);

		// Load all textures
		void SetAllTextures();

		// Handle user input
		void Controls(double delta_time);

		// Update the game based on user input and simulation
		void Update(glm::mat4 view_matrix, double delta_time);

		//Helper function to convert from screen coordinates to world coordinates
		void ConvertToWorldCoords(glm::vec3& pos);

		// Time variables
		float lastFireTime;
		
		// Wall variables
		int numWalls;
		bool drawingWall;
		glm::vec3 wallStartPos;
		int wallStorage;

		//score variables
		int curScore;
		int finalScore;
	}; // class Game

} // namespace game

#endif // GAME_H_
