#include "pch.hpp"
#include "Core.hpp"

#include "Engine/Engine.hpp"

int main() {
	Log::init();
	LOG_INFO("2D OEAF - SFML, TGUI");

	Engine engine;

	if (engine.successfulIgnition()) {
		engine.prime();
		engine.running();
		engine.shutdown();
	}

	return 1;
}