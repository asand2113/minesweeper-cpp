minesweeper: main.o board.o
	g++ main.o board.o -lm -lncurses -lpthread -o minesweeper

main.o: main.cpp
	g++ -Wall -Werror -ggdb -lm main.cpp -c
	
board.o: board.cpp
	g++ -Wall -Werror -ggdb -lm board.cpp -c
	
clean: 
	rm -f main.o board.o minesweeper