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

#include "chez/Board/Piece.h"

//*** DEFINES ***
#define CH_BOARD_SIZE_X 8
#define CH_BOARD_SIZE_Y 8

#define CH_WHITE 0
#define CH_BLACK 1

#define CH_BOARD_TEXTURE_PATH   "./assets/board.png"
#define CH_PIECE_TEXTURE_PATH   "./assets/pieces"


#define CH_NUM_PIECES       6 + 1
#define CH_NUM_PIECE_COLORS 2





//*** NAMESPACE ***
namespace Chez {



    class Board {
    public:
        
        Board(sf::RenderWindow &window);

        void OnRender();
    
    private:

        void SetPiece(u8 square, Piece piece);
        Piece GetPiece(u8 square);        

    private:
        // ** Members **    

        // rendering
        sf::RenderWindow   &m_Window;   // Ref to sf::RenderWindow

        // Textures
        sf::Texture         m_BoardTexture;
        sf::Sprite          m_BoardSprite;
        
        std::array<std::array<sf::Texture, CH_NUM_PIECES>, CH_NUM_PIECE_COLORS> m_PieceTextureLookup;

        std::array<Piece, (CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y)> m_Board = { };     // Board


        void FenToBoard(std::string &s);


    };
}