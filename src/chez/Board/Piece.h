/**
 * @file Piece.h
 * @author flexhaufen
 * @brief Pieac
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


//*** NAMESPACE ***
namespace Chez {


    enum class Piece_Type  { None = 0, Pawn, Knight, Bishop, Rook, Queen, King };
    enum class Piece_Color { White = 0, Black = 1, None};


    /**
     * @brief Chess Piec
     * 
     */
    struct Piece {
        Piece_Type type;
        Piece_Color color;

        sf::Sprite  sprite;
    };


    class PieceTextureLookup {
    public:

        PieceTextureLookup() {
            // Load all Pieces
            if (!m_PieceTextureLookup[CH_WHITE][1].loadFromFile("./assets/pieces/white-pawn.png"))  { CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_WHITE][2].loadFromFile("./assets/pieces/white-knight.png")){ CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_WHITE][3].loadFromFile("./assets/pieces/white-bishop.png")){ CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_WHITE][4].loadFromFile("./assets/pieces/white-rook.png"))  { CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_WHITE][5].loadFromFile("./assets/pieces/white-queen.png")) { CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_WHITE][6].loadFromFile("./assets/pieces/white-king.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        
            if (!m_PieceTextureLookup[CH_BLACK][1].loadFromFile("./assets/pieces/black-pawn.png"))  { CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_BLACK][2].loadFromFile("./assets/pieces/black-knight.png")){ CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_BLACK][3].loadFromFile("./assets/pieces/black-bishop.png")){ CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_BLACK][4].loadFromFile("./assets/pieces/black-rook.png"))  { CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_BLACK][5].loadFromFile("./assets/pieces/black-queen.png")) { CH_CORE_WARN("Board Texture not found!"); }
            if (!m_PieceTextureLookup[CH_BLACK][6].loadFromFile("./assets/pieces/black-king.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        }

        /**
         * @brief Get the Texture from given piece information
         * 
         * @param type              Piece type
         * @param color             Piece color
         * @return sf::Texture&     Texture refrence
         */
        sf::Texture& getTexture(Piece_Type type, Piece_Color color) {
            return m_PieceTextureLookup[(u8)color][(u8)type];
        }

    private:

        // ** Members **
        std::array<std::array<sf::Texture, CH_NUM_PIECES>, CH_NUM_PIECE_COLORS> m_PieceTextureLookup;   // Texture Map
    };
}