#pragma once

#include <AppCore/AppCore.h>
#include <Ultralight/Listener.h>


using namespace ultralight;

class Widget : public ViewListener, public LoadListener {
public:
	virtual ~Widget();

	void init(RefPtr<Window> _w, const String& _url);

	virtual void update(const JSObject& obj, const JSArgs& args) = 0;

	void show();
	void hide();

	//void setCommonJStoCppFunctions(JSObject* jso);

	static void setDatabaseQuery(std::function<json(json)> _f);
	static void setChangeWidget(std::function<void(json)> _f);
	static void setCloseApp(std::function<void(ultralight::Window*)> _f);

protected:
	RefPtr<Overlay> m_overlay;
	bool isVisible;

	static std::function<json(json)> s_queryDB;
	static std::function<void(json)> s_changeWidget;
	static std::function<void(ultralight::Window*)> s_closeApp;
};