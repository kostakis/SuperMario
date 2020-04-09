#include "AI_Initialization.h"
#include "CollisionFunctions.h"
#include "GameObject.h"
#include "Coin.h"

int whatCollision(const Sprite* s1, const Sprite* s2)
{
	int x1 = s1->GetX();
	int y1 = s1->GetY();
	int width1 = 15;
	int height1 = 10;

	int x2 = s2->GetX();
	int y2 = s2->GetY();
	int width2 = 15;
	int height2 = 10;

	bool condition1 = x1 + (width1 - 1) == x2;
	bool condtion2 = x2 + (width2 - 1) == x1;
	bool condtion3 = x2 - (width2 - 1) == x1;
	bool condtion4 = x1 - (width1 - 1) == x2;
	bool condtion5 = x1 == x2;
	if (y1 < y2) // Up Collision
	{
		return 0;
	}
	else {//Side Collision
		return 1;
	}
}

void CreateTurtles(const Game& game)
{
	AnimationFilm* koopaFilm = AnimationFilmHolder::GetInstance().GetFilm("KOOPA_TROOPA");

	Enemy* kpFirst = new KOOPA_TROOPA(ENEMY_DIRECTION::RIGHT, 1550, 545, koopaFilm);
	Enemy* kpSecond = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 1808, 545, koopaFilm);
	Enemy* kp3 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 3184, 288, koopaFilm);

	Enemy* kp4 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 3584, 545, koopaFilm);

	Enemy* kp5 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 4944, 380, koopaFilm);
	Enemy* kp6 = new KOOPA_TROOPA(ENEMY_DIRECTION::RIGHT, 5216, 380, koopaFilm);

	Enemy* kp6_1 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 2368, 545, koopaFilm);

	Enemy* kp7 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 4096, 415, koopaFilm);
	Enemy* kp8 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 4080, 415, koopaFilm);

	Enemy* kp10 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 5856, 545, koopaFilm);

	Enemy* kp11 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 4704, 545, koopaFilm);
	Enemy* kp12 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 5120, 545, koopaFilm);
	Enemy* kp13 = new KOOPA_TROOPA(ENEMY_DIRECTION::LEFT, 5344, 350, koopaFilm);

	auto& turtleAll = SpriteManager::GetInstance().getTypeList("KOOPA_TROOPA");
	for (auto* i : turtleAll) { 
		CollisionChecker::GetInstance().Register(game.getPlayer(), i, function_collision_turtle);
	}


	for (auto* i : turtleAll) {
		for (auto* j : turtleAll) {
			if (i->GetX() != j->GetX()) {
				CollisionChecker::GetInstance().Register(i, j, function_collision_turtle_turtle);
				CollisionChecker::GetInstance().Register(j, i, function_collision_turtle_turtle);
			}
		}
	}

	CollisionChecker::GetInstance().Register(kp3, kp4, function_collision_turtle_turtle);
	CollisionChecker::GetInstance().Register(kp5, kp6, function_collision_turtle_turtle);
	CollisionChecker::GetInstance().Register(kp7, kp8, function_collision_turtle_turtle);


	auto& goombas_all = SpriteManager::GetInstance().getTypeList("GOOMBA_BROWN");
	for (auto* i : turtleAll) {
		for (auto* j : goombas_all) {
			CollisionChecker::GetInstance().Register(i, j, function_collision_turtle_goomba);
		}
	}
}

