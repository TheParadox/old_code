#include "pch.hpp"
#include "MultiPlayerMenuUI.hpp"

void MultiPlayerMenuUI::initialize() {

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
	m_labels.back()->setText("Multiplayer");
	m_labels.back()->setSize(250, 30);
	m_labels.back()->setPosition(
		(panelWidth / 2) - 125,
		25
	);
	m_labels.back()->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	m_panel->add(m_labels.back());

	m_buttons.push_back(tgui::Button::create());
	m_buttons.back()->setText("Back");
	m_buttons.back()->setSize(125, 30);
	m_buttons.back()->setPosition(
		(panelWidth / 2) - 62,
		260
	);
	m_panel->add(m_buttons.back());

	addToGui();
}

void MultiPlayerMenuUI::update() {
}

void MultiPlayerMenuUI::updateJsonData(json d) {
}

void MultiPlayerMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void()> func) {
}

void MultiPlayerMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(int)> func, int a) {
}

void MultiPlayerMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(int, int)> func, int a, int b) {
	if (bn == "Back") {
		m_buttons[0]->onPress(func, a, b);
	}
}

void MultiPlayerMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(std::string)> func, std::string s) {
}

void MultiPlayerMenuUI::addFunctionCallbackToButton(std::string, std::function<void(json&)>, json&) {
}
