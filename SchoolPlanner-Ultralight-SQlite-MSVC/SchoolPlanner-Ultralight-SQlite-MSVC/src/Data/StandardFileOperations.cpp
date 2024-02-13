#include "sc_pch.hpp"

#include "StandardFileOperations.hpp"

#include <fstream>


namespace StdFO {
	void setFilePaths(std::string _s) {

	}

	json loadDataFile(std::string _filename, FileType _ft) {
		json data;

		std::ifstream file;

		std::string fullPath = "";
		if (_ft == FileType::json) {
			fullPath = _filename + ".json";
		} else {

		}

		SC_INFO("Loading {0}", fullPath);

		file.open(fullPath);
		if (file) {
			file >> data;
		} else {
			SC_ERROR("Failed to open: {0}", fullPath);
			data = json();
		}

		file.close();

		return data;
	}

	void saveDataFile(std::string _filename, FileType _ft, json& _data) {
		std::ofstream file;
		std::string fullPath = _filename + ".json";
		file.open(fullPath, std::ios::trunc);

		file << _data;

		file.close();
	}
};