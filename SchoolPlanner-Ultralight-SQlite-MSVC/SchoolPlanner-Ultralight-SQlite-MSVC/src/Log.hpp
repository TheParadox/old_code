#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

class Log {
public:
	static void init();

	inline static std::shared_ptr<spdlog::logger>& getLogger() { return s_logger; }

private:
	static std::shared_ptr<spdlog::logger> s_logger;
};

#define SC_TRACE(...) ::Log::getLogger()->trace(__VA_ARGS__)
#define SC_INFO(...) ::Log::getLogger()->info(__VA_ARGS__)
#define SC_WARN(...) ::Log::getLogger()->warn(__VA_ARGS__)
#define SC_ERROR(...) ::Log::getLogger()->error(__VA_ARGS__)
#define SC_CRITICAL(...) ::Log::getLogger()->critical(__VA_ARGS__)