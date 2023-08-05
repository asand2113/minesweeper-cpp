# minesweeper-cpp
## Overview
A simplistic, terminal-based game inspired by Minesweeper made in C++. Originally, this program was designed for a university course for educational purposes. Its overall simplistic nature and abundant code comments make it a good example for C++ learners to look over. 

Make is used to build the program.

Notably, the project utilises ncurses and pthreads.
## Controls
Both a mouse and keyboard are required to play this version. Game controls are bound to specific buttons and can not be remapped. 
```
- Left CLick - Reveal an unrevealed tile
- Right Click - Toggle a tile's "flagged" status
- q - Exit the game
```
## Files
```
- Makefile : Used by Make to build/remove the program
- board.cpp : Implements functions pertaining to game board functions
- board.h : Defines the functions used in board.cpp and manages the headers the game board depends on
- main.cpp : The primary game logic
- tile.h : Defines the tile Class used in the game
```
