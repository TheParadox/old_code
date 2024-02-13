#include "sc_pch.hpp"
#include "Application.hpp"

Application::Application() {
	loadConfig();

	m_app = App::Create();

	m_window = Window::Create(
		m_app->main_monitor(),
		m_configSettings->iWidth(),
		m_configSettings->iHeight(),
		false,
		kWindowFlags_Titled
	);

	m_window->SetTitle(m_configSettings->title.c_str());

	m_ui.reset(new UI(m_window));
	m_window->set_listener(m_ui.get());
	m_ui->setAppClose(SC_CALLBACK_0(Application::onClose));

	m_db.reset(new Database());
	m_ui->setQueryDatabase(SC_CALLBACK_1(Application::queryDB));

	m_ui->setApp(this);

	m_ui->init();
}

Application::~Application() {
	shutdown();
}

void Application::start() {


}

void Application::run() {
	m_app->Run();
}

void Application::shutdown() {
	m_window->set_listener(nullptr);

	m_ui.reset();

	m_window = nullptr;
	m_app = nullptr;
}

void Application::onClose() {
	App::instance()->Quit();
}

json Application::queryDB(json _j) {
	if (JH::getBool(_j, "createDB")) {
		return m_db->createDB(JH::getStdString(_j, "dbName"));
	} else if (JH::getBool(_j, "loadDB")) {
		return m_db->loadDB(JH::getStdString(_j, "dbName"));
	}

	return m_db->queryDB(_j);
}

void Application::setCurrentDB(std::string _s) {
	m_configSettings->currentDatabase = _s;
}

void Application::loadConfig() {
	m_configSettings = SC::CreateRefPtr<ConfigDataStruct>();
	json configData = StdFO::loadDataFile("data/config", StdFO::FileType::json);


	m_configSettings->title = JH::getStdString(configData["window"], "title", "CHAOS");

	if (configData["window"]["backgroundImage"].is_null()) {
		m_configSettings->backgroundImage = "assets/images/background.png";
	} else {
		m_configSettings->backgroundImage = configData["window"]["backgroundImage"].get<std::string>();
	}

	if (configData["window"]["screenResolutions"].is_null()) {
		m_configSettings->screenResolutions.push_back({ 1200, 700 });
	} else {
		for (int i = 0; i < configData["window"]["screenResolutions"].size(); i++) {
			m_configSettings->screenResolutions.push_back(
				{
					configData["window"]["screenResolutions"][i][0],
					configData["window"]["screenResolutions"][i][1]
				}
			);
		}
	}

	if (m_configSettings->screenResolutions.size() == 1) {
		m_configSettings->screenResID = 0;
	} else {
		if (configData["window"]["screenRes"].is_null()) {
			m_configSettings->screenResID = 0;
		} else {
			m_configSettings->screenResID = configData["window"]["screenRes"];
		}
	}
	m_configSettings->setScreenRes();


	m_configSettings->fullscreen = JH::getBool(configData["window"], "fullscreen");

	m_configSettings->currentDatabase = JH::getStdString(configData, "database");

}

void Application::updateConfig() {
}

void Application::saveConfig() {
	json data = json();

	StdFO::saveDataFile("data/config", StdFO::FileType::json, data);
}
