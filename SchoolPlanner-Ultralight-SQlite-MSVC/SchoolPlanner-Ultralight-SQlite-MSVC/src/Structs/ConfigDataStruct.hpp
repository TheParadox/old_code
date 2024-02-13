#pragma once

#include "Structs/DataEntity.hpp"

struct ConfigSets {
	int id = 0;
	std::string name = "Default";
	std::string path;
};

struct ScreenResolution {
	int width;
	int height;

	std::string resolution() {
		return (std::to_string(width) + " x " + std::to_string(height));
	}
};

struct ConfigDataStruct : public DataEntity {
	std::string title;
	std::string backgroundImage;
	std::vector<ScreenResolution> screenResolutions;
	int screenResID;
	bool fullscreen;

	std::string currentDatabase;

	int textSize;

	bool hasChaged = false;

public:
	int iWidth() { return width; }
	int iHeight() { return height; }

	float fWidth() { return (float)width; }
	float fHeight() { return (float)height; }

	void setWidth(int w) { width = w; }
	void setWidth(float w) { width = (int)w; }

	void setHeight(int h) { height = h; }
	void setHeight(float h) { height = (int)h; }

	void setScreenRes() {
		width = screenResolutions[screenResID].width;
		height = screenResolutions[screenResID].height;
	}


	ConfigDataStruct() {
		dataType = DataEntityType::Config;
		title = "";
		width = 0;
		height = 0;

		textSize = 12;

		currentDatabase = "";
	}

	json toJSON() {
		json data;


		data["title"] = title;
		data["backgroundImage"] = backgroundImage;
		data["screenResID"] = screenResID;

		for (size_t i = 0; i < screenResolutions.size(); i++) {
			data["resolutions"][i][0] = screenResolutions[i].width;
			data["resolutions"][i][1] = screenResolutions[i].height;
		}


		data["fullscreen"] = fullscreen;

		data["textSize"] = textSize;

		data["database"] = currentDatabase;

		return data;
	}

private:
	int width;
	int height;
};