CFLAGS=-Wall -g

all: main 

main: 
	g++ -o main main.cpp src/BinTree.cpp src/RedBlackTree.cpp
clean:
	rm -f main 
