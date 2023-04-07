#include <stdexcept>
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <iostream>

#include <path_config.h>

#include "sprite.h"
#include "shader.h"
#include "player_game_object.h"
#include "temp_game_object.h"
#include "collectible_game_object.h"
#include "background_game_object.h"
#include "enemy_game_object.h"
#include "cone_particle_system.h"
#include "player_particles.h"
#include "bullet_particles.h"
#include "game.h"

namespace game {

	// Some configuration constants
	// They are written here as global variables, but ideally they should be loaded from a configuration file

	// Globals that define the OpenGL window and viewport
	const char* window_title_g = "Game Demo";
	const unsigned int window_width_g = 800;
	const unsigned int window_height_g = 800;
	const glm::vec3 viewport_background_color_g(0.0, 0.0, 1.0);

	// Directory with game resources such as textures
	const std::string resources_directory_g = RESOURCES_DIRECTORY;


	Game::Game(void)
	{
		// Don't do work in the constructor, leave it for the Init() function
	}


	void Game::Init(void)
	{

		// Initialize the window management library (GLFW)
		if (!glfwInit()) {
			throw(std::runtime_error(std::string("Could not initialize the GLFW library")));
		}

		// Set window to not resizable
		// Required or else the calculation to get cursor pos to screenspace will be incorrect
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Create a window and its OpenGL context
		window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g, NULL, NULL);
		if (!window_) {
			glfwTerminate();
			throw(std::runtime_error(std::string("Could not create window")));
		}

		// Make the window's OpenGL context the current one
		glfwMakeContextCurrent(window_);

