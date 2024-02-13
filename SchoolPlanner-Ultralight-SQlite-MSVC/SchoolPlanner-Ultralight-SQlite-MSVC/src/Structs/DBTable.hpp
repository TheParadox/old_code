#pragma once

#include "sc_pch.hpp"

enum class TablesEnum {
	None = 0,
	School,
	Library
};

class DBTable {
public:
	DBTable() : m_table(TablesEnum::None) {};

	DBTable(TablesEnum _e) : m_table(_e) {};

	DBTable(int _i) {
		m_table = static_cast<TablesEnum>(_i);
	};

	DBTable(std::string _s) {
		m_table = stringToEnum(_s);
	};

	~DBTable() {};

	//Assignment operators
	DBTable& operator=(const int& _other) {
		m_table = static_cast<TablesEnum>(_other);
		return *this;
	};

	DBTable& operator=(const std::string& _other) {
		m_table = stringToEnum(_other);
		return *this;
	};

	DBTable& operator=(const TablesEnum& _other) {
		m_table = _other;
		return *this;
	};

	DBTable& operator=(const DBTable& _other) {
		if (this == &_other) {
			return *this;
		}

		m_table = _other.m_table;
		return *this;
	};


	//Comparison Operators
	bool operator==(const int& _other) {
		return (m_table == static_cast<TablesEnum>(_other));
	};

	bool operator==(const std::string& _other) {
		return (m_table == stringToEnum(_other));
	};

	bool operator==(const TablesEnum& _other) {
		return (m_table == _other);
	};

	bool operator==(const DBTable& _other) {
		return (m_table == _other.m_table);
	};


	//data type conversions
	int asInt() {
		return static_cast<int>(m_table);
	};

	TablesEnum asEnum() {
		return m_table;
	};

	operator TablesEnum() const {
		return m_table;
	};

	/*operator int() const {
		return static_cast<int>(m_table);
	};

	operator bool() const {
		return (m_table != TablesEnum::None) ? true : false;
	};*/

private:
	TablesEnum stringToEnum(std::string _s) {
		if (_s == "school") {
			return TablesEnum::School;
		} else if (_s == "library") {
			return TablesEnum::Library;
		}

		return TablesEnum::None;
	}

private:
	TablesEnum m_table;
};