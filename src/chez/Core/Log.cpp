/**
 * @file Log.cpp
 * @author flexhaufen
 * @brief logger
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// *** INCLUDES ***
#include "chez/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

// *** DEFINE ***


// *** NAMESPACE ***
namespace Chez {

	//inline std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	//inline std::shared_ptr<spdlog::logger> Log::s_ClientLogger;


	void Log::Init() {
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("chez.log", true));

		// ** Console Log **
		//							"[DD.MM.YY HH:MM:SS.ms][pid][tid] [CORE]: msg]"
		logSinks[0]->set_pattern("%^[%d.%m.%C %T.%e][%P][%t] %n: %v%$");
		// ** File Log **
		//							"[DD.MM.YY HH:MM:SS.ms][pid][tid][level]  [APP]: msg]"
		logSinks[1]->set_pattern("%^[%d.%m.%C %T.%e][%P][%t][%l]\t %n: %v");

		// ** LOGGER **
		// CORE
		s_CoreLogger = std::make_shared<spdlog::logger>("[CORE]", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		// CLIENT		
		s_ClientLogger = std::make_shared<spdlog::logger>("[CLIENT]", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::info);
		s_ClientLogger->flush_on(spdlog::level::info);

		CH_CORE_INFO("-------------------------------------");
		CH_CORE_INFO("Chez_Engine v{0}", CH_VERSION);
		CH_CORE_INFO("-------------------------------------");
		CH_CORE_INFO("Logger Initialized");
	}
}