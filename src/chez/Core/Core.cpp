/**
 * @file Core.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// *** INCLUDES ***
#include "chez/Core/Core.h"

// *** NAMESPACE ***
namespace Chez {

    Core::Core() :
        m_EventManager(m_Window) {
        Log::Init();

        // random number seed
        srand((u32)time(NULL));

        CH_CORE_INFO("Initializing Core");


        std::filesystem::current_path("./");
        CH_CORE_INFO("Running in: {0}",std::filesystem::current_path());
        
        CH_CORE_INFO("Creating Window");
        m_WindowTitle = "chez v";
        m_WindowTitle.append(CH_VERSION);
        m_Window.create(sf::VideoMode(CH_WINDOW_X, CH_WINDOW_Y), m_WindowTitle);

        //sf::Image icon;
        //if (!icon.loadFromFile(AC_WINDOW_ICON_PATH)) {
        //    CH_CORE_WARN("Can't open application icon");
        //}
        //else {
        //    m_Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        //}



        m_Board = CreateRef<Board>(m_Window);

        m_isRunning = true;        
    }

    Core::~Core() {
        CH_CORE_INFO("Shutting down Core");

        CH_CORE_INFO("Closing Window");
        m_Window.close();
    }

    void Core::Run() {
        CH_CORE_INFO("Setting up EventManager");
        m_EventManager.addEventCallback(sf::Event::EventType::Closed, [&](const sf::Event&) { Close(); });
        m_EventManager.addKeyPressedCallback(sf::Keyboard::Key::Escape, [&](const sf::Event&) {Close(); });
        m_EventManager.addKeyPressedCallback(sf::Keyboard::P, [&](const sf::Event&) { m_isPaused = !m_isPaused; });
        m_EventManager.addKeyPressedCallback(sf::Keyboard::H, [&](const sf::Event&) { PerformHotReload(); });

        // *** LOOP ***
        while (m_isRunning) {
            while (m_UpdateGame) {
                OnUpdate();
            }
            m_UpdateGame = true;
        }
    }

    void Core::Close() {
        CH_CORE_INFO("Quitting Core");
        m_isRunning = false;
        m_UpdateGame = false;
        m_Window.close();
    }

    void Core::OnUpdate() {
        // ---- EVENT HANDLING ----
        m_EventManager.processEvents(nullptr);

        if (!m_isPaused) {
            m_dt = m_dt_clock.restart();
            f32 dt_sec = m_dt.asSeconds();  // Getting dt [s]
            u16 fps = u16(1/dt_sec);        // Getting fps
            m_Window.setTitle(m_WindowTitle + " - FPS: " + std::to_string(fps));

            // ---- UPDATE HANDLING ----

            // ---- RENDER LOOP ----
            m_Window.clear(CH_SCENE_CLEAR_BACKGROUND);
            m_Board->OnRender();

            m_Window.display();
        } 
        else {
            m_Window.setTitle(m_WindowTitle + " - PAUSED");
        }
    }

    void Core::PerformHotReload() {
        CH_CORE_INFO("---- HOT RELOAD ----");
        m_UpdateGame = false;
    }
}