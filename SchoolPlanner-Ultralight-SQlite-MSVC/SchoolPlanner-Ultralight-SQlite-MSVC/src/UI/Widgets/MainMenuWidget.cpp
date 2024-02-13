#include "sc_pch.hpp"
#include "MainMenuWidget.hpp"

MainMenuWidget::MainMenuWidget() {
	m_schoolSet = false;
	m_currentSchool = "";
}

MainMenuWidget::~MainMenuWidget() {
}

void MainMenuWidget::OnDOMReady(ultralight::View* caller, uint64_t frameID, bool isMainFrame, const String& url) {

	RefPtr<JSContext> context = m_overlay->view()->LockJSContext();
	SetJSContext(context->ctx());

	JSObject global = JSGlobalObject();

	js_showSchool = global["showSchool"];
	global["quit"] = BindJSCallback(&MainMenuWidget::close);
	global["newSchool"] = BindJSCallback(&MainMenuWidget::newSchool);
	global["update"] = BindJSCallback(&MainMenuWidget::update);

	json request = json();
	request["table"] = "school";
	request["method"] = "selectOne";
	
	json response = s_queryDB(request);
	m_currentSchool = JH::getStdString(response, "school").c_str();
	m_schoolSet = JH::getBool(response, "dbLoaded");

	js_showSchool({m_schoolSet, m_currentSchool});
}

void MainMenuWidget::update(const JSObject& obj, const JSArgs& args) {

	json request = json();
	request["table"] = "school";
	request["method"] = "selectOne";

	json response = s_queryDB(request);
	m_currentSchool = JH::getStdString(response["school"], "name").c_str();
	m_schoolSet = JH::getBool(response, "success");

	js_showSchool({ m_schoolSet, m_currentSchool });
}

void MainMenuWidget::close(const JSObject& obj, const JSArgs& args) {
	s_closeApp(nullptr);
}

void MainMenuWidget::newSchool(const JSObject& obj, const JSArgs& args) {
	if (args.size() == 1) {
		std::string data = static_cast<String>(args[0]).utf8().data();
		json result = json::parse(data);

		json request = json();
		request["createDB"] = true;
		request["dbName"] = "data/" + JH::getStdString(result, "name") + ".db";
		s_queryDB(request);

		request = json();
		request["table"] = "school";
		request["method"] = "create";
		request["schoolName"] = JH::getStdString(result, "name");
		s_queryDB(request);

	}

}
