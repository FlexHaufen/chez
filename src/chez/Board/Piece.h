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


    enum Piece_Type  { None = 0, Pawn, Knight, Bishop, Rook, Queen, King };
    enum Piece_Color { White = 0, Black = 8};


    /**
     * @brief Chess Piec
     * 
     */
    struct Piece {
        Piece_Color color;
        Piece_Type type;


    }
}