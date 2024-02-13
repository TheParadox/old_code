#pragma once

#include "Core.hpp"

namespace FileHandler {
	extern std::string n_mainDataFolder;
	extern std::string n_mainFilename;

	extern std::string n_playerConfigFilename;

	bool loadMainDataFile();
	json loadPlayerConfigs();

	json loadJsonFile(std::string);

	void saveJsonFile(std::string, json);

};