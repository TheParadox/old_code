#pragma once

#include "UI/Widget.hpp"

class MainMenuWidget : public Widget {
public:
	MainMenuWidget();
	virtual ~MainMenuWidget();

	virtual void OnDOMReady(ultralight::View* caller,
		uint64_t frameID,
		bool isMainFrame,
		const String& url) override;

	virtual void update(const JSObject& obj, const JSArgs& args) override;

	void close(const JSObject& obj, const JSArgs& args);
	void newSchool(const JSObject& obj, const JSArgs& args);

private:
	JSFunction js_showSchool;

private:
	bool m_schoolSet;
	String m_currentSchool;
};