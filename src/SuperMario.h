#pragma once
#include "App.h"
#include "Engine.h"

namespace superMario {
	class SuperMario :
		public app::App
	{
	private:
		Engine engine;
	public:
		SuperMario() = default;
		SuperMario(Engine& _engine);
		~SuperMario() = default;

		void Initialise();
		void Load();
		void Clear();
	};
}