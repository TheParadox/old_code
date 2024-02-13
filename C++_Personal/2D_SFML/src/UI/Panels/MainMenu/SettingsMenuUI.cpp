#include "pch.hpp"
#include "SettingsMenuUI.hpp"

void SettingsMenuUI::initialize() {

	int panelWidth = 450;
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
	m_labels.back()->setText("Settings");
	m_labels.back()->setSize(250, 30);
	m_labels.back()->setPosition(
		(panelWidth / 2) - 125,
		10
	);
	m_labels.back()->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	m_panel->add(m_labels.back());

	m_tabContainer = tgui::TabContainer::create();
	tgui::Panel::Ptr tab1 = createGameplayPanel(m_tabContainer);
	tgui::Panel::Ptr tab2 = createGraphicsPanel(m_tabContainer);
	tgui::Panel::Ptr tab3 = createSoundPanel(m_tabContainer);
	tgui::Panel::Ptr tab4 = createControlsPanel(m_tabContainer);

	m_tabContainer->setPosition(0, 45);
	m_tabContainer->setTabsHeight(30);
	m_tabContainer->setSize(450, 250);
	m_tabContainer->select(0);
	m_panel->add(m_tabContainer);

	m_buttons.push_back(tgui::Button::create());
	m_buttons.back()->setText("Back");
	m_buttons.back()->setSize(125, 30);
	m_buttons.back()->setPosition(
		(panelWidth / 2) + 70,
		260
	);
	m_panel->add(m_buttons.back());

	m_buttons.push_back(tgui::Button::create());
	m_buttons.back()->setText("Accept");
	m_buttons.back()->setSize(125, 30);
	m_buttons.back()->setPosition(
		(panelWidth / 2) - 60,
		260
	);
	m_panel->add(m_buttons.back());


	addToGui();
}

void SettingsMenuUI::update() {
}

void SettingsMenuUI::updateJsonData(json d) {
	m_settingsData = d;
	for (int i = 0; i < 23; i++) {
		if (
			(listOfScreenHeights[i] == m_settingsData["graphics"]["resolution"]["h"]) &&
			(listOfScreenWidths[i] == m_settingsData["graphics"]["resolution"]["w"])
			) {
			m_screenRes->setSelectedItemByIndex(i);
		}
	}
	for (int i = 0; i < 3; i++) {
		if (listOfWindowStyleInts[i] == m_settingsData["graphics"]["windowStyle"]) {
			m_windowStyle->setSelectedItemByIndex(i);
		}
	}
}

void SettingsMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void()> func) {
}

void SettingsMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(int)> func, int a) {
}

void SettingsMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(int, int)> func, int a, int b) {
	if (bn == "Back") {
		m_buttons[0]->onPress(func, a, b);
	}
}

void SettingsMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(std::string)> func, std::string s) {
}

void SettingsMenuUI::addFunctionCallbackToButton(std::string bn, std::function<void(json&)> func, json& data) {
	if (bn == "Accept") {
		m_buttons[1]->onPress(func, std::ref(m_settingsData));
	}
}

tgui::Panel::Ptr SettingsMenuUI::createGameplayPanel(tgui::TabContainer::Ptr tb) {
	tgui::Panel::Ptr panel = tb->addTab("Gameplay");

	return panel;
}

tgui::Panel::Ptr SettingsMenuUI::createGraphicsPanel(tgui::TabContainer::Ptr tb) {
	tgui::Panel::Ptr panel = tb->addTab("Graphics");

	tgui::Label::Ptr label = tgui::Label::create();
	label->setText("Screen Resolution:");
	label->setSize(200, 20);
	label->setPosition(10, 10);
	label->setTextSize(14);
	label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	panel->add(label);

	m_screenRes = tgui::ComboBox::create();
	m_screenRes->setSize(200, 20);
	m_screenRes->setPosition(225, 10);
	m_screenRes->setItemsToDisplay(5);
	for (int i = 0; i < 23; i++) {
		m_screenRes->addItem(std::to_string(listOfScreenWidths[i]) + "x" + std::to_string(listOfScreenHeights[i]), std::to_string(i));
	}
	panel->add(m_screenRes);
	m_screenRes->onItemSelect(&SettingsMenuUI::updateScreenResSetting, this);



	label = tgui::Label::create();
	label->setText("Window Style:");
	label->setSize(200, 20);
	label->setPosition(10, 40);
	label->setTextSize(14);
	label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	panel->add(label);

	m_windowStyle = tgui::ComboBox::create();
	m_windowStyle->setSize(200, 20);
	m_windowStyle->setPosition(225, 40);
	m_windowStyle->setItemsToDisplay(5);
	for (int i = 0; i < 3; i++) {
		m_windowStyle->addItem(listOfWindowStyle[i], std::to_string(i));
	}
	panel->add(m_windowStyle);
	m_windowStyle->onItemSelect(&SettingsMenuUI::updateWindowStyle, this);


	return panel;
}

tgui::Panel::Ptr SettingsMenuUI::createSoundPanel(tgui::TabContainer::Ptr tb) {
	tgui::Panel::Ptr panel = tb->addTab("Sound");

	return panel;
}

tgui::Panel::Ptr SettingsMenuUI::createControlsPanel(tgui::TabContainer::Ptr tb) {
	tgui::Panel::Ptr panel = tb->addTab("Controls");

	return panel;
}

void SettingsMenuUI::updateScreenResSetting() {
	int i = m_screenRes->getSelectedItemIndex();
	LOG_TRACE("Updating Screen Resolution - ID: " + std::to_string(i));
	m_settingsData["graphics"]["resolution"]["w"] = listOfScreenWidths[i];
	m_settingsData["graphics"]["resolution"]["h"] = listOfScreenHeights[i];
}

void SettingsMenuUI::updateWindowStyle() {
	int i = m_windowStyle->getSelectedItemIndex();
	LOG_TRACE("Updating Window Style - ID: " + std::to_string(i));
	m_settingsData["graphics"]["windowStyle"] = listOfWindowStyleInts[i];
}

int SettingsMenuUI::listOfScreenWidths[23] = {
		800, 1024, 1152, 1176, 1280, 1280, 1280, 1280, 1280, 1280, 1360, 1366, 1440, 1600, 1600, 1600,
		1680, 1920, 1920, 1920, 2048, 2560, 2560
};

int SettingsMenuUI::listOfScreenHeights[23] = {
		600, 768, 8684, 664, 720, 768, 800, 960, 1024, 1440, 768, 768, 900, 900, 1024, 1200, 1050, 1080,
		1200, 1440, 1536, 1440, 1600
};

int SettingsMenuUI::listOfWindowStyleInts[3] = {0, 5, 8};
std::string SettingsMenuUI::listOfWindowStyle[3]{
	"Borderless",
	"Window",
	"Fullscreen"
};