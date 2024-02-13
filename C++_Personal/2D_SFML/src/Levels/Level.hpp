#pragma once

#include "Core.hpp"

#include "UI/UserInterface.hpp"

#include <TGUI/TGUI.hpp>

class Level {
public:
	Level() {};
	~Level() {
		m_ui.clear();
	};

	virtual void initializeLevel(std::shared_ptr<sf::RenderWindow> window) = 0;
	virtual void update() = 0;
	virtual void shutdown() = 0;

	virtual void draw(std::shared_ptr<sf::RenderWindow> window) = 0;

	void updateGUIWindow(std::shared_ptr<sf::RenderWindow> window) {
		m_gui->setTarget(*window);
	}

	void renderUI(int a) {
		m_ui[a]->changeVisibility();
	};

	void swapUI(int a, int b) {
		m_ui[a]->changeVisibility();
		m_ui[b]->changeVisibility();
	};


	void drawUI() {
		m_gui->draw();
	};

	void guiHandleEvent(sf::Event event) {
		m_gui->handleEvent(event);
	}

	virtual void updateJsonData(std::string, json d) = 0;

	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void()>) = 0;

	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void(int)>, int) = 0;
	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void(int, int)>, int, int) = 0;

	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void(std::string)>, std::string) = 0;
	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void(json&)>, json&) = 0;



protected:
	std::shared_ptr<tgui::Gui> m_gui;
	std::vector<std::shared_ptr<UserInterface>> m_ui;

	std::shared_ptr<tgui::Theme> m_theme;
};