void CreateGoomba(const Game& game)
{
	AnimationFilm* goombaFilm = AnimationFilmHolder::GetInstance().GetFilm("GOOMBA_BROWN");
	Enemy* goombaOne = new Goomba(ENEMY_DIRECTION::LEFT, 250, 548, goombaFilm);
	Enemy* goombaTwo = new Goomba(ENEMY_DIRECTION::LEFT, 265, 548, goombaFilm);
	Enemy* goombaThree = new Goomba(ENEMY_DIRECTION::LEFT, 950, 548, goombaFilm);
	Enemy* goombaFour = new Goomba(ENEMY_DIRECTION::LEFT, 1400, 548, goombaFilm);
	Enemy* goombaFive = new Goomba(ENEMY_DIRECTION::LEFT, 1380, 548, goombaFilm);
	Enemy* goomba6 = new Goomba(ENEMY_DIRECTION::LEFT, 2784, 448, goombaFilm);
	Enemy* goomba7 = new Goomba(ENEMY_DIRECTION::LEFT, 2800, 448, goombaFilm);

	Enemy* goomba9 = new Goomba(ENEMY_DIRECTION::LEFT, 1936, 448, goombaFilm);
	Enemy* goomba8 = new Goomba(ENEMY_DIRECTION::LEFT, 1952, 448, goombaFilm);

	Enemy* goomba10 = new Goomba(ENEMY_DIRECTION::RIGHT, 4816, 548, goombaFilm);
	Enemy* goomba11 = new Goomba(ENEMY_DIRECTION::RIGHT, 4831, 548, goombaFilm);

	Enemy* goomba12 = new Goomba(ENEMY_DIRECTION::RIGHT, 5488, 560, goombaFilm);
	Enemy* goomba13 = new Goomba(ENEMY_DIRECTION::RIGHT, 5504, 560, goombaFilm);

	CollisionChecker::GetInstance().Register(goomba10, goomba11, function_collicion_two_goom);
	CollisionChecker::GetInstance().Register(goomba8, goomba9, function_collicion_two_goom);
	CollisionChecker::GetInstance().Register(goombaOne, goombaTwo, function_collicion_two_goom);
	CollisionChecker::GetInstance().Register(goombaFour, goombaFive, function_collicion_two_goom);
	CollisionChecker::GetInstance().Register(goomba6, goomba7, function_collicion_two_goom);
	CollisionChecker::GetInstance().Register(goomba12, goomba13, function_collicion_two_goom);
	/*CollisionChecker::GetInstance().Register(goombaSix, goombaSeven, function_collicion_two_goom);*/

	auto& goombas_all = SpriteManager::GetInstance().getTypeList("GOOMBA_BROWN");
	for (auto* i : goombas_all) {
		CollisionChecker::GetInstance().Register(game.getPlayer(), i, function_collision_goomba);
	}
}

