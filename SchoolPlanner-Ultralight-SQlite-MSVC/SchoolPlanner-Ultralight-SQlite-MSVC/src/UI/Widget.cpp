#include "sc_pch.hpp"
#include "Widget.hpp"


std::function<json(json)> Widget::s_queryDB = nullptr;
std::function<void(json)> Widget::s_changeWidget = nullptr;
std::function<void(ultralight::Window*)> Widget::s_closeApp = nullptr;


Widget::~Widget() {}

void Widget::init(RefPtr<Window> _w, const String& _url) {
	m_overlay = Overlay::Create(_w, _w->width(), _w->height(), 0, 0);
	m_overlay->view()->set_view_listener(this);
	m_overlay->view()->set_load_listener(this);
	m_overlay->view()->LoadURL("file:///" + _url + ".html");
}

void Widget::show() {
	m_overlay->Show();
	m_overlay->Focus();
}

void Widget::hide() {
	m_overlay->Hide();
	m_overlay->Unfocus();
}

void Widget::setDatabaseQuery(std::function<json(json)> _f) {
	s_queryDB = _f;
}

void Widget::setChangeWidget(std::function<void(json)> _f) {
	s_changeWidget = _f;
}

void Widget::setCloseApp(std::function<void(ultralight::Window*)> _f) {
	s_closeApp = _f;
	//
}
