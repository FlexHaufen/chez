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
        static sf::Vector2i getRelativeMousePosition(sf::RenderWindow &window) {
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
        static s8 mousePositionToBoardSquare(sf::Vector2i pos, sf::Vector2i squareSize) {
            // Get mouse pos
            sf::Vector2i pos_board(pos.x / (CH_GLOBAL_SCALE * squareSize.x), pos.y / (CH_GLOBAL_SCALE * squareSize.y)); // Pos in board pixels
            // Check if mouse is over game board
            if (pos_board.x < CH_BOARD_SIZE_X && pos_board.y < CH_BOARD_SIZE_Y) {
                // Calculate square 
                return (pos_board.x + pos_board.y * CH_BOARD_SIZE_X);
            }
            return -1;
        }

        /**
         * @brief Get a traceback rectangle for latest move
         *        at given square
         * @param squareSize    single squaresize of board [px]
         * @param square        index of square
         * @param color         color of rect
         * @return sf::RectangleShape 
         */
        static sf::RectangleShape getBoardTracebackRect(sf::Vector2i squareSize, u8 square, sf::Color color) {
            sf::RectangleShape rect;

            rect.setSize(sf::Vector2f(squareSize));
            // Dynamically set Scale
            rect.setScale(sf::Vector2f(CH_GLOBAL_SCALE,
                                       CH_GLOBAL_SCALE));

            rect.setPosition(sf::Vector2f((u8)(square % CH_BOARD_SIZE_X) * CH_GLOBAL_SCALE * squareSize.x, 
                                          (u8)(square / CH_BOARD_SIZE_X) * CH_GLOBAL_SCALE * squareSize.y));

            rect.setFillColor(color);

            return rect;
        }


        /**
         * @brief Compares the aspect ratio of the window to the aspect ratio of the view,
         *        and sets the view's viewport accordingly in order to archieve a letterbox effect.
         *        A new view (with a new viewport set) is returned.
         * 
         * @param view          sf::View
         * @param windowWidth   
         * @param windowHeight 
         * @return sf::View 
         */
        static void getLetterboxView(sf::View &view, s32 windowWidth, s32 windowHeight) {
            f32 windowRatio = windowWidth / (f32)windowHeight;
            f32 viewRatio = view.getSize().x / (f32)view.getSize().y;
            f32 sizeX = 1;
            f32 sizeY = 1;
            f32 posX = 0;
            f32 posY = 0;

            b8 horizontalSpacing = (windowRatio >= viewRatio);

            // If horizontalSpacing is true, the black bars will appear on the left and right side.
            // Otherwise, the black bars will appear on the top and bottom.
            if (horizontalSpacing) {
                sizeX = viewRatio / windowRatio;
                posX = (1 - sizeX) / 2.f;
            }
            else {
                sizeY = windowRatio / viewRatio;
                posY = (1 - sizeY) / 2.f;
            }

            view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
            return;
        }
    }
}