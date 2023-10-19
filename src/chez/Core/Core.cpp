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

#include "chez/Helper/Convert.h"

// *** NAMESPACE ***
namespace Chez {

    Core::Core() {
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

        // Setup View
        m_View.setSize(CH_WINDOW_X, CH_WINDOW_Y);
        m_View.setCenter(m_View.getSize().x / 2, m_View.getSize().y / 2 );
        Convert::getLetterboxView(m_View, CH_WINDOW_X, CH_WINDOW_Y);  

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
        // *** LOOP ***
        while (m_isRunning) {
            OnEvent();
            OnUpdate();
        }
    }

    void Core::Close() {
        CH_CORE_INFO("Quitting Core");
        m_isRunning = false;
        m_Window.close();
    }


    void Core::OnEvent() {
        sf::Event e;
        while (m_Window.pollEvent(e)) {

            m_Board->OnEvent(e);

            switch(e.type) {
                case sf::Event::Resized:
                    // update the view to the new size of the window
                    Convert::getLetterboxView(m_View, e.size.width, e.size.height );
                    break;

                case sf::Event::Closed:
                    Close();
                    break;
            }
        }
    }


    void Core::OnUpdate() {

        m_dt = m_dt_clock.restart();
        f32 dt_sec = m_dt.asSeconds();  // Getting dt [s]
        u16 fps = u16(1/dt_sec);        // Getting fps
        m_Window.setTitle(m_WindowTitle + " - FPS: " + std::to_string(fps));

        // ---- UPDATE HANDLING ----
        m_Board->OnUpdate();

        // ---- RENDER LOOP ----
        m_Window.clear(CH_SCENE_CLEAR_BACKGROUND);
        m_Window.setView(m_View);
        m_Board->OnRender();

        m_Window.display();
    }
}