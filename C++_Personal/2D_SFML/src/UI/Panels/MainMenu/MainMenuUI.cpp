#include "pch.hpp"
#include "MainMenuUI.hpp"

void MainMenuUI::initialize() {
	std::string buttonLabels[7] = {"Singleplayer Game", "Multiplayer Game", "Load Game", "Editor", "Settings", "Credits", "Quit"};

	int panelWidth = 250;
	int panelHeight = 75 + (7 * 35);
	m_panel = tgui::Panel::create(
		tgui::Layout2d(
			panelWidth,
			panelHeight
		)
	);


	m_panel->setPosition(
		(m_screenWidth / 2) - (panelWidth / 2),
		(m_screenHeight / 2) - (panelHeight / 2)
	);

	m_labels.push_back(tgui::Label::create());
	m_labels.back()->setText("Of Emperors and Freelancers");
	m_labels.back()->setSize(250, 30);
	m_labels.back()->setPosition(
		(panelWidth / 2) - 125,
		25
	);
	m_labels.back()->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	m_panel->add(m_labels.back());

	for (int i = 0; i < 7; i++) {
		m_buttons.push_back(tgui::Button::create());
		m_buttons.back()->setText(buttonLabels[i]);
		m_buttons.back()->setSize(125, 30);
		m_buttons.back()->setPosition(
			(panelWidth / 2) - 62,
			50 + (i * 35)
		);
		m_panel->add(m_buttons.back());

	}

	addToGui();
}

void MainMenuUI::update() {

}

void MainMenuUI::updateJsonData(json d) {
}

void MainMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void()> func) {
if (bn == "Quit") {
		m_buttons[6]->onPress(func);
	}
}

void MainMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(int)> func, int a) {

}

void MainMenuUI::addFunctionCallbackToButton(std::string, std::function<void(json&)>, json&) {
}

void MainMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(int, int)> func, int a, int b) {
	if (bn == "Singleplayer") {
		m_buttons[0]->onPress(func, a, b);
	} else if (bn == "Multiplayer") {
		m_buttons[1]->onPress(func, a, b);
	} else if (bn == "Load") {
		m_buttons[2]->onPress(func, a, b);
	} else if (bn == "Editor") {
		m_buttons[3]->onPress(func, a, b);
	} else if (bn == "Settings") {
		m_buttons[4]->onPress(func, a, b);
	} else if (bn == "Credits") {
		m_buttons[5]->onPress(func, a, b);
	}
};

void MainMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(std::string)> func, std::string s) {

}