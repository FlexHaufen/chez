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

#include "chez/Helper/Convert.h"

namespace Chez {


    Board::Board(sf::RenderWindow &window) : 
    m_Window(window) {

        CH_CORE_INFO("Initializing Board");
        if (!m_BoardTexture.loadFromFile(CH_BOARD_TEXTURE_PATH)) {
            CH_CORE_WARN("Board Texture not found!");
        } else {
            m_SquareSize = sf::Vector2i(m_BoardTexture.getSize().x / CH_BOARD_SIZE_X, m_BoardTexture.getSize().y / CH_BOARD_SIZE_Y);

            m_BoardSprite.setTexture(m_BoardTexture);
            m_BoardSprite.setPosition(sf::Vector2f(0,0));
            m_BoardSprite.setScale(sf::Vector2f(CH_GLOBAL_SCALE, CH_GLOBAL_SCALE));
            CH_CORE_INFO("Current Board size = {0} / {1}", m_BoardTexture.getSize().x, m_BoardTexture.getSize().y);
        }

        

        // NOTE (flex): FEN test string
        std::string s = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR";
        FenToBoard(s);

        // Inizialise Board
        for (u8 i = 0; i < m_Board.size(); i++) {
            if (m_Board[i] == nullptr) {
                continue;
            }
            sf::Texture &t = m_PieceTextureLookup.getTexture(m_Board[i]->type, m_Board[i]->color);
            m_Board[i]->sprite.setTexture(t);
            // Dynamically set Scale
            m_Board[i]->sprite.setScale(sf::Vector2f(m_BoardTexture.getSize().x / t.getSize().x * CH_GLOBAL_SCALE / CH_BOARD_SIZE_X,
                                                    m_BoardTexture.getSize().y / t.getSize().y * CH_GLOBAL_SCALE / CH_BOARD_SIZE_Y));

            UpdateSpritePos(i);
        }
    }


    void Board::OnRender() {
        m_Window.draw(m_BoardSprite);

        for (auto &i : m_MoveTracbackSquares) {
            m_Window.draw(i);
        }

        for (auto &i : m_Board) {
            if (i == nullptr) {
                continue;
            }
            m_Window.draw(i->sprite);
        }
    }


    void Board::OnEvent(sf::Event &e) {

        // FIXME (inj):
        // - Error on moving to the same square
        // - Error on clicken on another square first
        switch(e.type) {
            case sf::Event::MouseButtonPressed:
                if (e.key.code == sf::Mouse::Left) {
                    DragPiece();
                }
                break;
            
            case sf::Event::MouseButtonReleased:
                if (e.key.code == sf::Mouse::Left) {
                    DropPiece();
                }
                break;
            
            default:
                break;
        }
    }


    void Board::OnUpdate() {
        if (m_DragActive) {
            m_Board[m_DragFromSquare]->sprite.setPosition(sf::Vector2f(Convert::getRelativeMousePosition(m_Window)) - sf::Vector2f(64, 64));
        }

            
        
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

        if (target_square != square) {
            CH_CORE_TRACE("Moving: [{0} -> {1}]", square, target_square);
            m_Board[target_square] = m_Board[square];
            m_Board[square] = nullptr;

            // Update Traceback squares
            m_MoveTracbackSquares[0] = Convert::getBoardTracebackRect(m_SquareSize, square, sf::Color(163, 177, 138, 255));
            m_MoveTracbackSquares[1] = Convert::getBoardTracebackRect(m_SquareSize, target_square, sf::Color(88, 129, 87, 255));

        }

        UpdateSpritePos(target_square);
        return 0;
    }

    void Board::UpdateSpritePos(u8 square) {
        if (m_Board[square] == nullptr) {
            CH_CORE_ERROR("access violation: nullptr refrence in UpdateSquarPos", square);
            return;
        }
        m_Board[square]->sprite.setPosition(sf::Vector2f((u8)(square % CH_BOARD_SIZE_X) * CH_GLOBAL_SCALE * m_SquareSize.x, 
                                                         (u8)(square / CH_BOARD_SIZE_X) * CH_GLOBAL_SCALE * m_SquareSize.y));
    }

    void Board::DragPiece() {
        s8 square = Convert::mousePositionToBoardSquare(Convert::getRelativeMousePosition(m_Window), m_SquareSize);
        if (square == -1) { return; }
        if (m_Board[square] == nullptr) { return; }

        m_DragActive = true; 
        m_DragFromSquare = square;
    }

    void Board::DropPiece() {
        if (!m_DragActive) { return; }

        s8 square = Convert::mousePositionToBoardSquare(Convert::getRelativeMousePosition(m_Window), m_SquareSize);

        if (square != -1) {
            m_DragToSquare = square;
        }
        else {
            m_DragToSquare = m_DragFromSquare;
        }
        MovePiece(m_DragFromSquare, m_DragToSquare);
        m_DragActive = false;
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
                    Piece* p = new Piece;
                    p->type = pieceLookupMap.at(c);
                    p->color = Piece_Color::White;
                    m_Board[board.x + board.y * CH_BOARD_SIZE_X] = p;
                } 
                else {
                    c = toupper(c);
                    if (pieceLookupMap.count(c) > 0) {
                        // Key Found black
                        Piece* p = new Piece;
                        p->type = pieceLookupMap.at(c);
                        p->color = Piece_Color::Black;
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