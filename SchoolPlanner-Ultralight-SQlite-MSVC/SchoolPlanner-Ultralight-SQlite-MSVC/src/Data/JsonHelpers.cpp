#include "sc_pch.hpp"
#include "JsonHelpers.hpp"

namespace JH {

	std::string getStdString(json _data, std::string _field, std::string _default) {
		std::string response = _default;

		if (!_data[_field].is_null()) {
			response = _data[_field].get<std::string>();
		}

		return response;
	};


	int getInt(json _data, std::string _field) {
		int response = -1;

		if (!_data[_field].is_null()) {
			response = _data[_field].get<int>();
		}

		return response;
	};

	bool getBool(json _data, std::string _field) {
		bool response = false;

		if (!_data[_field].is_null()) {
			response = _data[_field].get<bool>();
		}

		return response;
	};

};