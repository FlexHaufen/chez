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
        if (!m_PieceTextureLookup[CH_WHITE][4].loadFromFile("./assets/pieces/white-rook.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_WHITE][5].loadFromFile("./assets/pieces/white-queen.png")) { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_WHITE][6].loadFromFile("./assets/pieces/white-king.png"))  { CH_CORE_WARN("Board Texture not found!"); }
    
        if (!m_PieceTextureLookup[CH_BLACK][1].loadFromFile("./assets/pieces/black-pawn.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][2].loadFromFile("./assets/pieces/black-knight.png")){ CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][3].loadFromFile("./assets/pieces/black-bishop.png")){ CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][4].loadFromFile("./assets/pieces/black-rook.png"))  { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][5].loadFromFile("./assets/pieces/black-queen.png")) { CH_CORE_WARN("Board Texture not found!"); }
        if (!m_PieceTextureLookup[CH_BLACK][6].loadFromFile("./assets/pieces/black-king.png"))  { CH_CORE_WARN("Board Texture not found!"); }
    
        // NOTE (flex): FEN test string
        std::string s = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR";
        FenToBoard(s);

    }


    void Board::OnRender() {
        m_Window.draw(m_BoardSprite);
    
        for (u8 i = 0; i < m_Board.size(); i++) {
            sf::Sprite sprite;
            sprite.setTexture(m_PieceTextureLookup[(u8)m_Board[i].color][(u8)m_Board[i].type]);
            // TODO: Define random ass numbers
            sprite.setPosition(sf::Vector2f((u8)(i % 8) * CH_GLOBAL_SCALE * 32, (u8)(i / 8) * CH_GLOBAL_SCALE * 32));
            m_Window.draw(sprite);
        }
    }


    void Board::OnEvent(sf::Event &e) {

    }


    void Board::OnUpdate() {
        // Get Mouse pos
        sf::Vector2i pos(m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window)) / CH_GLOBAL_SCALE);
    }

    u8 Board::MovePiece(u8 square, u8 target_square) {
        if (square >= CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y) {
            CH_CORE_ERROR("access violation: Square [{0}] not in range", square);
            return 1;
        }
        if (target_square >= CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y) {
            CH_CORE_ERROR("access violation: Target_Square [{0}] not in range", target_square);
            return 1;
        }
        SetPiece(target_square, GetPiece(square));
        return 0;
    }


    void Board::SetPiece(u8 square, Piece& piece) {
        if (square >= CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y) {
            CH_CORE_ERROR("access violation: Square [{0}] not in range", square);
            return;
        }
        m_Board[square] = piece;
    }

    Piece& Board::GetPiece(u8 square) {
        if (square >= CH_BOARD_SIZE_X * CH_BOARD_SIZE_Y) {
            CH_CORE_ERROR("access violation: Square [{0}] not in range. Returning 0", square);
            //return nullptr_t;
            return m_Board[0];
        }
        return m_Board[square];
    }


    void Board::FenToBoard(std::string &fen_string) {

        v2 board = {0, 0};

        const std::map<char, Piece_Type> pieceLookupMap {
            {'P', Piece_Type::Pawn },
            {'N', Piece_Type::Knight },
            {'B', Piece_Type::Bishop },
            {'R', Piece_Type::Rook },
            {'Q', Piece_Type::Queen },
            {'K', Piece_Type::King },
        };

        for (char &c : fen_string) {
            if (c == '/' || c == '\\') {
                board.y++;
                board.x = 0;
            }
            else if (c >= '0' && c <= '8') {
                board.x += (int)(c - '0');
            }
            else {
                if (pieceLookupMap.count(c) > 0) {
                    // Key found white
                    Piece p = {pieceLookupMap.at(c), Piece_Color::White };
                    m_Board[board.x + board.y * CH_BOARD_SIZE_X] = p;
                } 
                else {
                    c = toupper(c);
                    if (pieceLookupMap.count(c) > 0) {
                        // Key Found black
                        Piece p = { pieceLookupMap.at(c), Piece_Color::Black };
                        m_Board[board.x + board.y * CH_BOARD_SIZE_X] = p;
                    }
                    else {
                        CH_CORE_ERROR("FEN literal [{0}] not found. passing", c); 
                    }
                }
                board.x++;
            }
        }
    }
}