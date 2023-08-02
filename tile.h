/*-----------------------------------------------------
-	Minesweeper Tile Data Header
-	Defines the tile class used in the 
-	Minesweeper game
-	
-	Initial Date: 5/2/2023
-----------------------------------------------------*/

//Header guard
#ifndef TILE_H
#define TILE_H

//Class for storing information about a game tile
class tile {
	private:
		char symbol;
		bool has_flag;
		bool revealed;
	public:
		//Default constructor
		tile() {
			symbol = '-';
			has_flag = false;
			revealed = false;
		}
		//Destructor
		~tile() {}
		
		//Getters
		char get_symbol() const { return symbol; }
		bool get_flagged() const { return has_flag; }
		bool get_revealed() const { return revealed; }
		
		//Setters
		void set_symbol(char n) { symbol = n; }
		void set_flagged(bool n) { has_flag = n; }
		void set_revealed(bool n) { revealed = n; }
		
		//Toggles whether or not the tile is flagged
		void flag() { has_flag = !has_flag; }
		//Reveals the tile
		void reveal() { revealed = true; }
};

#endif