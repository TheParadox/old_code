#pragma once

namespace StdFO {
	enum class FileType {
		json
	};

	void setFilePaths(std::string _s);

	json loadDataFile(std::string _filename, FileType _ft);
	void saveDataFile(std::string _filename, FileType _ft, json& _data);


};