#pragma once
#define SPDLOG_DISABLE_TID_CACHING
#include "spdlog/spdlog.h"
#include "Base.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace TServer {
	class  Log
	{
	public:
		Log();
		~Log();


		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}



// core log macros
#define TSO_CORE_TRACE(...)  ::TServer::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TSO_CORE_INFO(...)   ::TServer::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TSO_CORE_WARN(...)   ::TServer::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TSO_CORE_ERROR(...)  ::TServer::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TSO_CORE_FATAL(...)  ::TServer::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// core client macros
#define TSO_TRACE(...)  ::TServer::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TSO_INFO(...)   ::TServer::Log::GetClientLogger()->info(__VA_ARGS__)
#define TSO_WARN(...)   ::TServer::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TSO_ERROR(...)  ::TServer::Log::GetClientLogger()->error(__VA_ARGS__)
#define TSO_FATAL(...)  ::TServer::Log::GetClientLogger()->fatal(__VA_ARGS__)

