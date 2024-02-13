#pragma once

#include "Core.hpp"

struct WindowData {
public:
	WindowData() {
		m_screenHeight = 0;
		m_screenWidth = 0;
		m_windowStyle = 0;
	};

	~WindowData() {};

	void setHeight(int h) {
		m_screenHeight = h;
	};

	void setWidth(int w) {
		m_screenWidth = w;
	};

	void setStyle(int s) {
		m_windowStyle = s;
	};

	int getHeight() {
		return m_screenHeight;
	};

	int getWidth() {
		return m_screenWidth;
	};

	int getStyle() {
		return m_windowStyle;
	};

private:
	int m_screenHeight;
	int m_screenWidth;
	int m_windowStyle;

};