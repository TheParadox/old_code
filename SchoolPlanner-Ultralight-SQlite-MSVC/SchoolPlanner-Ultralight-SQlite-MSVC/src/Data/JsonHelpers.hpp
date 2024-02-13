#pragma once

namespace JH {

	std::string getStdString(json _data, std::string _field, std::string _default = "");

	int getInt(json _data, std::string _field);

	bool getBool(json _data, std::string _field);

};