/**
 * @file Core.h
 * @author flexhaufen
 * @brief core
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

// *** INCLUDES ***
#include "chez/ch_pch.h"
#include "chez/Core/Events/EventManager.h"


#include "chez/Board/Board.h"

//*** DEFINES ***


//*** NAMESPACE ***
namespace Chez {

    /**
     * @brief Core class of Game
     * 
     */
    class Core {

    public:

        /**
         * @brief Construct a new Core object
         * 
         */
        Core();

        /**
         * @brief Destroy the Core object
         * 
         */
        ~Core();

        /**
         * @brief Running loop
         * 
         */
        void Run();

        /**
         * @brief Closes App
         * 
         */
        void Close();

    private:
    
        /**
         * @brief Game loop of app
         * 
         */
        void OnUpdate();

        /**
         * @brief Performe a HotReload
         * 
         */
        void PerformHotReload();

    private:
        // ** Members **
        sf::Clock m_dt_clock;           // Sfml Clock for DeltaTime
        sf::Time m_dt;                  // DeltaTime

        b8 m_isRunning = true;          // True when app is running
        b8 m_isPaused = false;          // True when app is paused
        b8 m_isMinimized = false;       // True when app is minimzed
        b8 m_UpdateGame = true;         // True when game should be updated

        sf::RenderWindow m_Window;      // Sfml window
        std::string m_WindowTitle;      // Sfml window title



        Ref<Board>      m_Board;        // Game Board

        EventManager m_EventManager;    // Event manager

    };
}