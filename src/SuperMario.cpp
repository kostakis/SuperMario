#include "SuperMario.h"

superMario::SuperMario::SuperMario(Engine& _engine)
{
	engine = _engine;
}

void superMario::SuperMario::Initialise()
{
	engine.Initialise();
	game->setStartScreenPath("media/Start_image.png");
	game->Init(engine);//All initilazations for the game
}

void superMario::SuperMario::Load()
{
	engine.Load();
}

void superMario::SuperMario::Clear()
{
	delete game;
	engine.Clear();
}