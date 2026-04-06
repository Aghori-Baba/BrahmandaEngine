// Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

#pragma once

#include <spdlog/spdlog.h>

namespace Logger
{
	inline void InitLogger()
	{
#if ENABLE_LOGGER
		spdlog::set_pattern("[%T] [%^%l%$] %v");
		spdlog::set_level(spdlog::level::trace);
#endif // ENABLE_LOGGER
	}

	template<typename... Args>
	inline void Info(const char* fmt, Args&&... args)
	{
#if ENABLE_LOGGER
		spdlog::info(fmt, std::forward<Args>(args)...);
#endif // ENABLE_LOGGER
	}

	template<typename... Args>
	inline void Warn(const char* fmt, Args&&... args)
	{
#if ENABLE_LOGGER
		spdlog::warn(fmt, std::forward<Args>(args)...);
#endif // ENABLE_LOGGER
	}

	template<typename... Args>
	inline void Error(const char* fmt, Args&&... args)
	{
#if ENABLE_LOGGER
		spdlog::error(fmt, std::forward<Args>(args)...);
#endif // ENABLE_LOGGER
	}

	inline void Fatal(const char* fmt)
	{
#if ENABLE_LOGGER
		spdlog::critical("FATAL: {}", fmt);
		std::abort();
#endif // ENABLE_LOGGER
	}
}