		// Initialize the GLEW library to access OpenGL extensions
		// Need to do it after initializing an OpenGL context
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char*)glewGetErrorString(err))));
		}

		// Set event callbacks
		glfwSetFramebufferSizeCallback(window_, ResizeCallback);

		// Initialize player particle geometry
		player_particles_ = new PlayerParticles();
		player_particles_->CreateGeometry();

		// Initialize player particle geometry
		bullet_particles_ = new BulletParticles();
		bullet_particles_->CreateGeometry();

		// Initialize sprite geometry
		sprite_ = new Sprite();
		sprite_->CreateGeometry();

		// Initialize player particle shader
		player_particle_shader_.Init((resources_directory_g + std::string("/player_particle_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/player_particle_fragment_shader.glsl")).c_str());

		// Initialize player particle shader
		bullet_particle_shader_.Init((resources_directory_g + std::string("/player_particle_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/bullet_particle_fragment_shader.glsl")).c_str());

		// Initialize sprite shader
		sprite_shader_.Init((resources_directory_g + std::string("/sprite_vertex_shader.glsl")).c_str(), (resources_directory_g + std::string("/sprite_fragment_shader.glsl")).c_str());

		// Initialize time
		current_time_ = 0.0;

		//Initialize time variables
		lastFireTime = 0;
		
		//Initialize wall variables
		drawingWall = false;
		numWalls = 0;
	}


	Game::~Game()
	{
		// Free memory for all objects
		delete sprite_;
		delete player_particles_;
		delete bullet_particles_;
		for (int i = 0; i < background_game_objects_.size(); i++) {
			delete background_game_objects_[i];
		}
		for (int i = 0; i < enemy_game_objects_.size(); i++) {
			delete enemy_game_objects_[i];
		}
		for (int i = 0; i < player_game_objects_.size(); i++) {
			delete player_game_objects_[i];
		}
		for (int i = 0; i < collectible_game_objects_.size(); i++) {
			delete collectible_game_objects_[i];
		}
		for (int i = 0; i < temp_game_objects_.size(); i++) {
			delete temp_game_objects_[i];
		}
		for (int i = 0; i < ally_bullets_.size(); i++) {
			delete ally_bullets_[i];
		}
		for (int i = 0; i < enemy_bullets_.size(); i++) {
			delete enemy_bullets_[i];
		}
		for (int i = 0; i < player_effects.size(); i++) {
			delete player_effects[i];
		}
		for (int i = 0; i < bullet_effects_.size(); i++) {
			delete bullet_effects_[i];
		}



		// Close window
		glfwDestroyWindow(window_);
		glfwTerminate();
	}


	void Game::Setup(void)
	{

		// Setup the game world
		// sets the gameOver state
		gameOver = false;
		// Load textures
		SetAllTextures();

		// player(s)
		player_game_objects_.push_back(new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[0]));

		// stationary enemies
		enemy_game_objects_.push_back(new EnemyGameObject(glm::vec3(-1.0f, 1.0f, 0.0f), sprite_, &sprite_shader_, tex_[1], glm::vec3(0.0f, 0.0f, 0.0f), 0));
		enemy_game_objects_.push_back(new EnemyGameObject(glm::vec3(1.0f, -0.5f, 0.0f), sprite_, &sprite_shader_, tex_[2], glm::vec3(0.0f, 0.0f, 0.0f), 0));
		enemy_game_objects_.push_back(new EnemyGameObject(glm::vec3(2.0f, 2.0f, 0.0f), sprite_, &sprite_shader_, tex_[5], glm::vec3(0.0f, 0.0f, 0.0f), 0));

		// moving enemies
		srand(time(NULL));
		enemy_game_objects_.push_back(new EnemyGameObject(glm::vec3(rand() % 5 - 2, rand() % 5 - 2, 0.0f), sprite_, &sprite_shader_, tex_[6], glm::vec3(0.0f, 0.0f, 0.0f), 1));
		enemy_game_objects_.push_back(new EnemyGameObject(glm::vec3(rand() % 5 - 2, rand() % 5 - 2, 0.0f), sprite_, &sprite_shader_, tex_[6], glm::vec3(0.0f, 0.0f, 0.0f), 1));
		enemy_game_objects_.push_back(new EnemyGameObject(glm::vec3(rand() % 5 - 2, rand() % 5 - 2, 0.0f), sprite_, &sprite_shader_, tex_[6], glm::vec3(0.0f, 0.0f, 0.0f), 1));

		//collectibles
		collectible_game_objects_.push_back(new CollectibleObject(glm::vec3(-3.0f, -2.0f, 0.0f), sprite_, &sprite_shader_, tex_[8]));
		collectible_game_objects_.push_back(new CollectibleObject(glm::vec3(-3.0f, -1.0f, 0.0f), sprite_, &sprite_shader_, tex_[8]));
		collectible_game_objects_.push_back(new CollectibleObject(glm::vec3(-3.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[8]));
		collectible_game_objects_.push_back(new CollectibleObject(glm::vec3(-3.0f, 1.0f, 0.0f), sprite_, &sprite_shader_, tex_[8]));
		collectible_game_objects_.push_back(new CollectibleObject(glm::vec3(-3.0f, 2.0f, 0.0f), sprite_, &sprite_shader_, tex_[8]));

		collectible_game_objects_.push_back(new CollectibleObject(glm::vec3(-4.0f, -4.0f, 0.0f), sprite_, &sprite_shader_, tex_[8]));
		collectible_game_objects_.push_back(new CollectibleObject(glm::vec3(-1.0f, -1.0f, 0.0f), sprite_, &sprite_shader_, tex_[8]));

		// Setup background
		Background* background = new Background(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[3]);
		background->SetScale(10.0);
		background_game_objects_.push_back(background);

		// Setup particle system
		ConeParticleSystem* playerParticles = new ConeParticleSystem(glm::vec3(0.0f, -0.5f, 0.0f), player_particles_, &player_particle_shader_, tex_[4], player_game_objects_[0]);
		playerParticles->SetScale(0.2);
		player_effects.push_back(playerParticles);

		// handle the blade on the player (TO BE DELETED)
		blade = new FlavourGameObject(glm::vec3(0.0f, 0.0f, 0.0f), sprite_, &sprite_shader_, tex_[11], player_game_objects_[0]);
	}


	void Game::ResizeCallback(GLFWwindow* window, int width, int height)
	{

		// Set OpenGL viewport based on framebuffer width and height
		glViewport(0, 0, width, height);
	}


	void Game::SetTexture(GLuint w, const char* fname)
	{
		// Bind texture buffer
		glBindTexture(GL_TEXTURE_2D, w);

		// Load texture from a file to the buffer
		int width, height;
		unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		// Texture Wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Texture Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}


	void Game::SetAllTextures(void)
	{
		// Load all textures that we will need
		glGenTextures(NUM_TEXTURES, tex_);
		SetTexture(tex_[0], (resources_directory_g + std::string("/textures/Player.png")).c_str());
		SetTexture(tex_[1], (resources_directory_g + std::string("/textures/rat.png")).c_str());
		SetTexture(tex_[2], (resources_directory_g + std::string("/textures/skull.png")).c_str());
		SetTexture(tex_[3], (resources_directory_g + std::string("/textures/stars.png")).c_str());
		SetTexture(tex_[4], (resources_directory_g + std::string("/textures/orb.png")).c_str());
		// new textures 
		SetTexture(tex_[5], (resources_directory_g + std::string("/textures/OctoHead.png")).c_str());
		SetTexture(tex_[6], (resources_directory_g + std::string("/textures/OctoTent.png")).c_str());
		SetTexture(tex_[7], (resources_directory_g + std::string("/textures/boom.png")).c_str());
		SetTexture(tex_[8], (resources_directory_g + std::string("/textures/coin.png")).c_str());
		SetTexture(tex_[9], (resources_directory_g + std::string("/textures/PlayerInvincible.png")).c_str());
		SetTexture(tex_[10], (resources_directory_g + std::string("/textures/bullet.png")).c_str());
		SetTexture(tex_[11], (resources_directory_g + std::string("/textures/blade.png")).c_str());
		SetTexture(tex_[12], (resources_directory_g + std::string("/textures/wall.png")).c_str());
		glBindTexture(GL_TEXTURE_2D, tex_[0]);
	}


	void Game::MainLoop(void)
	{
		glm::vec3 playerPos;

		// Loop while the user did not close the window
		double last_time = glfwGetTime();
		while (!glfwWindowShouldClose(window_)) {

			// Clear background
			glClearColor(viewport_background_color_g.r,
				viewport_background_color_g.g,
				viewport_background_color_g.b, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 view_matrix = glm::mat4(1.0f);
			view_matrix = glm::scale(view_matrix, glm::vec3(CAMERA_ZOOM, CAMERA_ZOOM, CAMERA_ZOOM));

			if (!gameOver) {//while not gameOver, access the player position
				playerPos = -player_game_objects_[0]->GetPosition();
			}


			//translate the view matrix by the player position, or the last player position it saw
			view_matrix = glm::translate(view_matrix, playerPos);

			// Calculate delta time
			double current_time = glfwGetTime();
			double delta_time = current_time - last_time;
			last_time = current_time;

			// Update other events like input handling
			glfwPollEvents();

			// Update the game
			Update(view_matrix, delta_time);

			// Push buffer drawn in the background onto the display
			glfwSwapBuffers(window_);
		}
	}


	void Game::Update(glm::mat4 view_matrix, double delta_time)
	{

		// Update time
		current_time_ += delta_time;

		// Handle user input
		Controls(delta_time);

		//update and render all player game objects
		for (int i = 0; i < player_game_objects_.size(); i++) {
			// Get the player
			PlayerGameObject* playerObject = player_game_objects_[i];

			//update the object
			playerObject->Update(delta_time);

			//chenge player sprite
			if (playerObject->getInvincible()) {
				playerObject->SetTexture(tex_[9]);
			}
			else {
				playerObject->SetTexture(tex_[0]);
			}

			//handle player death
			if (playerObject->getTimeOfDeath() != NULL) {
				glm::vec3 tmpPos = playerObject->GetPosition();
				player_game_objects_.erase(player_game_objects_.begin());

				//creates a temp object on death
				TempGameObject* tmp = new TempGameObject(tmpPos, sprite_, &sprite_shader_, tex_[7], 3);
				tmp->setPlayerExplosion(true);

				temp_game_objects_.push_back(tmp);
				gameOver = true;
			}

			// Check for collision between player with enemy objects
			for (int j = 0; j < enemy_game_objects_.size(); j++) {
				EnemyGameObject* enemyObject = enemy_game_objects_[j];
				float distance = glm::length(enemyObject->GetPosition() - playerObject->GetPosition());

				//if distance is below a threshold, update the health
				if (distance < 0.8f && enemyObject->getHealth() > 0) {
					if (!playerObject->getInvincible()) {
						playerObject->setHealth(playerObject->getHealth() - 1);
					}
					enemyObject->setHealth(enemyObject->getHealth() - 1);
				}
			}

			// Check for collision between player with collectible objects
			for (int j = 0; j < collectible_game_objects_.size(); j++) {
				CollectibleObject* collectibleObject = collectible_game_objects_[j];
				float distance = glm::length(collectibleObject->GetPosition() - playerObject->GetPosition());

				if (distance < 0.8f) {
					playerObject->setNumCollectibles(playerObject->getNumCollectibles() + 1);
					collectibleObject->setHealth(collectibleObject->getHealth() - 1);
				}
			}

			//render the object
			playerObject->Render(view_matrix, current_time_);
		}

		for (int i = 0; i < enemy_game_objects_.size(); i++) {
			//get the enemy
			EnemyGameObject* enemyObject = enemy_game_objects_[i];

			//update the object
			enemyObject->Update(delta_time);

			//deletes objects requesting deletion. skips collision detection
			if (enemyObject->getDelStatus()) {
				//now greyscales instead of creating a boom

				//glm::vec3 tmpPos = enemyObject->GetPosition();
				enemy_game_objects_.erase(enemy_game_objects_.begin() + i);
				//temp_game_objects_.push_back(new TempGameObject(tmpPos, sprite_, &sprite_shader_, tex_[7], 3));
			}

			if (!gameOver) {
				PlayerGameObject* playerObject = player_game_objects_[0];
				// Compute distance between enemy and player
				float distance = glm::length(enemyObject->GetPosition() - playerObject->GetPosition());

				// If distance is below a threshold, the player is in sight
				if (distance < 1.6 && !enemyObject->getStationary()) {
					enemyObject->setPatrolling(false);
					enemyObject->setMoving(true);
					enemyObject->setTargetLoc(playerObject->GetPosition());
				}
				else if (distance > 1.6 && !enemyObject->getStationary()) {
					enemyObject->setPatrolling(true);
					enemyObject->setMoving(false);
				}
			}
			//render the object
			enemyObject->Render(view_matrix, current_time_);
		}

		for (int i = 0; i < collectible_game_objects_.size(); i++) {
			//get the collectible
			CollectibleObject* collectibleObject = collectible_game_objects_[i];

			//update the object
			collectibleObject->Update(delta_time);

			//deletes objects requesting deletion. skips collision detection
			if (collectibleObject->getDelStatus()) {
				glm::vec3 tmpPos = collectibleObject->GetPosition();
				collectible_game_objects_.erase(collectible_game_objects_.begin() + i);
			}

			//render the object
			collectibleObject->Render(view_matrix, current_time_);
		}

		for (int i = 0; i < temp_game_objects_.size(); i++) {
			//get the temporary effect
			TempGameObject* tmpObject = temp_game_objects_[i];

			//update the object
			tmpObject->Update(delta_time);

			bool isPlayerExplosion = tmpObject->getPlayerExplosion();

			//deletes objects requesting deletion. skips collision detection
			if (tmpObject->getDelStatus()) {
				temp_game_objects_.erase(temp_game_objects_.begin() + i);
				if (gameOver && isPlayerExplosion) {
					std::cout << "GAME OVER";
					exit(0);
				}
			}

			//render the object
			tmpObject->Render(view_matrix, current_time_);
		}

		for (int i = 0; i < obstacles_.size(); i++) {
			//get the temporary obstacle object
			ObstacleObject* obstacle = obstacles_[i];

			//update the object
			obstacle->Update(delta_time);

			//deletes objects requesting deletion. skips collision detection
			if (obstacle->getDelStatus()) {
				obstacles_.erase(obstacles_.begin() + i);
			}

			//render the object
			obstacle->Render(view_matrix, current_time_);
		}

		for (int i = 0; i < ally_bullets_.size(); i++) {
			//get the temporary effect
			BulletGameObject* bullet = ally_bullets_[i];

			//update the object
			bullet->Update(delta_time);

			//Handle collision with obstacles
			for (int j = 0; j < obstacles_.size(); j++)
			{
				ObstacleObject* obstacle = obstacles_[j];

				glm::vec3 curpos = bullet->GetPosition();
				glm::vec3 nextpos = bullet->GetVelocity();
				nextpos *= delta_time;
				nextpos += curpos;

				//Get the obstacle position, length, and rotation angle
				glm::vec3 obspos = obstacle->GetPosition();
				float obslength = obstacle->GetScalex();
				float obsangle = obstacle->getRotation();

				//vector from bullet to next position
				glm::vec3 ray = nextpos - curpos;
				
				//Create a vector for the obstacle
				glm::vec3 obsVector = obstacle->getEndPos() - obstacle->getStartPos();

				//asx = curpos.x,	asy = curpos.y,		Adx = ray.x,			Ady = ray.y
				//bsx = obspos.x,	bsy = obspos.y,		Bdx = obsVector.x,		Bdy = obsVector.y

				//Calculate the lengths of each vector needed for the rays to intersect
				float u = (curpos.x * obsVector.x + obsVector.y * obspos.x - obspos.y * obsVector.x - obsVector.y * curpos.x)
					/ (curpos.x * obsVector.y - ray.y * obsVector.x);
				float v = (curpos.x - obspos.x + (ray.x * u)) / obsVector.x;

				std::cout << "(u: " << u << ", v: " << v << ")" << std::endl;

				//Check if both lengths are less than 1 and greater than 0
				if (u <= 1 && u > 0 && v <= 1 && v > 0)
				{					
					//Set the bullet's position to be against the wall
					glm::vec3 intersect;
					intersect.x = curpos.x + (ray.x * u);
					intersect.y = curpos.y + (ray.y * u);
					intersect.z = 0.0f;
					bullet->SetPosition(intersect);

					//Ricochet the bullet
					bullet->Ricochet(obstacle);
				}
			}

			//Handle collision with enemies
			for (int j = 0; j < enemy_game_objects_.size(); j++) {
				EnemyGameObject* enemyObject = enemy_game_objects_[j];

				glm::vec3 curpos = bullet->GetPosition();
				glm::vec3 nextpos = bullet->GetVelocity();
				nextpos *= delta_time;
				nextpos += curpos;

				glm::vec3 enemypos = enemyObject->GetPosition();
				//get the circle radius. Assume scale x = scale y.
				float enemyscale = enemyObject->GetScalex();

				//vector from bullet to next position
				glm::vec3 ray = nextpos - curpos;
				//vector from bullet to enemy
				glm::vec3 distFromEnemy = enemypos - curpos;

				float a = glm::dot(ray, ray);
				float b = 2 * glm::dot(ray, (curpos - enemypos));
				float c = glm::dot(distFromEnemy, distFromEnemy) - (enemyscale * enemyscale);

				if (((b * b) - (4 * a * c)) > 0) {
					//detected an enemy on the line of travel
					float u1 = (-b + sqrt((b * b) - (4 * a * c))) / (2 * a);
					float u2 = (-b - sqrt((b * b) - (4 * a * c))) / (2 * a);

					//if the hitbox intersects the bullet, register a hit
					if (((u1 >= 0 && u1 <= 1) || (u2 >= 0 && u2 <= 1)) && enemyObject->getTimeOfDeath() == NULL) {
						enemyObject->setHealth(enemyObject->getHealth() - bullet->getDamage());
						bullet->setDelStatus(true);
					}
				}
				float distance = glm::length(enemyObject->GetPosition() - bullet->GetPosition());
			}


			//deletes objects requesting deletion. skips collision detection
			if (bullet->getDelStatus()) {
				//delete bullet particles if needed
				for (int j = 0; j < bullet_effects_.size(); j++) {
					//get the effect
					ConeParticleSystem* effect = bullet_effects_[j];

					if (effect->getParent() == bullet) {
						bullet_effects_.erase(bullet_effects_.begin() + j);
					}

				}

				ally_bullets_.erase(ally_bullets_.begin() + i);
			}

			//render the object
			bullet->Render(view_matrix, current_time_);
		}

		for (int i = 0; i < enemy_bullets_.size(); i++) {
			//get the temporary effect
			BulletGameObject* bullet = enemy_bullets_[i];

			//update the object
			bullet->Update(delta_time);

			//deletes objects requesting deletion. skips collision detection
			if (bullet->getDelStatus()) {
				enemy_bullets_.erase(enemy_bullets_.begin() + i);
			}

			//render the object
			bullet->Render(view_matrix, current_time_);
		}

		//update the blade
		blade->Update(delta_time);

		//only render the blade if there is a player
		if (player_game_objects_.size() != 0) {
			blade->Render(view_matrix, current_time_);
		}

		for (int i = 0; i < background_game_objects_.size(); i++) {
			//get the background
			GameObject* background = background_game_objects_[i];

			//update the object
			background->Update(delta_time);

			//render the object
			background->Render(view_matrix, current_time_);
		}

		//render player particles
		for (int i = 0; i < player_effects.size(); i++) {
			//get the effect
			GameObject* effect = player_effects[i];

			//update the object
			effect->Update(delta_time);

			//delete the effects if there is no player
			if (player_game_objects_.size() == 0) {
				player_effects.erase(player_effects.begin() + i);
			}
			else {
				//render the object otherwise
				effect->Render(view_matrix, current_time_);
			}
		}

		//render bullet particles
		for (int i = 0; i < bullet_effects_.size(); i++) {
			//get the effect
			GameObject* effect = bullet_effects_[i];

			//update the object
			effect->Update(delta_time);

			effect->Render(view_matrix, current_time_);

		}

	}

	void Game::Controls(double delta_time)
	{
		if (!gameOver) {
			// Get player game object
			PlayerGameObject* player = player_game_objects_[0];
			// Get current velocity position and rotation
			glm::vec3 curvel = player->GetVelocity();
			glm::vec3 curpos = player->GetPosition();
			float currot = player->getRotation();

			// Set standard forward and right directions
			glm::vec3 dir = glm::vec3(cos(currot + 3.1415 / 2), sin(currot + 3.1415 / 2), 0.0);
			glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);

			// Adjust motion increment based on a given speed
			float speed = 2.5;
			float rotSpeed = 5;
			float motion_increment = speed * delta_time;
			float rotation_increment = rotSpeed * delta_time;

			// Check for player input and make changes accordingly
			if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
				//increases speed in direction pointed
				player->SetVelocity(curvel + motion_increment * dir);
			}
			if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS && glm::length(curvel) > 0) {
				//decreases speed in direction going(up to 0)
				player->SetVelocity(curvel - motion_increment * glm::normalize(curvel));
			}
			if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
				//rotate right
				player->setRotation(currot - rotation_increment);
			}
			if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
				//rotate left
				player->setRotation(currot + rotation_increment);
			}
			if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS) {
				//fire ally bullet every 1 seconds
				if (glfwGetTime() > lastFireTime + 1) {
					lastFireTime = glfwGetTime();
					ally_bullets_.push_back(new BulletGameObject(curpos, sprite_, &sprite_shader_, tex_[10], currot + 3.1415 / 2, 1, false));

					// Setup particle system
					ConeParticleSystem* bulletParticles = new ConeParticleSystem(glm::vec3(0.0f, -0.5f, 0.0f), bullet_particles_, &bullet_particle_shader_, tex_[4], ally_bullets_[ally_bullets_.size() - 1]);
					bulletParticles->SetScale(0.1);
					bullet_effects_.push_back(bulletParticles);
				}
			}
			if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			{
				//Begin drawing a wall if there are currently less than the maximum number of walls and another wall is not currently being drawn
				if (numWalls < MAX_WALLS && !drawingWall)
				{
					drawingWall = true;
					
					//Record the position of the mouse at the beginning of the drawing
					double* x = new double();
					double* y = new double();
					glfwGetCursorPos(window_, x, y);
					wallStartPos.x = *x;
					wallStartPos.y = *y;
					wallStartPos.z = 0;
					ConvertToWorldCoords(wallStartPos);
				}
			}
			if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
			{
				//Finish drawing a wall if a wall is currently being drawn
				if (drawingWall)
				{
					drawingWall = false;

					//Record the position of the mouse at the end of the drawing
					double* x = new double();
					double* y = new double();
					glfwGetCursorPos(window_, x, y);
					glm::vec3 wallEndPos;
					wallEndPos.x = *x;
					wallEndPos.y = *y;
					wallEndPos.z = 0;
					ConvertToWorldCoords(wallEndPos);

					//Check the length of the wall
					glm::vec3 wallVector = wallEndPos - wallStartPos;
					double length = sqrt(pow(wallVector.x, 2) + pow(wallVector.y, 2));
					
					if (length >= MIN_WALL_LENGTH && length <= MAX_WALL_LENGTH)
					{						
						//Calculate the position of the wall
						wallVector *= 0.5;
						glm::vec3 wallPos = wallStartPos + wallVector;

						//Calculate the angle of the wall
						float wallAngle = 0;
						
						if (wallVector.x != 0)
						{
							wallAngle = atan(wallVector.y/wallVector.x);
						}
						else
						{
							
						}

						//Create the wall
						obstacles_.push_back(new ObstacleObject(wallPos, sprite_, &sprite_shader_, tex_[12], wallStartPos, wallEndPos, length, wallAngle));
						++numWalls;
					}
				}
			}
			if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window_, true);
			}
		}
	}

	void Game::ConvertToWorldCoords(glm::vec3& pos)
	{
		//Create a 4x4 matrix to represent the position on the screen, reducing the coordinates to a range of -1 to 1
		pos.x -= window_width_g / 2;
		pos.x /= window_width_g / 2;
		pos.y -= window_width_g;
		pos.y *= -1;
		pos.y -= window_height_g / 2;
		pos.y /= window_height_g / 2;

		//Divide by the camera zoom
		pos /= CAMERA_ZOOM;

		//Get the player's position
		glm::vec3 playerPos = -player_game_objects_[0]->GetPosition();

		//Translate by the player's position
		pos += playerPos;
		
	}

} // namespace game
