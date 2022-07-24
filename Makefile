 .default: all

all: azul

clean:
	rm -f azul *.o

azul: Board.o CentralFactory.o BoxLid.o Factory.o LinkedList.o main.o Game.o Player.o Tile.o TileBag.o GameEngine.o
	g++ -Wall -Werror  -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror   -std=c++14 -g -O -c $^
