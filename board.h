/*-----------------------------------------------------
-	Minesweeper Board Data Header
-	Defines the prototypes used in board.cpp
-	
-	Initial Date: 5/2/2023
-----------------------------------------------------*/

//Header guard
#ifndef BOARD_H
#define BOARD_H

//Included Headers
#include <vector>
#include "tile.h"

/* Function used to generate the game board
 * board: The board to generate
 * board_y: The height of the board
 * board_x: The width of the board
 * mines: The number of mines to generate
 */
void generate_board(std::vector<std::vector<tile*>> &board, int board_y, int board_x, int mines);

/* Function used to generate a tile's number
 * board: The board to generate in
 * tile_y: The y-coordinate of the tile
 * tile_x: The x-coordinate of the tile
 */
void generate_number(std::vector<std::vector<tile*>> &board, int tile_y, int tile_x);

/* Function used to reveal a tile
 * board: The board to reveal the tile on
 * tile_y: The y-coordinate of the tile
 * tile_x: The x-coordinate of the tile
 * *tiles_left: Pointer to the number of tiles left to reveal
 */
void reveal_tile(std::vector<std::vector<tile*>> &board, int tile_y, int tile_x, int *tiles_left);

#endif