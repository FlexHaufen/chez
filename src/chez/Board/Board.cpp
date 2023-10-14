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

        // Load all Pieces
        if (!m_PieceTextureLookup[CH_WHITE][1].loadFromFile("./assets/pieces/white-pawn.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_WHITE][2].loadFromFile("./assets/pieces/white-knight.png")){ CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_WHITE][3].loadFromFile("./assets/pieces/white-bishop.png")){ CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_WHITE][4].loadFromFile("./assets/pieces/white-rock.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_WHITE][5].loadFromFile("./assets/pieces/white-queen.png")) { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_WHITE][6].loadFromFile("./assets/pieces/white-king.png"))  { CH_CORE_WARN("Board Texture not found!"); }
    
        if (!m_PieceTextureLookup[CH_BLACK][1].loadFromFile("./assets/pieces/black-pawn.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][2].loadFromFile("./assets/pieces/black-knight.png")){ CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][3].loadFromFile("./assets/pieces/black-bishop.png")){ CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][4].loadFromFile("./assets/pieces/black-rock.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][5].loadFromFile("./assets/pieces/black-queen.png")) { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][6].loadFromFile("./assets/pieces/black-king.png"))  { CH_CORE_WARN("Board Texture not found!"); }
    
    

        Piece p;
        p.color = Piece_Color::White;
        p.type = Piece_Type::King;
    
        m_Board[0] = p;
        m_Board[1] = p;

        m_Board[63] = p;
        m_Board[62] = p;

    
    }


    void Board::OnRender() {
        m_Window.draw(m_BoardSprite);
    
        CH_CORE_TRACE("Boardsize {0}", m_Board.size());

        for (u8 i = 0; i < m_Board.size(); i++) {
            sf::Sprite sprite;
            sprite.setTexture(m_PieceTextureLookup[(u8)m_Board[i].color][(u8)m_Board[i].type]);
            // TODO: Define random ass numbers
            sprite.setPosition(sf::Vector2f((u8)(i / 8) * CH_GLOBAL_SCALE * 32, (u8)(i % 8) * CH_GLOBAL_SCALE * 32));
            m_Window.draw(sprite);
        }
    }


    void Board::SetPiece(u8 square, Piece piece) {
        if (square >= CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y) {
            CH_CORE_ERROR("access violation: Square [{0}] not in range", square);
            return;
        }
        m_Board[square] = piece;
    }

    Piece Board::GetPiece(u8 square) {
        if (square >= CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y) {
            CH_CORE_ERROR("access violation: Square [{0}] not in range. Returning 0", square);
            //return nullptr_t;
            return m_Board[0];
        }
        return m_Board[square];
    }

}