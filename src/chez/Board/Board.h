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





//*** NAMESPACE ***
namespace Chez {



    class Board {
    public:
        
        /**
         * @brief Construct a new Chess Board
         * 
         * @param window    ref sf::RenderWindow 
         */
        Board(sf::RenderWindow &window);         // Ref to EventManager

        /**
         * @brief Update
         * 
         */
        void OnUpdate();

        /**
         * @brief Render
         * 
         */
        void OnRender();

        /**
         * @brief Event
         * 
         * @param e  ref sf::Event
         */
        void OnEvent(sf::Event &e);


        /**
         * @brief Moves a piece from the given square to
         *        the given target square
         * 
         * @param square         square with piece to move
         * @param target_square  square to move piece to
         * @return u8            0: Success, 1: Error
         */
        u8 MovePiece(u8 square, u8 target_square);
    


    private:

        // void SetPiece(u8 square, Piece& piece);
        // Piece& GetPiece(u8 square);     

        /**
         * @brief Sets Board to given FEN-String
         * 
         * @param s         FenString
         */
        void FenToBoard(std::string &s);

        /**
         * @brief Updates sprite at given pos
         *        This Function centers the sprite to the corresponding
         *        square.
         * 
         * @param square 
         */
        void UpdateSpritePos(u8 square);

        /**
         * @brief Drag a Piece at current mouse pos
         * 
         */
        void DragPiece();

        /**
         * @brief Drag a Piece at current mouse pos
         * 
         */
        void DropPiece();

    private:
        // ** Members **    
        sf::RenderWindow   &m_Window;           // Ref to sf::RenderWindow

        // Textures
        sf::Texture         m_BoardTexture;     // texture of Board
        sf::Sprite          m_BoardSprite;      // sprite of Board
        sf::Vector2i        m_SquareSize;       // Size of a single board square
        std::array<sf::RectangleShape, CH_MAX_MOVE_TRACEBACK> m_MoveTracbackSquares;    // Deque for Rectangleshape to store the latest movment markings

        // Drag & Drop
        b8 m_DragActive = false;                // true: Drag is active
        u8 m_DragFromSquare;                    // square from Drag&Drop
        u8 m_DragToSquare;                      // square to Drag&Drop

        Piece_Color m_ColorToMove;              // Color to make next move. 0: White, 1: Black

        // Board
        PieceTextureLookup m_PieceTextureLookup;    // Texture Map for pieces
        
        std::array<Piece*, (CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y)> m_Board = {nullptr};     // Board
    };
}