void CreateBricks(const Game& game)
{
	/*Simple Bricks*/
	AnimationFilm* brickFilm = AnimationFilmHolder::GetInstance().GetFilm("SIMPLE_BRICK");
	GameObject* simpleBrickOne = new SimpleBrick(208, 518, brickFilm);
	GameObject* simpleBrick2 = new SimpleBrick(800, 518, brickFilm);
	GameObject* simpleBrick3 = new SimpleBrick(816, 518, brickFilm);
	GameObject* simpleBrick4 = new SimpleBrick(832, 518, brickFilm);
	GameObject* simpleBrick5 = new SimpleBrick(848, 518, brickFilm);
	GameObject* simpleBrick6 = new SimpleBrick(864, 518, brickFilm);
	GameObject* simpleBrick7 = new SimpleBrick(880, 518, brickFilm);

	GameObject* simpleBrick8 = new SimpleBrick(1680, 518, brickFilm);
	GameObject* simpleBrick9 = new SimpleBrick(1696, 518, brickFilm);
	GameObject* simpleBrick10 = new SimpleBrick(1712, 518, brickFilm);
	GameObject* simpleBrick11 = new SimpleBrick(1728, 518, brickFilm);

	GameObject* simpleBrick13 = new SimpleBrick(1808, 470, brickFilm);
	GameObject* simpleBrick14 = new SimpleBrick(1824, 470, brickFilm);
	GameObject* simpleBrick15 = new SimpleBrick(1840, 470, brickFilm);
	GameObject* simpleBrick16 = new SimpleBrick(1856, 470, brickFilm);
	GameObject* simpleBrick17 = new SimpleBrick(1872, 470, brickFilm);
	GameObject* simpleBrick18 = new SimpleBrick(1888, 470, brickFilm);
	GameObject* simpleBrick19 = new SimpleBrick(1904, 470, brickFilm);
	GameObject* simpleBrick20 = new SimpleBrick(1920, 470, brickFilm);
	GameObject* simpleBrick21 = new SimpleBrick(1936, 470, brickFilm);
	GameObject* simpleBrick22 = new SimpleBrick(1952, 470, brickFilm);
	GameObject* simpleBrick23 = new SimpleBrick(1968, 470, brickFilm);
	GameObject* simpleBrick24 = new SimpleBrick(1984, 470, brickFilm);
	GameObject* simpleBrick25 = new SimpleBrick(2000, 470, brickFilm);
	GameObject* simpleBrick26 = new SimpleBrick(2016, 470, brickFilm);

	GameObject* simpleBrick1222 = new SimpleBrick(2736, 486, brickFilm);
	GameObject* simpleBrick1333 = new SimpleBrick(2752, 486, brickFilm);
	GameObject* simpleBrick1444 = new SimpleBrick(2768, 486, brickFilm);
	GameObject* simpleBrick1555 = new SimpleBrick(2784, 486, brickFilm);

	GameObject* simpleBrick27 = new SimpleBrick(2672, 486, brickFilm);
	GameObject* simpleBrick28 = new SimpleBrick(2688, 486, brickFilm);
	GameObject* simpleBrick29 = new SimpleBrick(2704, 486, brickFilm);
	GameObject* simpleBrick30 = new SimpleBrick(2720, 486, brickFilm);

	GameObject* simpleBrick31 = new SimpleBrick(2736, 422, brickFilm);
	GameObject* simpleBrick32 = new SimpleBrick(2752, 422, brickFilm);
	GameObject* simpleBrick33 = new SimpleBrick(2768, 422, brickFilm);
	GameObject* simpleBrick34 = new SimpleBrick(2784, 422, brickFilm);

	GameObject* simpleBrick35 = new SimpleBrick(2800, 486, brickFilm);
	GameObject* simpleBrick36 = new SimpleBrick(2816, 486, brickFilm);
	GameObject* simpleBrick37 = new SimpleBrick(2832, 486, brickFilm);
	GameObject* simpleBrick38 = new SimpleBrick(2848, 486, brickFilm);
	GameObject* simpleBrick39 = new SimpleBrick(2864, 486, brickFilm);
	GameObject* simpleBrick40 = new SimpleBrick(2880, 486, brickFilm);
	GameObject* simpleBrick41 = new SimpleBrick(2896, 486, brickFilm);
	GameObject* simpleBrick42 = new SimpleBrick(2912, 486, brickFilm);
	GameObject* simpleBrick43 = new SimpleBrick(2928, 486, brickFilm);
	GameObject* simpleBrick44 = new SimpleBrick(2944, 486, brickFilm);
	GameObject* simpleBrick45 = new SimpleBrick(2960, 486, brickFilm);

	GameObject* simpleBrick46 = new SimpleBrick(2928, 406, brickFilm);
	GameObject* simpleBrick47 = new SimpleBrick(2944, 406, brickFilm);
	GameObject* simpleBrick48 = new SimpleBrick(2960, 406, brickFilm);

	GameObject* simpleBrick808 = new SimpleBrick(2928, 406, brickFilm);
	GameObject* simpleBrick818 = new SimpleBrick(2944, 406, brickFilm);
	GameObject* simpleBrick828 = new SimpleBrick(2960, 406, brickFilm);

	GameObject* simpleBrick49 = new SimpleBrick(2832, 374, brickFilm);
	GameObject* simpleBrick50 = new SimpleBrick(2848, 374, brickFilm);
	GameObject* simpleBrick51 = new SimpleBrick(2864, 374, brickFilm);
	GameObject* simpleBrick52 = new SimpleBrick(2880, 374, brickFilm);
	GameObject* simpleBrick53 = new SimpleBrick(2896, 374, brickFilm);

	GameObject* simpleBrick54 = new SimpleBrick(2976, 374, brickFilm);
	GameObject* simpleBrick55 = new SimpleBrick(2992, 374, brickFilm);
	GameObject* simpleBrick56 = new SimpleBrick(3008, 374, brickFilm);

	GameObject* simpleBrick57 = new SimpleBrick(3040, 342, brickFilm);
	GameObject* simpleBrick58 = new SimpleBrick(3056, 342, brickFilm);
	GameObject* simpleBrick59 = new SimpleBrick(3072, 342, brickFilm);

	GameObject* simpleBrick60 = new SimpleBrick(3088, 310, brickFilm);
	GameObject* simpleBrick61 = new SimpleBrick(3104, 310, brickFilm);
	GameObject* simpleBrick62 = new SimpleBrick(3120, 310, brickFilm);
	GameObject* simpleBrick63 = new SimpleBrick(3136, 310, brickFilm);
	GameObject* simpleBrick64 = new SimpleBrick(3148, 310, brickFilm);
	GameObject* simpleBrick65 = new SimpleBrick(3164, 310, brickFilm);
	GameObject* simpleBrick66 = new SimpleBrick(3180, 310, brickFilm);
	GameObject* simpleBrick67 = new SimpleBrick(3196, 310, brickFilm);
	GameObject* simpleBrick68 = new SimpleBrick(3212, 310, brickFilm);
	GameObject* simpleBrick69 = new SimpleBrick(3228, 310, brickFilm);
	GameObject* simpleBrick70 = new SimpleBrick(3244, 310, brickFilm);
	GameObject* simpleBrick71 = new SimpleBrick(3260, 310, brickFilm);
	GameObject* simpleBrick72 = new SimpleBrick(3228, 294, brickFilm);
	GameObject* simpleBrick73 = new SimpleBrick(3244, 294, brickFilm);
	GameObject* simpleBrick74 = new SimpleBrick(3260, 294, brickFilm);
	GameObject* simpleBrick75 = new SimpleBrick(3212, 294, brickFilm);

	GameObject* simpleBrick76 = new SimpleBrick(3280, 262, brickFilm);
	GameObject* simpleBrick77 = new SimpleBrick(3296, 262, brickFilm);
	GameObject* simpleBrick78 = new SimpleBrick(3312, 262, brickFilm);
	GameObject* simpleBrick79 = new SimpleBrick(3328, 262, brickFilm);

	GameObject* gdsfgdfgg = new SimpleBrick(4096, 454, brickFilm);

	GameObject* simpleBrick83 = new SimpleBrick(2992, 518, brickFilm);
	GameObject* simpleBrick84 = new SimpleBrick(3008, 518, brickFilm);
	GameObject* simpleBrick85 = new SimpleBrick(3024, 518, brickFilm);
	GameObject* simpleBrick86 = new SimpleBrick(3040, 518, brickFilm);
	GameObject* simpleBrick87 = new SimpleBrick(3056, 518, brickFilm);
	GameObject* simpleBrick88 = new SimpleBrick(3072, 518, brickFilm);
	GameObject* simpleBrick89 = new SimpleBrick(3088, 518, brickFilm);
	GameObject* simpleBrick90 = new SimpleBrick(3104, 518, brickFilm);

	GameObject* simpleBrick91 = new SimpleBrick(3056, 502, brickFilm);
	GameObject* simpleBrick92 = new SimpleBrick(3072, 502, brickFilm);
	GameObject* simpleBrick93 = new SimpleBrick(3088, 502, brickFilm);
	GameObject* simpleBrick94 = new SimpleBrick(3104, 502, brickFilm);

	GameObject* simpleBrick96 = new SimpleBrick(3808, 486, brickFilm);
	GameObject* simpleBrick97 = new SimpleBrick(3824, 486, brickFilm);
	GameObject* simpleBrick98 = new SimpleBrick(3840, 486, brickFilm);
	GameObject* simpleBrick99 = new SimpleBrick(3856, 486, brickFilm);
	GameObject* simpleBrick100 = new SimpleBrick(3872, 486, brickFilm);
	GameObject* simpleBrick101 = new SimpleBrick(3888, 486, brickFilm);
	GameObject* simpleBrick102 = new SimpleBrick(3904, 486, brickFilm);
	GameObject* simpleBrick103 = new SimpleBrick(3920, 486, brickFilm);
	GameObject* simpleBrick104 = new SimpleBrick(3936, 486, brickFilm);
	GameObject* simpleBrick105 = new SimpleBrick(3952, 486, brickFilm);
	GameObject* simpleBrick106 = new SimpleBrick(3968, 486, brickFilm);

	GameObject* simpleBrick108 = new SimpleBrick(4016, 454, brickFilm);
	GameObject* simpleBrick109 = new SimpleBrick(4032, 454, brickFilm);
	GameObject* simpleBrick110 = new SimpleBrick(4048, 454, brickFilm);
	GameObject* simpleBrick111 = new SimpleBrick(4064, 454, brickFilm);
	GameObject* simpleBrick112 = new SimpleBrick(4080, 454, brickFilm);

	GameObject* simpleBrick1122 = new SimpleBrick(4608, 502, brickFilm);
	GameObject* simpleBrick114 = new SimpleBrick(4624, 502, brickFilm);
	GameObject* simpleBrick115 = new SimpleBrick(4640, 502, brickFilm);
	GameObject* simpleBrick116 = new SimpleBrick(4656, 502, brickFilm);
	GameObject* simpleBrick117 = new SimpleBrick(4672, 502, brickFilm);
	GameObject* simpleBrick118 = new SimpleBrick(4688, 502, brickFilm);
	GameObject* simpleBrick119 = new SimpleBrick(4704, 502, brickFilm);
	GameObject* simpleBrick120 = new SimpleBrick(4720, 502, brickFilm);
	GameObject* simpleBrick121 = new SimpleBrick(4736, 502, brickFilm);
	GameObject* simpleBrick122 = new SimpleBrick(4752, 502, brickFilm);
	GameObject* simpleBrick123 = new SimpleBrick(4768, 502, brickFilm);
	GameObject* simpleBrick124 = new SimpleBrick(4784, 502, brickFilm);

	GameObject* simpleBrick126 = new SimpleBrick(4832, 470, brickFilm);
	GameObject* simpleBrick127 = new SimpleBrick(4848, 470, brickFilm);

	GameObject* simpleBrick128 = new SimpleBrick(4848, 454, brickFilm);
	GameObject* simpleBrick129 = new SimpleBrick(4864, 454, brickFilm);

	GameObject* simpleBrick130 = new SimpleBrick(4864, 438, brickFilm);
	GameObject* simpleBrick131 = new SimpleBrick(4880, 438, brickFilm);

	GameObject* simpleBrick132 = new SimpleBrick(4880, 422, brickFilm);
	GameObject* simpleBrick133 = new SimpleBrick(4896, 422, brickFilm);

	GameObject* simpleBrick134 = new SimpleBrick(4896, 406, brickFilm);
	GameObject* simpleBrick135 = new SimpleBrick(4912, 406, brickFilm);
	GameObject* simpleBrick137 = new SimpleBrick(4944, 406, brickFilm);
	GameObject* simpleBrick138 = new SimpleBrick(4960, 406, brickFilm);
	GameObject* simpleBrick139 = new SimpleBrick(4976, 406, brickFilm);
	GameObject* simpleBrick140 = new SimpleBrick(4992, 406, brickFilm);
	GameObject* simpleBrick141 = new SimpleBrick(5008, 406, brickFilm);
	GameObject* simpleBrick142 = new SimpleBrick(5024, 406, brickFilm);
	GameObject* simpleBrick143 = new SimpleBrick(5040, 406, brickFilm);
	GameObject* simpleBrick144 = new SimpleBrick(5056, 406, brickFilm);
	GameObject* simpleBrick145 = new SimpleBrick(5072, 406, brickFilm);
	GameObject* simpleBrick146 = new SimpleBrick(5088, 406, brickFilm);
	GameObject* simpleBrick147 = new SimpleBrick(5104, 406, brickFilm);
	GameObject* simpleBrick148 = new SimpleBrick(5120, 406, brickFilm);
	GameObject* simpleBrick149 = new SimpleBrick(5136, 406, brickFilm);
	GameObject* simpleBrick150 = new SimpleBrick(5152, 406, brickFilm);
	GameObject* simpleBrick151 = new SimpleBrick(5168, 406, brickFilm);
	GameObject* simpleBrick152 = new SimpleBrick(5184, 406, brickFilm);
	GameObject* simpleBrick153 = new SimpleBrick(5200, 406, brickFilm);
	GameObject* simpleBrick154 = new SimpleBrick(5216, 406, brickFilm);
	GameObject* simpleBrick155 = new SimpleBrick(5232, 406, brickFilm);
	GameObject* simpleBrick156 = new SimpleBrick(5248, 406, brickFilm);

	GameObject* simpleBrick158 = new SimpleBrick(5248, 390, brickFilm);
	GameObject* simpleBrick157 = new SimpleBrick(4928, 390, brickFilm);
	GameObject* simpleBrick157_2 = new SimpleBrick(4928, 406, brickFilm);
	GameObject* simpleBrick157_1 = new SimpleBrick(2816, 374, brickFilm);

	GameObject* simpleBrick159 = new SimpleBrick(5296, 374, brickFilm);
	GameObject* simpleBrick160 = new SimpleBrick(5296, 358, brickFilm);

	GameObject* simpleBrick161 = new SimpleBrick(5312, 374, brickFilm);
	GameObject* simpleBrick162 = new SimpleBrick(5328, 374, brickFilm);
	GameObject* simpleBrick163 = new SimpleBrick(5344, 374, brickFilm);
	GameObject* simpleBrick164 = new SimpleBrick(5360, 374, brickFilm);
	GameObject* simpleBrick165 = new SimpleBrick(5376, 374, brickFilm);
	GameObject* simpleBrick166 = new SimpleBrick(5392, 374, brickFilm);
	GameObject* simpleBrick167 = new SimpleBrick(5408, 374, brickFilm);
	GameObject* simpleBrick168 = new SimpleBrick(5408, 358, brickFilm);

	auto& allSimpleBricks = SpriteManager::GetInstance().getTypeList("SIMPLE_BRICK");
	for (auto* i : allSimpleBricks) {
		CollisionChecker::GetInstance().Register(game.getPlayer(), i, function_collision_player_simpleBrick);
	}
	/*---------------------------------*/

	//Ta y itane 512 alla prepei na pane 518 gia na doulepsei to collision
	//Ta zwgrafizoyme opws san na itane sto 512.....
	//Oti brick valeis vres kanonika to ipsos stoy kai apla kane +6 otan ftiaxneis to object
	//Sta tiles  den allazei kati
}

