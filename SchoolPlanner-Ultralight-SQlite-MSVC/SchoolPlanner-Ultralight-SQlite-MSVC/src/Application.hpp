#pragma once
#include <AppCore/App.h>
#include <AppCore/Window.h>

#include "UI/UI.hpp"
#include "SQL/Database.hpp"

#include "Structs/ConfigDataStruct.hpp"

using namespace ultralight;

class Application {
public:
	Application();
	~Application();

	void start();
	void run();
	void shutdown();

	void onClose();

	json queryDB(json _j);

	void setCurrentDB(std::string _s);

private:
	void loadConfig();
	void updateConfig();
	void saveConfig();

private:
	RefPtr<App> m_app;
	RefPtr<Window> m_window;

	SC::RefPtr<UI> m_ui;
	SC::RefPtr<Database> m_db;

	SC::RefPtr<ConfigDataStruct> m_configSettings;
};