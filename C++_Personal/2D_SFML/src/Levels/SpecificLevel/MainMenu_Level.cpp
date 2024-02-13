#include "pch.hpp"
#include "MainMenu_Level.hpp"

#include "UI/Panels/MainMenu/MainMenuUI.hpp"
#include "UI/Panels/MainMenu/SinglePlayerMenuUI.hpp"
#include "UI/Panels/MainMenu/MultiPlayerMenuUI.hpp"
#include "UI/Panels/MainMenu/LoadGameMenuUI.hpp"
#include "UI/Panels/MainMenu/SettingsMenuUI.hpp"
#include "UI/Panels/MainMenu/CreditsMenuUI.hpp"

MainMenu_Level::MainMenu_Level() {

}

MainMenu_Level::~MainMenu_Level() {

}

void MainMenu_Level::initializeLevel(std::shared_ptr<sf::RenderWindow> window) {

	m_gui = std::make_shared<tgui::GuiSFML>();

	m_gui->setTarget(*window);

	try {
		m_theme = std::make_shared<tgui::Theme>("themes/Black.txt");
		tgui::Theme::setDefault(m_theme);
	} catch (const tgui::Exception& e) {
		LOG_ERROR(e.what());
	}

	int screenX = window->getSize().x;
	int screenY = window->getSize().y;

	m_ui.push_back(std::make_shared<MainMenuUI>(m_gui, screenX, screenY));
	m_ui.back()->initialize();
	m_ui.back()->addFunctionCallbackToButton("Singleplayer", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 0, 1);
	m_ui.back()->addFunctionCallbackToButton("Multiplayer", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 0, 2);
	m_ui.back()->addFunctionCallbackToButton("Load", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 0, 3);
	m_ui.back()->addFunctionCallbackToButton("Settings", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 0, 4);
	m_ui.back()->addFunctionCallbackToButton("Credits", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 0, 5);

	m_ui.push_back(std::make_shared<SinglePlayerMenuUI>(m_gui, screenX, screenY));
	m_ui.back()->initialize();
	m_ui.back()->changeVisibility();
	m_ui.back()->addFunctionCallbackToButton("Back", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 1, 0);

	m_ui.push_back(std::make_shared<MultiPlayerMenuUI>(m_gui, screenX, screenY));
	m_ui.back()->initialize();
	m_ui.back()->changeVisibility();
	m_ui.back()->addFunctionCallbackToButton("Back", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 2, 0);

	m_ui.push_back(std::make_shared<LoadGameMenuUI>(m_gui, screenX, screenY));
	m_ui.back()->initialize();
	m_ui.back()->changeVisibility();
	m_ui.back()->addFunctionCallbackToButton("Back", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 3, 0);

	m_ui.push_back(std::make_shared<SettingsMenuUI>(m_gui, screenX, screenY));
	m_ui.back()->initialize();
	m_ui.back()->changeVisibility();
	m_ui.back()->addFunctionCallbackToButton("Back", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 4, 0);

	m_ui.push_back(std::make_shared<CreditsMenuUI>(m_gui, screenX, screenY));
	m_ui.back()->initialize();
	m_ui.back()->changeVisibility();
	m_ui.back()->addFunctionCallbackToButton("Back", BIND_EVENT_FN_2(MainMenu_Level::swapUI), 5, 0);
}

void MainMenu_Level::update() {

}

void MainMenu_Level::shutdown() {

}

void MainMenu_Level::draw(std::shared_ptr<sf::RenderWindow> window) {

}

void MainMenu_Level::updateJsonData(std::string ui, json d) {
	if (ui == "SettingsMenu") {
		m_ui[4]->updateJsonData(d);
	}
}

void MainMenu_Level::addFunctionCallbackToButton(std::string ui, std::string bn, std::function<void()> func) {
	if (ui == "MainMenu") {
		m_ui[0]->addFunctionCallbackToButton(bn, func);
	}
}

void MainMenu_Level::addFunctionCallbackToButton(std::string ui, std::string bn, std::function<void(int)> func, int a) {

}

void MainMenu_Level::addFunctionCallbackToButton(std::string, std::string, std::function<void(int, int)>, int a, int b) {

};

void MainMenu_Level::addFunctionCallbackToButton(std::string ui, std::string bn, std::function<void(std::string)> func, std::string s) {

}

void MainMenu_Level::addFunctionCallbackToButton(std::string ui, std::string bn, std::function<void(json&)> func, json& data) {
	if (ui == "SettingsMenu") {
		m_ui[4]->addFunctionCallbackToButton(bn, func, data);
	}
}