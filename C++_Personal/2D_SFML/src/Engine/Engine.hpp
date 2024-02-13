#pragma once

#include "Core.hpp"
#include "Helpers/EngineEnums.hpp"

#include "Levels/Level.hpp"
#include "Levels/SpecificLevel/MainMenu_Level.hpp"

#include <SFML/Graphics.hpp>

class Engine {
public:
	Engine();
	~Engine();

	void prime();
	void running();
	void shutdown();

	void changeLevel(EngineLevelEnums level);

	void changeRunningState() {
		LOG_TRACE("Quitting the game");
		m_isRunning = !m_isRunning;
	};

	void updateSettings(json& newSettings);

	bool successfulIgnition() {
		return m_isRunning;
	};

private:
	bool m_isRunning;
	bool m_isPaused;

	std::shared_ptr<sf::RenderWindow> m_mainWindow;
	sf::Color m_bg;

	std::shared_ptr<Level> m_level;

	json m_graphicsData;
	json m_gameplayData;
	json m_audioData;
	json m_controlsData;
};