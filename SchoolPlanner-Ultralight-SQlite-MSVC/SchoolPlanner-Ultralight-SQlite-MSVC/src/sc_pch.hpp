#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "sqlite/sqlite3.h"
#include "SQL/DBHelpers.hpp"

#include "Data/nlohmann/json.hpp"
using json = nlohmann::json;
#include "Data/JsonHelpers.hpp"

#include "Log.hpp"

#include "Data/StandardFileOperations.hpp"

namespace SC {
	template<typename T>
	using ScopePtr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr ScopePtr<T> CreateScopePtr(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using RefPtr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr RefPtr<T> CreateRefPtr(Args&&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using LinkPtr = std::weak_ptr<T>;


};


#define SC_CALLBACK_0(fn) std::bind(&fn, this)
#define SC_CALLBACK_1(fn) std::bind(&fn, this, std::placeholders::_1)
#define SC_CALLBACK_2(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2)
#define SC_CALLBACK_3(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define SC_CALLBACK_4(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define SC_CALLBACK_5(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)