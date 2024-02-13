#pragma once

using json = nlohmann::json;

#define BIND_EVENT_FN_0(fn) std::bind(&fn, this)
#define BIND_EVENT_FN_1(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_FN_2(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2)
