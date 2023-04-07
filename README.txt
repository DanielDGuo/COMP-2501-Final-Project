Developed on a Win11 OS system

You will have to set Assignment4 as the startup.	

NEW:
	Added bullets that fire 10 times a second when space is held
		New bullet_game_object.[h/cc] files
		Deleted automatically after 3 seconds
			found in the source file update function
	Enemies still spawn in random places
		Found in the game.cc file
		When circling enemies are initialized they spawn at random places
	Bullets damage enemies
		Logic in game source code
		Iterates over ally bullets, and then over enemies to find ray-circle collision
	Blade added as the flavour_game_object.[h/cpp]
		Uses hierarchical transformation
			Logic is similar to particle system render function
	Bullet particles added
		Added as BulletParticle class in bullet_particles.[h/cpp]
		Adjusted copy of player particles
			tmod divided by 2 on line 41 for longer cone
			theta multiplied by 0.05f instead of 0.13f on line 57 for narrower cone
		Scale is half that of the player object
		Uses a new "bullet_fragment_shader" to colour the bullet differently

BUGS:
	Did not implement explosion effects
	Bullet Particles are not *exactly* at the back of the bullet
		Solution: translate them towards the intended position