+prog: main.o ship.o board.o game.o player.o
	g++ -std=c++11 -g -Wall main.o ship.o board.o game.o player.o -o prog

main.o: main.cpp ship.h board.h game.h player.h
	g++ -std=c++11 -g -Wall -c main.cpp

ship.o: ship.h ship.cpp
	g++ -std=c++11 -g -Wall -c ship.cpp 

board.o: board.h board.cpp
	g++ -std=c++11 -g -Wall -c board.cpp 

game.o: game.h game.cpp
	g++ -std=c++11 -g -Wall -c game.cpp 

player.o: player.h player.cpp
	g++ -std=c++11 -g -Wall -c player.cpp

clean: 
	rm *.o prog