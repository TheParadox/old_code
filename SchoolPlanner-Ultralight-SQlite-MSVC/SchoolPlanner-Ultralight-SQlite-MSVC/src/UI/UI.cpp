#include "sc_pch.hpp"
#include "UI.hpp"

#include "Application.hpp"


std::function<void()> UI::s_appClose = nullptr;
std::function<json(json)> UI::s_queryDatabase = nullptr;
Application* UI::s_app = nullptr;

UI::UI(RefPtr<Window> _w) : m_window(_w) {
	init();

	Widget::setChangeWidget(SC_CALLBACK_1(UI::changeWidget));
	Widget::setCloseApp(SC_CALLBACK_1(UI::OnClose));
}

UI::~UI() {}

void UI::init() {
	m_overlay = Overlay::Create(m_window, m_window->width(), m_window->height(), 0, 0);

	m_overlay->view()->set_load_listener(this);
	m_overlay->view()->set_view_listener(this);
	m_overlay->Hide();
	m_overlay->Unfocus();


	m_mainMenu = SC::CreateRefPtr<MainMenuWidget>();
	m_mainMenu->init(m_window, "MainMenu");
	m_mainMenu->show();

}

void UI::OnDOMReady(ultralight::View* _caller, uint64_t _frameID, bool _isMainFrame, const String& _url) {
	RefPtr<JSContext> context = _caller->LockJSContext();
	SetJSContext(context->ctx());

	JSObject global = JSGlobalObject();
}

void UI::OnClose(ultralight::Window* _window) {
	s_appClose();
}

void UI::OnResize(ultralight::Window* _window, uint32_t _width, uint32_t _height) {
}

void UI::changeWidget(json _data) {
}

void UI::setAppClose(std::function<void()> _f) {
	s_appClose = _f;
}

void UI::setQueryDatabase(std::function<json(json)> _f) {
	s_queryDatabase = _f;
	Widget::setDatabaseQuery(_f);
}
