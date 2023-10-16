/**
 * @file Convert.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2023-10-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

// *** INCLUDES ***
#include "chez/ch_pch.h"

namespace Chez {
    namespace Convert {

        /**
         * @brief Gets mouse position relative to screen
         * 
         * @param window            sf::RenderWindow
         * @return sf::Vector2i     Mouse postition
         */
        sf::Vector2i getRelativeMousePosition(sf::RenderWindow &window) {
            return sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }

        /**
         * @brief Gets chess square from mouse position
         * @warning Mouse position must be relative to screen
         * 
         * @param pos           Mouse position 
         * @param boardSize     size of a single Boardsquare
         * @return s8           Returns chess square (0 - 63), -1: Error
         */
        s8 mousePositionToBoardSquare(sf::Vector2i pos, sf::Vector2i squareSize) {
            // Get mouse pos
            sf::Vector2i pos_board(pos.x / (CH_GLOBAL_SCALE * squareSize.x), pos.y / (CH_GLOBAL_SCALE * squareSize.y)); // Pos in board pixels
            // Check if mouse is over game board
            if (pos_board.x < CH_BOARD_SIZE_X && pos_board.y < CH_BOARD_SIZE_Y) {
                // Calculate square 
                return (pos_board.x + pos_board.y * CH_BOARD_SIZE_X);
            }
            return -1;
        }
    }
}