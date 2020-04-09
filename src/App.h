#pragma once
#ifndef APP_H
#define APP_H
#include"Game.h"

namespace app {

	class App {

	protected:
		Game* game = new Game();

	public:
		virtual void Initialise() = 0;
		virtual void Load() = 0;

		virtual void Run() {
			game->mainLoop();
		}

		virtual void RunIteration(void)
		{
			game->mainLoopIteration();
		}

		Game* GetGame()
		{
			return game;
		}

		const Game* GetGame() const {
			return game;
		}

		virtual void Clear() = 0;

		void Main() {
			Initialise(); //Just init some variables
			Load(); //Loading the map from txt
			Run();//Run the game loop
			Clear();//Memory management
		}
	};
}
#endif // ! APP_H