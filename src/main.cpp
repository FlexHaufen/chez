/**
 * @file main.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//*** INCLUDES ***
#include "chez/Chez.h"

//*** MAIN ***
int main(int argc, char **argv) {

	Chez::Core* ch_game = new Chez::Core();
	ch_game->Run();
	delete ch_game;


    return 0;
}