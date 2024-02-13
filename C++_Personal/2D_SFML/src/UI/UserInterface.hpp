#pragma once

#include "Core.hpp"

#include <TGUI/TGUI.hpp>

class UserInterface {
public:
	UserInterface(std::shared_ptr<tgui::Gui> gui, int x, int y)
		: m_gui(gui), m_screenWidth(x), m_screenHeight(y) {};

	~UserInterface() {
		m_buttons.clear();
		m_labels.clear();
	};

	virtual void initialize() = 0;
	virtual void update() = 0;

	void changeVisibility() {
		m_isVisible = !m_isVisible;
		m_panel->setVisible(m_isVisible);
	};

	void addToGui() {
		m_gui->add(m_panel);
	};

	void removeFromGui() {
		m_gui->remove(m_panel);
	};

	virtual void updateJsonData(json d) = 0;

	virtual void addFunctionCallbackToButton(std::string, std::function<void()>) = 0;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(int)>, int) = 0;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(int, int)>, int, int) = 0;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(std::string)>, std::string) = 0;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(json&)>, json&) = 0;

protected:
	std::shared_ptr<tgui::Gui> m_gui;

	int m_screenWidth;
	int m_screenHeight;

	bool m_isVisible = true;
	tgui::Panel::Ptr m_panel;
	std::vector<tgui::Button::Ptr> m_buttons;
	std::vector<tgui::Label::Ptr> m_labels;

};