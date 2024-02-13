#pragma once

#include "Core.hpp"

#include "UI/UserInterface.hpp"

class SettingsMenuUI : public UserInterface {
public:
	SettingsMenuUI(std::shared_ptr<tgui::Gui> gui, int x, int y) : UserInterface(gui, x, y) {};
	~SettingsMenuUI() {};

	virtual void initialize() override;
	virtual void update() override;

	virtual void updateJsonData(json d) override;

	virtual void addFunctionCallbackToButton(std::string, std::function<void()>) override;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(int)>, int) override;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(int, int)>, int, int) override;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(std::string)>, std::string) override;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(json&)>, json&) override;


	tgui::Panel::Ptr createGameplayPanel(tgui::TabContainer::Ptr);
	tgui::Panel::Ptr createGraphicsPanel(tgui::TabContainer::Ptr);
	tgui::Panel::Ptr createSoundPanel(tgui::TabContainer::Ptr);
	tgui::Panel::Ptr createControlsPanel(tgui::TabContainer::Ptr);

	void updateScreenResSetting();
	void updateWindowStyle();

private:
	tgui::TabContainer::Ptr m_tabContainer;
	tgui::ComboBox::Ptr m_screenRes;
	tgui::ComboBox::Ptr m_windowStyle;


	json m_settingsData;

	static int listOfScreenWidths[23];
	static int listOfScreenHeights[23];
	static int listOfWindowStyleInts[3];
	static std::string listOfWindowStyle[3];
};