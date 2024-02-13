#pragma once

#include "sc_pch.hpp"

enum class MethodsEnum {
	None = 0,
	Create,
	Update,
	SelectOne,
	SelectAll
};

class DBMethod {
public:
	DBMethod() : m_method(MethodsEnum::None) {};

	DBMethod(MethodsEnum _e) : m_method(_e) {};

	DBMethod(int _i) {
		m_method = static_cast<MethodsEnum>(_i);
	};

	DBMethod(std::string _s) {
		m_method = stringToEnum(_s);
	};

	~DBMethod() {};

	//Assignment operators
	DBMethod& operator=(const int& _other) {
		m_method = static_cast<MethodsEnum>(_other);
		return *this;
	};

	DBMethod& operator=(const std::string& _other) {
		m_method = stringToEnum(_other);
		return *this;
	};

	DBMethod& operator=(const MethodsEnum& _other) {
		m_method = _other;
		return *this;
	};

	DBMethod& operator=(const DBMethod& _other) {
		if (this == &_other) {
			return *this;
		}

		m_method = _other.m_method;
		return *this;
	};



	//Comparison Operators
	bool operator==(const int& _other) {
		return (m_method == static_cast<MethodsEnum>(_other));
	};

	bool operator==(const std::string& _other) {
		return (m_method == stringToEnum(_other));
	};

	bool operator==(const MethodsEnum& _other) {
		return (m_method == _other);
	};

	bool operator==(const DBMethod& _other) {
		return (m_method == _other.m_method);
	};


	//data type conversions
	int asInt() {
		return static_cast<int>(m_method);
	};

	MethodsEnum asEnum() {
		return m_method;
	};


	//Default return type...
	operator MethodsEnum() const {
		return m_method;
	};

private:
	MethodsEnum stringToEnum(std::string _s) {
		if (_s == "create") {
			return MethodsEnum::Create;
		} else if (_s == "update") {
			return MethodsEnum::Update;
		} else if (_s == "selectOne") {
			return MethodsEnum::SelectOne;
		} else if (_s == "selectAll") {
			return MethodsEnum::SelectAll;
		}

		return MethodsEnum::None;
	};

private:
	MethodsEnum m_method;

};