void CreateCoins(const Game& game)
{
	AnimationFilm* coinFilm = AnimationFilmHolder::GetInstance().GetFilm("COIN");
	GameObject* coinOne = new Coin(220, 560, coinFilm);
	GameObject* coinTwo = new Coin(448, 528, coinFilm);
	GameObject* coinThree = new Coin(1328, 528, coinFilm);
	GameObject* coinFour = new Coin(1344, 528, coinFilm);
	GameObject* coinSix = new Coin(608, 528, coinFilm);
	GameObject* coinSeven = new Coin(624, 528, coinFilm);
	GameObject* coinEight = new Coin(1824, 528, coinFilm);
	GameObject* coinNine = new Coin(1843, 528, coinFilm);
	GameObject* coinTen = new Coin(1859, 528, coinFilm);

	GameObject* coinNine_1 = new Coin(2816, 432, coinFilm);
	GameObject* coinTen_1 = new Coin(2832, 432, coinFilm);
	GameObject* coinTen_2 = new Coin(2848, 432, coinFilm);

	GameObject* coinTen_11 = new Coin(3280, 224, coinFilm);
	GameObject* coinTen_22 = new Coin(3296, 224, coinFilm);
	GameObject* coinTen_222 = new Coin(3312, 224, coinFilm);

	GameObject* coin11 = new Coin(4944, 352, coinFilm);
	GameObject* coin12 = new Coin(4976, 352, coinFilm);
	GameObject* coin13 = new Coin(5008, 352, coinFilm);
	GameObject* coin14 = new Coin(5040, 352, coinFilm);
	GameObject* coin15 = new Coin(5072, 352, coinFilm);
	GameObject* coin16 = new Coin(5104, 352, coinFilm);
	GameObject* coin17 = new Coin(5136, 352, coinFilm);
	GameObject* coin18 = new Coin(5168, 352, coinFilm);
	GameObject* coin19 = new Coin(5200, 352, coinFilm);
	GameObject* coin20 = new Coin(5232, 352, coinFilm);
	GameObject* coin21 = new Coin(5264, 256, coinFilm);
	GameObject* coin22 = new Coin(5296, 256, coinFilm);
	GameObject* coin23 = new Coin(5328, 256, coinFilm);
	GameObject* coin24 = new Coin(5360, 256, coinFilm);

	GameObject* coin25 = new Coin(3792, 448, coinFilm);
	GameObject* coin26 = new Coin(3808, 448, coinFilm);
	GameObject* coin27 = new Coin(3824, 448, coinFilm);
	GameObject* coin28 = new Coin(3840, 448, coinFilm);
	GameObject* coin29 = new Coin(3856, 448, coinFilm);
	GameObject* coin30 = new Coin(3872, 448, coinFilm);
	GameObject* coin31 = new Coin(3888, 448, coinFilm);
	GameObject* coin32 = new Coin(3904, 448, coinFilm);
	GameObject* coin33 = new Coin(3920, 448, coinFilm);
	GameObject* coin34 = new Coin(3936, 448, coinFilm);
	GameObject* coin35 = new Coin(3952, 448, coinFilm);
	GameObject* coin36 = new Coin(3968, 448, coinFilm);
	GameObject* coin37 = new Coin(3984, 448, coinFilm);

	GameObject* coin38 = new Coin(5600, 560, coinFilm);
	GameObject* coin39 = new Coin(5600, 544, coinFilm);
	GameObject* coin40 = new Coin(5600, 528, coinFilm);
	GameObject* coin41 = new Coin(5600, 512, coinFilm);
	GameObject* coin42 = new Coin(5616, 512, coinFilm);
	GameObject* coin43 = new Coin(5632, 512, coinFilm);
	GameObject* coin44 = new Coin(5648, 512, coinFilm);
	GameObject* coin45 = new Coin(5664, 512, coinFilm);
	GameObject* coin46 = new Coin(5680, 512, coinFilm);
	GameObject* coin47 = new Coin(5680, 528, coinFilm);
	GameObject* coin48 = new Coin(5680, 544, coinFilm);
	GameObject* coin49 = new Coin(5680, 560, coinFilm);

	/*Bonus scene coins*/

	GameObject* coinb1 = new Coin(8256, 128, coinFilm);
	GameObject* coinb2 = new Coin(8274, 128, coinFilm);
	GameObject* coinb3 = new Coin(8290, 128, coinFilm);

	GameObject* coin14_2 = new Coin(8256, 480, coinFilm);
	GameObject* coin15_2 = new Coin(8256, 460, coinFilm);
	GameObject* coin16_2 = new Coin(8256, 440, coinFilm);

	GameObject* coinb7 = new Coin(8320, 480, coinFilm);
	GameObject* coinb8 = new Coin(8320, 460, coinFilm);
	GameObject* coinb9 = new Coin(8320, 440, coinFilm);

	GameObject* coinb20 = new Coin(8400, 480, coinFilm);
	GameObject* coinb21 = new Coin(8400, 460, coinFilm);
	GameObject* coinb22 = new Coin(8400, 440, coinFilm);

	auto& coinAll = SpriteManager::GetInstance().getTypeList("COIN");
	for (auto* i : coinAll) {
		CollisionChecker::GetInstance().Register(game.getPlayer(), i, function_collision_player_coin);
	}
}

