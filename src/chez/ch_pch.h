/**
 * @file ch_pch.h
 * @author flexhaufen
 * @brief PCH
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

// *** INCLUDES ***

#pragma warning(push, 0)
#include <algorithm>
#include <array>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>
#include <filesystem>
#include <functional>
#include <math.h>
#include <cmath>

// ** External **
// * SFML *
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// * ImGui *
// #define IMGUI_DEFINE_MATH_OPERATORS
// #include "imgui-SFML.h"
// #include "imgui.h"



#pragma warning(pop)


// ** Local **
#include "chez/Helper/Types.h"
#include "chez/Core/Log.h"


// *** DEFINES ***
#define CH_VERSION                          "0.0.2a"

#define CH_WINDOW_RESIZABLE                             // flag
#define CH_WINDOW_X                         1920
#define CH_WINDOW_Y                         1080
#define CH_CALC_FPS

#define CH_SCENE_CLEAR_BACKGROUND           sf::Color(158, 222, 232, 255)   // light blue

#define CH_GLOBAL_SCALE                     2.f          


// ** Board **
#define CH_BOARD_TEXTURE_PATH   "./assets/board.png"
#define CH_PIECE_TEXTURE_PATH   "./assets/pieces"

#define CH_BOARD_SIZE_X 8
#define CH_BOARD_SIZE_Y 8

#define CH_WHITE 0
#define CH_BLACK 1

#define CH_NUM_PIECES       6 + 1
#define CH_NUM_PIECE_COLORS 2


#define CH_MAX_MOVE_TRACEBACK 2