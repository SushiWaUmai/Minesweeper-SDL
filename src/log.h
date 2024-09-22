#pragma once
#include "spdlog/spdlog.h"

#define LOG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_WARNING(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK() __builtin_trap()
#endif

#define LOG_ASSERT(check, msg)	{ if(!check) { LOG_ERROR("Assertion Failed: {0}", msg); DEBUG_BREAK(); } }

#define LOG_LEVEL_TRACE spdlog::level::trace
#define LOG_LEVEL_INFO spdlog::level::info
#define LOG_LEVEL_DEBUG spdlog::level::debug
#define LOG_LEVEL_WARNING spdlog::level::warn
#define LOG_LEVEL_ERROR spdlog::level::err
#define LOG_LEVEL_CRITICAL spdlog::level::critical

#define LOG_SET_LEVEL(level) spdlog::set_level(level)
