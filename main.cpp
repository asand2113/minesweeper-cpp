/*-----------------------------------------------------
-	Main Minesweeper Game Code
-
-	Initial Date: 5/2/2023
-----------------------------------------------------*/

//Included Headers
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>
#include <atomic>
#include "board.h"

//Global Variables
std::atomic<bool> end_thread (false);
int game_time;

//Game counting function for the 
void count(){
	game_time = 0;
	while(game_time != 9999){
		if(end_thread){
			break;
		}
		game_time++;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

int main(int argv, char* argc[]){
	//Variable Declaration
	int scr_y, scr_x, input, print_x = 2, print_y = 2, tiles_left, colour, board_x, board_y, mines, finish_code = 0;
	WINDOW* game_end;
	
	//Briefly initialising a window to get the terminal's current size
	initscr();
	getmaxyx(stdscr, scr_y, scr_x);
	endwin();
	
	//Prompting the user for the board width
	std::cout << "Please input a width for the board (12-" << (scr_x / 2) - 3 << "): ";
	std::cin >> board_x;
	//Testing if the input is valid
	if(board_x < 12 || board_x > (scr_x / 2) - 3){
		std::cout << "Error: Invalid width given" << std::endl;
		exit(1);
	}
	
	//Prompting the user for the board height
	std::cout << "Please input a height for the board (3-" << (scr_y / 2) - 3 << "): ";
	std::cin >> board_y;
	//Testing if the input is valid
	if(board_y < 3 || board_y > (scr_y / 2) - 3){
		std::cout << "Error: Invalid height given" << std::endl;
		exit(1);
	}
	
	//Prompting the user for the number of mines
	std::cout << "Please input the number of mines to play with (1-" << (board_x * board_y) - 1 << "): ";
	std::cin >> mines;
	//Testing if the input is valid
	if(mines < 1 || mines > (board_x * board_y) - 1){
		std::cout << "Error: Invalid number of mines given" << std::endl;
		exit(1);
	}
	
	//Declare the board
	std::vector<std::vector<tile*>> board(board_y, std::vector<tile*> (board_x));
	
	//Seeding the random numbers
	srand(time(NULL));
	
	//Generate the Board
	generate_board(board, board_y, board_x, mines);
	
	//Enable mouse movement tracking
	printf("\033[?1003h\n");
	
	//Initialise ncurses space
	initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	cbreak();
	mouseinterval(0);
	
	//Starting terminal colours
	if(start_color() == ERR || !has_colors()){
		endwin();
		printf("Error: Colour could not be initialised!\n");
		exit(1);
	}
	
	//Initialising ncurses colours
	init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
	
	//Setting correct terminal size
	resizeterm(board_y * 2 + 3, board_x * 2 + 3);
	
	//Setting up the screen's border
	border('|', '|', '-', '-', '+', '+', '+', '+');
	
	//Printing out the board
	for(std::vector<tile*> vect1D : board){
		for(tile* x : vect1D){
			x->get_symbol(); //This needs to be here or x will count as unused
			//Print the unrevealed symbol
			mvaddch(print_y, print_x, '-');
			print_x += 2;
		}
		//Move the cursor to the start of the next line
		print_y += 2;
		print_x = 2;
		move(print_y, print_x);
	}
	
	//Get all of the mouse event
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	
	//Starting the timer thread
	std::thread thread_obj(count);
	
	//Calculate the number of tiles the player must reveal
	tiles_left = (board_x * board_y) - mines;
	
	//Main Game Loop
	do{
		mvprintw(1, 2, "                        ");
		mvprintw(1, 2, "Mines Remaining: %d", mines);
		
		//Resetting the cursor position variables
		print_x = 2;
		print_y = 2;
		//Printing out the board
		for(std::vector<tile*> vect1D : board){
			for(tile* x : vect1D){
				x->get_symbol(); //This needs to be here or x will count as unused
				//Print a flag if flagged
				if(board[print_y / 2 - 1][print_x / 2 - 1]->get_flagged()){
					attron(COLOR_PAIR(COLOR_RED));
					mvaddch(print_y, print_x, 'F');
					attroff(COLOR_PAIR(COLOR_RED));	
				}
				//Otherwise, print it if it is revealed
				else if(board[print_y / 2 - 1][print_x / 2 - 1]->get_revealed()){
					//Testing what symbol is being revealed to give it the correct colour
					switch(board[print_y / 2 - 1][print_x / 2 - 1]->get_symbol()){
						case '0':
							colour = COLOR_WHITE;
							break;
						case '1':
							colour = COLOR_CYAN;
							break;
						case '2':
							colour = COLOR_MAGENTA;
							break;
						case '3':
							colour = COLOR_GREEN;
							break;
						case '4':
							colour = COLOR_YELLOW;
							break;
						case '5':
							colour = COLOR_CYAN;
							break;
						case '6':
						case '7':
						case '8':
							colour = COLOR_BLUE;
							break;
					}
					//Set the colour to print in
					attron(COLOR_PAIR(colour));
					//Print out the tile
					mvprintw(print_y, print_x, "%c", board[print_y / 2 - 1][print_x / 2 - 1]->get_symbol());
					//Remove the colour
					attroff(COLOR_PAIR(colour));	
				}
				//Otherwise, print the unrevealed tile
				else{
					mvprintw(print_y, print_x, "%c", '-');
				}
				print_x += 2;
			}
			//Move the cursor to the start of the next line
			print_y += 2;
			print_x = 2;
			move(print_y, print_x);
		}
		
		//Displaying the board
		refresh();
		
		//The game is won if there are no non-mine tiles left to reveal
		if(!tiles_left){
			finish_code = 1;
			break;
		}
		
		//Get user input
		input = wgetch(stdscr);
		
		//Testing user input
		if (input == KEY_MOUSE) {
			MEVENT event;
			if (getmouse(&event) == OK) {
				int y_coord = event.y / 2 - 1;
				int x_coord = event.x / 2 - 1;
				if(x_coord < 0 || y_coord < 0 || x_coord >= board_x || y_coord >= board_y){
					continue;
				}
				//Check if it was left click
				if(event.bstate & BUTTON1_PRESSED && !board[y_coord][x_coord]->get_revealed()){
					//Reveal the tile
					reveal_tile(board, y_coord, x_coord, &tiles_left);
					//Lose the game if the revealed tile was a mine
					if(board[y_coord][x_coord]->get_symbol() == 'X'){
						break;
					}
				}
				//Check if it was right click
				else if(event.bstate & BUTTON3_PRESSED){
					//Testing if the tile has already been revealed
					if(!board[y_coord][x_coord]->get_revealed()){
						//If not, flag it
						board[y_coord][x_coord]->flag();
						//Decreases mine count in the tile was just flagged
						if(board[y_coord][x_coord]->get_flagged()){
							mines--;
						}
						//Otherwise, the tile was just unflagged, so mine count increases
						else{
							mines++;
						}
					}
				}
			}
		}
		
	}while(input != 'q');
	
	//End the thread
	end_thread = true;
	thread_obj.join();
	
	//Initialising the game ending screen
	if(!(game_end = newwin(6, 24, 2, 2))){
		//Exits program if the window failed initialisation
		noraw();
		endwin();
		printf("Critical Error: Window could not be allocated!\n");
		exit(1);
	}

	//Print the game over menu's border
	wborder(game_end, '|', '|', '-', '-', '+', '+', '+', '+');
	
	//Testing if the game was lost
	if(!finish_code){
		mvwprintw(game_end, 1, 2, "You Lose!");
	}
	//Otherwise, the game is won
	else{
		mvwprintw(game_end, 1, 2, "You Win!");
		mvwprintw(game_end, 2, 2, "Your Score was: %d", game_time);
	}
	
	//Print the quit instructions
	mvwprintw(game_end, 4, 2, "Press \'q\' to Quit");
	
	//Refresh the game over window
	wrefresh(game_end);
	
	//Wait for the user to exit the program
	do{
		//Getting user input
		input = wgetch(game_end);
	}while(input != 'q');
	
	//Deleting all of the tile objects from memory
	for(std::vector<tile*> vect1D : board){
		for(tile* x : vect1D){
			delete(x);
		}
		std::cout << std::endl;
	}
	
	//Ending the ncurses window
	delwin(game_end);
	noraw();
	endwin();
	
	//Diable mouse movement tracking
	printf("\033[?1003l\n");
	
	return 0;
}