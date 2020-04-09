#include <time.h>
#include "SuperMario.h"

#pragma warning (disable: 4267)

/*
Version: 1.0.4
Animations: Small,Super,Invicible (Left,right,jump)
Enemys: Gooma,Koopas,
Bonus scene: No entering animation
Sounds: Yes
Bricks destruction: No
Destroy enemys when hitting bricks: Yes (Can be better)
Error checking for allegro: Yes
Assertions: No
Memory leaks: Some
Code cleanup: Some
Refactoring: Very small
Randomness on question bricks: Yes (60% coin, 12% green mushrrom, 12% red mushroom, 16%, starman)
Game loading configuration: 
	Number of lifes: Yes
	Setting mario size: Yes
	Ending time: Yes
Bugs:
	Filter grid motion: Only works for height = 10 and width = 15
*/

int main() {

	srand(time(NULL));

	string tile_path = "media/TileLayer.csv";
	string bitmap_path = "media/super_mario_tiles.png";
	string back_path = "media/BackGroundLayer.csv";
	Engine engine(tile_path, bitmap_path, back_path);
	superMario::SuperMario supermario(engine);
	supermario.Main();

	return 0;
}