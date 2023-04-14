How to play:
	Controls:
		W to accelarate, S to decellarate(to 0). A and D to steer.
		To shoot, hold space
			To switch weapons, press Tab
		To create a wall, hold left click to create a start point, and release to create
		To quit the game, press Q
	Objective:
		Reach a score of 25, then defeat the boss to win the game. 
Project Requirements:
	Game Mechanics:
		Gameplay:
			As the checklist does not mention gameplay in this section, it shall be ommited.
		Finishing Condition:
			The player must defeat waves of enemies, each with varying score(detailed below). Upon reaching
			a score of 25, the next wave will consist of a boss, which upon defeat finishes 
			the game.
			
			The boss has a weak point in the middle, taking double damage.
	Enemies:
		Kamakaze:
			Texture: Orb
			Weapon: None
			Behaviour: Attepts to move directly towards the player.
			Damage: 5
			Score: 1
		Stationary:
			Texture: Skull
			Weapon: Forked Bullets
			Behaviour: Tries to move towards a point on the current screen. Upon reaching that point, fires
			its weapon at the player.
			Damage: 4 per bullet
			Score: 3
		Moving:
			Texture: Rat.png
			Weapon: Slow firing bullets
			Behaviour: Tries to move towards a point on the current screen. Upon reaching within a radius
				of that point, orbits the point and fires its weapon at the player
			Damage: 2
			Score: 5
		Boss:
			Texture: Octopus with two tentacles
			Weapon: Fast firing downwards shots. One on each arm.
			Behaviour: Moves in a sinusoidal pattern at the top of the screen, moving with the player
			Damage: 3
			Score: 30
				Destroying each arm seperately gives an additional 10
	Weapons:
		Triple Shot:
			Upon ricochet off a wall, the bullet will split into 3
			This bullet is brown
		Standard Shot:
			Upon ricochet off a wall, the bullet will deal double damage(10 instead of 5)
			This bullet is purple
	Collectibles:
		Upon the death of an enemy(when its grey texture is deleted), a random collectible will spawn
		Health(Green Cross):
			40% chance to spawn
			Adds 5 to player health
		Wall(White Line):
			10% chance to spawn
			Adds an extra wall to use
		Money:
			30% chance to spawn
			Upon collecting 5, the player is invincible for a short time
	Movement/Transformations:
		Some objects are moved with parametric motion, such as enemies. The player is handled with 
		physics based movement.
	Collision detection:
		Upon colliding with an enemy, the player takes 5 damage. This is used mainly by the kamakaze,
		however is also a penalty for notn moving out of the way of another enemy.
		Bullets use ray-circle collision.
	Game World:
		The camera follows the player across the map.
		The background is tiled ar random.
	Particle System:
		Upon killing an enemy with a bullet, they explode.
		The player has a stream of fire particles attached
	UI:
		The HUD displays the current score, weapon, health, and number of walls available for use
	Advanced Method:
		Collision resolution with walls, as bulets ricochet off them.
	Code readabiulity and Organization:
		Comments are provided to explain more complicated methods and calculations.
	Bonus:
		The boss has hierarchical transformations, with the player(link 1) connected to the boss(link 2)
		which is connected to the boss arms(link 3)

Github with changes can be seen here:
https://github.com/Draco-28/COMP-2501-Final-Project