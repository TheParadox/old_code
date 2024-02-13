#include "pch.hpp"
#include "Engine.hpp"

Engine::Engine() {
	m_isRunning = true;
	m_isPaused = false;

	m_bg = sf::Color(218, 24, 132, 255);

	if (!FileHandler::loadMainDataFile()) {
		LOG_FATAL("Failed to load main data files! Quiting!");
		m_isRunning = false;
		return;
	}

	json playerConfigs = FileHandler::loadPlayerConfigs();
	m_graphicsData = playerConfigs["graphics"];
	m_audioData = playerConfigs["audio"];
	m_gameplayData = playerConfigs["gameplay"];
	m_controlsData = playerConfigs["controls"];
}

Engine::~Engine() {

}

void Engine::prime() {

	m_mainWindow = std::make_shared<sf::RenderWindow>();
	m_mainWindow->create(
		sf::VideoMode(
			m_graphicsData["resolution"]["w"].get<int>(),
			m_graphicsData["resolution"]["h"].get<int>()
		), 
		"Of Emperors and Freelancers",
		m_graphicsData["windowStyle"].get<int>()
	);

	changeLevel(EngineLevelEnums::MainMenuLevel);

}

void Engine::running() {
	if (m_level == nullptr) {
		LOG_FATAL("NO LEVEL FOUND!");
		m_isRunning = false;
	}

	while (m_isRunning) {
		sf::Event event;

		while (m_mainWindow->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				changeRunningState();
			}

			m_level->guiHandleEvent(event);

			//IF it wasn't a close event AND not a GUI event, then we
			//Pass the event to the player controller here
		}

		if (!m_isPaused) {
			//run update logic here...
			//physics update?
		}

		m_mainWindow->clear(m_bg);

		m_level->draw(m_mainWindow);

		m_level->drawUI();

		m_mainWindow->display();
	}
}

void Engine::shutdown() {
	m_mainWindow->close();
}

void Engine::changeLevel(EngineLevelEnums level) {
	if (m_level != nullptr) {
		m_level->shutdown();
	}

	switch (level) {
		case EngineLevelEnums::MainMenuLevel:
			m_level = std::make_shared<MainMenu_Level>();
			break;
		case EngineLevelEnums::GameLevel:
			m_level = nullptr;
			break;
		default:
			m_level = nullptr;
			break;
	}

	m_level->initializeLevel(m_mainWindow);

	if (level == EngineLevelEnums::MainMenuLevel) {
		m_level->addFunctionCallbackToButton("MainMenu", "Quit", BIND_EVENT_FN_0(Engine::changeRunningState));
		json data = json::object();
		data["graphics"] = m_graphicsData;
		data["audio"] = m_audioData;
		data["gameplay"] = m_gameplayData;
		data["controls"] = m_controlsData;
		m_level->updateJsonData("SettingsMenu", data);
		m_level->addFunctionCallbackToButton("SettingsMenu", "Accept", BIND_EVENT_FN_1(Engine::updateSettings), std::ref(data));
	}

}

void Engine::updateSettings(json& newSettings) {
	LOG_TRACE(std::to_string(newSettings["graphics"]["windowStyle"].get<int>()));
	if (m_graphicsData["windowStyle"].get<int>() != newSettings["graphics"]["windowStyle"].get<int>()) {
		m_mainWindow->create(
			sf::VideoMode(
			newSettings["graphics"]["resolution"]["w"].get<int>(),
			newSettings["graphics"]["resolution"]["h"].get<int>()
		),
			"Of Emperors and Freelancers",
			newSettings["graphics"]["windowStyle"].get<int>()
		);
	} else if (
		(m_graphicsData["resolution"]["w"].get<int>() != newSettings["graphics"]["resolution"]["w"].get<int>()) ||
		(m_graphicsData["resolution"]["h"].get<int>() != newSettings["graphics"]["resolution"]["h"].get<int>())) {
		m_mainWindow->setSize(sf::Vector2u(
			newSettings["graphics"]["resolution"]["w"].get<int>(),
			newSettings["graphics"]["resolution"]["h"].get<int>()
		));
	}

	FileHandler::saveJsonFile(FileHandler::n_mainDataFolder + FileHandler::n_playerConfigFilename, newSettings);

	m_graphicsData = newSettings["graphics"];
	m_audioData = newSettings["audio"];
	m_gameplayData = newSettings["gameplay"];
	m_controlsData = newSettings["controls"];

	m_level->updateGUIWindow(m_mainWindow);
}
