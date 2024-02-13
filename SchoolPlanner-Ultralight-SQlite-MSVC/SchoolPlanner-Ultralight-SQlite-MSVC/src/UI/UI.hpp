#pragma once
#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>
#include <AppCore/JSHelpers.h>

#include "Widget.hpp"
#include "Widgets/MainMenuWidget.hpp"

class Application;

using namespace ultralight;

class UI : public LoadListener, public WindowListener, public ViewListener {
public:
	UI(RefPtr<Window> _w);
	~UI();

	void init();

	virtual void OnDOMReady(ultralight::View* _caller,
		uint64_t _frameID,
		bool _isMainFrame,
		const String& _url) override;

	virtual void OnClose(ultralight::Window* _window) override;
	virtual void OnResize(ultralight::Window* _window, uint32_t _width, uint32_t _height) override;

	void changeWidget(json _data);

	static void setAppClose(std::function<void()> _f);
	static void setQueryDatabase(std::function<json(json)> _f);

	static void setApp(Application* _a) {
		s_app = _a;
	}

private:
	RefPtr<Window> m_window;
	RefPtr<Overlay> m_overlay;

	SC::RefPtr<MainMenuWidget> m_mainMenu;
	

	static std::function<void()> s_appClose;
	static std::function<json(json)> s_queryDatabase;

	static Application* s_app;

};