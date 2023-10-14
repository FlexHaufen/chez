/**
 * @file Board.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// *** INCLUDES ***
#include "chez/Board/Board.h"

namespace Chez {


    Board::Board(sf::RenderWindow &window) : 
    m_Window(window) {

        CH_CORE_INFO("Initializing Board");

        if (!m_BoardTexture.loadFromFile(CH_BOARD_TEXTURE_PATH)) {
            CH_CORE_WARN("Board Texture not found!");
        } else {
            CH_CORE_INFO("Current Board size = {0} / {1}", m_BoardTexture.getSize().x, m_BoardTexture.getSize().y);
        }
        m_BoardSprite.setTexture(m_BoardTexture);
        m_BoardSprite.setPosition(sf::Vector2f(0,0));

        m_BoardSprite.setScale(sf::Vector2f(2, 2));
    }


    void Board::OnRender() {
        m_Window.draw(m_BoardSprite);
    }
}