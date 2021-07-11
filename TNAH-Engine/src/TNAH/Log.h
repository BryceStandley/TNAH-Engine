#pragma once

#include "Core.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace tnah
{
	class TNAH_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define TNAH_CORE_TRACE(...)    ::tnah::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TNAH_CORE_INFO(...)     ::tnah::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TNAH_CORE_WARN(...)     ::tnah::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TNAH_CORE_ERROR(...)    ::tnah::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TNAH_CORE_FATAL(...)    ::tnah::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define TNAH_TRACE(...)	      ::tnah::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TNAH_INFO(...)	      ::tnah::Log::GetClientLogger()->info(__VA_ARGS__)
#define TNAH_WARN(...)	      ::tnah::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TNAH_ERROR(...)	      ::tnah::Log::GetClientLogger()->error(__VA_ARGS__)
#define TNAH_FATAL(...)	      ::tnah::Log::GetClientLogger()->critical(__VA_ARGS__) 