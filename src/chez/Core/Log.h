/**
 * @file Log.h
 * @author flexhaufen
 * @brief logger
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

// *** INCLUDES ***


// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
    #include <spdlog/spdlog.h>
    #include <spdlog/fmt/ostr.h>
#pragma warning(pop)

//*** DEFINES ***
#ifndef NLY_DEBUG
    #define CH_LOGGER_ENABLE
#else
    // TODO: This will change later -> maby logger is only file logging is enabled
    #define CH_LOGGER_ENABLE
#endif


//*** NAMESPACE ***
namespace Chez {
    /**
     * @brief Logger Class
     * 
     */
	class Log {
	public:
        /**
         * @brief initializes the logger
         * 
         */
		static void Init();

        /**
         * @brief Get the Core Logger object
         * 
         * @return std::shared_ptr<spdlog::logger>& 
         */
		static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

        /**
         * @brief Get the Client Logger object
         * 
         * @return std::shared_ptr<spdlog::logger>& 
         */
		static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:

        //*** MEMBERS ***
		static inline std::shared_ptr<spdlog::logger> s_CoreLogger;     // Core Logger
		static inline std::shared_ptr<spdlog::logger> s_ClientLogger;   // Client Logger
	};

}

#ifdef CH_LOGGER_ENABLE
    // Core log macros
    #define CH_CORE_TRACE(...)    ::Chez::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define CH_CORE_INFO(...)     ::Chez::Log::GetCoreLogger()->info(__VA_ARGS__)
    #define CH_CORE_WARN(...)     ::Chez::Log::GetCoreLogger()->warn(__VA_ARGS__)
    #define CH_CORE_ERROR(...)    ::Chez::Log::GetCoreLogger()->error(__VA_ARGS__)
    #define CH_CORE_CRITICAL(...) ::Chez::Log::GetCoreLogger()->critical(__VA_ARGS__)

    // Client log macros
    #define CH_TRACE(...)         ::Chez::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define CH_INFO(...)          ::Chez::Log::GetClientLogger()->info(__VA_ARGS__)
    #define CH_WARN(...)          ::Chez::Log::GetClientLogger()->warn(__VA_ARGS__)
    #define CH_ERROR(...)         ::Chez::Log::GetClientLogger()->error(__VA_ARGS__)
    #define CH_CRITICAL(...)      ::Chez::Log::GetClientLogger()->critical(__VA_ARGS__)

#else
    // Core log macros
    #define CH_CORE_TRACE(...)   
    #define CH_CORE_INFO(...)     
    #define CH_CORE_WARN(...)     
    #define CH_CORE_ERROR(...)    
    #define CH_CORE_CRITICAL(...) 

    // Client log macros
    #define CH_TRACE(...)         
    #define CH_INFO(...)          
    #define CH_WARN(...)          
    #define CH_ERROR(...)         
    #define CH_CRITICAL(...)      
#endif