void CreateQuestionBricks(const Game& game)
{
	/*Question bricks*/
	AnimationFilm* questionFilm = AnimationFilmHolder::GetInstance().GetFilm("QUESTION_BRICK");
	GameObject* brickOne = new QuestionBrick(192, 518, questionFilm);
	GameObject* bricktwo = new QuestionBrick(224, 518, questionFilm);
	GameObject* brick4 = new QuestionBrick(3792, 486, questionFilm);
	GameObject* brick5 = new QuestionBrick(4656, 454, questionFilm);
	GameObject* brick6 = new QuestionBrick(4720, 454, questionFilm);
	GameObject* brick7 = new QuestionBrick(5344, 310, questionFilm);
	GameObject* brick8 = new QuestionBrick(1744, 518, questionFilm);

	GameObject* brick9 = new QuestionBrick(3296, 214, questionFilm);
	GameObject* brick10 = new QuestionBrick(3312, 214, questionFilm);
	GameObject* brick11 = new QuestionBrick(2800, 422, questionFilm);
	auto& allQuestionBricks = SpriteManager::GetInstance().getTypeList("QUESTION_BRICK");
	for (auto* i : allQuestionBricks) {
		CollisionChecker::GetInstance().Register(game.getPlayer(), i, function_collision_player_questionBrick);
	}
	/*------------------------------*/
	//Ta y itane 512 alla prepei na pane 518 gia na doulepsei to collision
	//Ta zwgrafizoyme opws san na itane sto 512.....
	//Oti brick valeis vres kanonika to ipsos stoy kai apla kane +6 otan ftiaxneis to object
	//Sta tiles  den allazei kati
}