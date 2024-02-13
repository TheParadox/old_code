#include "pch.hpp"
#include "FileHandler.hpp"

namespace FileHandler {

	std::string n_mainFilename = "StartupConfigurations";

	std::string n_mainDataFolder = "";

	std::string n_playerConfigFilename = "";


	bool loadMainDataFile() {
		json data;
		data = loadJsonFile(n_mainFilename);

		if (data == NULL) {
			LOG_FATAL("No Main Data file, quiting");
			return false;
		}

		n_mainDataFolder = data["MainDataFolder"];
		n_playerConfigFilename = data["PlayerConfig"];


		return true;
	}

	json loadPlayerConfigs() {
		json data = loadJsonFile(n_mainDataFolder + n_playerConfigFilename);
		if (data == NULL) {
			LOG_FATAL("No Player Configurations file, quiting");
		}

		return data;
	}
	;
	
	json loadJsonFile(std::string fn) {
		std::ifstream file;
		json data;


		file.open(fn + ".json");
		if (file.is_open()) {
			file >> data;
		} else {
			LOG_ERROR("FILE: " + fn + " Not found!");
			data = NULL;
		}

		file.close();

		return data;
	}

	void saveJsonFile(std::string fn, json data) {
		std::ofstream file;

		file.open(fn + ".json");
		if (file.is_open()) {
			file << data;
		} else {
			LOG_ERROR("FILE: " + fn + " Not found!");
		}

		file.close();
	}

};