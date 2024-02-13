#pragma once

#include "Core.hpp"

#include "Levels/Level.hpp"

class MainMenu_Level : public Level {
public:
	MainMenu_Level();
	~MainMenu_Level();

	virtual void initializeLevel(std::shared_ptr<sf::RenderWindow> window) override;
	virtual void update() override;
	virtual void shutdown() override;

	virtual void draw(std::shared_ptr<sf::RenderWindow> window) override;

	virtual void updateJsonData(std::string, json d) override;

	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void()>) override;
	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void(int)>, int) override;
	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void(int, int)>, int, int) override;
	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void(std::string)>, std::string) override;
	virtual void addFunctionCallbackToButton(std::string, std::string, std::function<void(json&)>, json&) override;
private:


};