#pragma once

#include "Core.hpp"

#include "UI/UserInterface.hpp"

class MultiPlayerMenuUI : public UserInterface {
public:
	MultiPlayerMenuUI(std::shared_ptr<tgui::Gui> gui, int x, int y) : UserInterface(gui, x, y) {};
	~MultiPlayerMenuUI() {};

	virtual void initialize() override;
	virtual void update() override;

	virtual void updateJsonData(json d) override;

	virtual void addFunctionCallbackToButton(std::string, std::function<void()>) override;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(int)>, int) override;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(int, int)>, int, int) override;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(std::string)>, std::string) override;
	virtual void addFunctionCallbackToButton(std::string, std::function<void(json&)>, json&) override;

private:


};