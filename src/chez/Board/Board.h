/**
 * @file Board.h
 * @author flexhaufen
 * @brief Board
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

// *** INCLUDES ***
#include "chez/ch_pch.h"

//*** DEFINES ***
#define CH_BOARD_SIZE_X 8
#define CH_BOARD_SIZE_Y 8

#define CH_BOARD_TEXTURE_PATH   "./assets/board.png"


//*** NAMESPACE ***
namespace Chez {



    class Board {
    public:
        
        Board(sf::RenderWindow &window);

        void OnRender();
    
        
        

    private:
        // ** Members **    

        // rendering
        sf::RenderWindow   &m_Window;   // Ref to sf::RenderWindow

        sf::Texture         m_BoardTexture;
        sf::Sprite          m_BoardSprite;
        
        //std::array<u32, CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y> m_Board;     // Board

    };


}