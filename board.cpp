/*-----------------------------------------------------
-	Minesweeper Game Board Code
-	
-	Initial Date: 5/2/2023
-----------------------------------------------------*/

//Included Headers
#include "board.h"
#include <iostream>

void generate_board(std::vector<std::vector<tile*>> &board, int board_y, int board_x, int mines){
	//Variable Declaration
	int i, j;
	
	//Creating a new game tile for each board slot
	for(j = 0; j < board_y; j++){	
		for(i = 0; i < board_x; i++){
			board[j][i] = new tile();
		}
	}	
	
	//Place the mines onto the board
	do{
		//Get random coords to place a mine
		i = (rand() % (board_x - 1 + 1));
		j = (rand() % (board_y - 1 + 1));
		
		//Test if a mine is already there
		//Place one there if not
		if(board[j][i]->get_symbol() == '-'){
			board[j][i]->set_symbol('X');
		}
		//There is already a mine there. Try again
		else{
			continue;
		}
		
		//Decrement the number of mines to place
		mines--;
	}while(mines);
	
	//Filling in the board's numbers
	for(j = 0; j < board_y; j++){	
		for(i = 0; i < board_x; i++){
			//Testing that there is not a mine there
			if(board[j][i]->get_symbol() == '-'){
				generate_number(board, j, i);
			}
		}
	}	
}

void generate_number(std::vector<std::vector<tile*>> &board, int tile_y, int tile_x){
	//Declaring and initialising variables
	int mines = 0;
	
	//Testing if the tile is not on the left border
	if(tile_x){
		if(board[tile_y][tile_x - 1]->get_symbol() == 'X'){
			mines++;
		}
		//Testing if the tile is not on the top border
		if(tile_y){
			if(board[tile_y - 1][tile_x - 1]->get_symbol() == 'X'){
				mines++;
			}
		}
		//Testing if the tile is not on the bottom border
		if(tile_y != (int)board.size() - 1){
			if(board[tile_y + 1][tile_x - 1]->get_symbol() == 'X'){
				mines++;
			}
		}
	}
	//Testing if the tile is not on the top border
	if(tile_y){
		if(board[tile_y - 1][tile_x]->get_symbol() == 'X'){
			mines++;
		}
	}
	//Testing if the tile is not on the bottom border
	if(tile_y != (int)board.size() - 1){
		if(board[tile_y + 1][tile_x]->get_symbol() == 'X'){
			mines++;
		}
	}
	//Testing if the tile is not on the right border
	if(tile_x != (int)board[0].size() - 1){
		if(board[tile_y][tile_x + 1]->get_symbol() == 'X'){
			mines++;
		}
		//Testing if the tile is not on the top border
		if(tile_y){
			if(board[tile_y - 1][tile_x + 1]->get_symbol() == 'X'){
				mines++;
			}
		}
		//Testing if the tile is not on the bottom border
		if(tile_y != (int)board.size() - 1){
			if(board[tile_y + 1][tile_x + 1]->get_symbol() == 'X'){
				mines++;
			}
		}
	}
	
	//Set the number to the respective tile
	board[tile_y][tile_x]->set_symbol('0' + mines);
}

void reveal_tile(std::vector<std::vector<tile*>> &board, int tile_y, int tile_x, int *tiles_left){
	//Test if the tile is already revealed
	if(!board[tile_y][tile_x]->get_revealed()){
		//Reveal the tile
		board[tile_y][tile_x]->reveal();
		board[tile_y][tile_x]->set_flagged(false);
		(*tiles_left)--;
		
		//Test if the tile being revealed is a zero
		if(board[tile_y][tile_x]->get_symbol() == '0'){
			//Testing if the tile is not on the left border
			if(tile_x){
				if(!board[tile_y][tile_x - 1]->get_revealed()){
					reveal_tile(board, tile_y, tile_x - 1, tiles_left);
				}
				//Testing if the tile is not on the top border
				if(tile_y){
					if(!board[tile_y - 1][tile_x - 1]->get_revealed()){
						reveal_tile(board, tile_y - 1, tile_x - 1, tiles_left);
					}
				}
				//Testing if the tile is not on the bottom border
				if(tile_y != (int)board.size() - 1){
					if(!board[tile_y + 1][tile_x - 1]->get_revealed()){
						reveal_tile(board, tile_y + 1, tile_x - 1, tiles_left);
					}
				}
			}
			//Testing if the tile is not on the top border
			if(tile_y){
				if(!board[tile_y - 1][tile_x]->get_revealed()){
					reveal_tile(board, tile_y - 1, tile_x, tiles_left);
				}
			}
			//Testing if the tile is not on the bottom border
			if(tile_y != (int)board.size() - 1){
				if(!board[tile_y + 1][tile_x]->get_revealed()){
					reveal_tile(board, tile_y + 1, tile_x, tiles_left);
				}
			}
			//Testing if the tile is not on the right border
			if(tile_x != (int)board[0].size() - 1){
				if(!board[tile_y][tile_x + 1]->get_revealed()){
					reveal_tile(board, tile_y, tile_x + 1, tiles_left);
				}
				//Testing if the tile is not on the top border
				if(tile_y){
					if(!board[tile_y - 1][tile_x + 1]->get_revealed()){
						reveal_tile(board, tile_y - 1, tile_x + 1, tiles_left);
					}
				}
				//Testing if the tile is not on the bottom border
				if(tile_y != (int)board.size() - 1){
					if(!board[tile_y + 1][tile_x + 1]->get_revealed()){
						reveal_tile(board, tile_y + 1, tile_x + 1, tiles_left);
					}
				}
			}
		}
	}
}