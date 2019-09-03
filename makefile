#lab2
PROJECT = lab2
OBJ = main.o  TAVLtree.o
CC = g++ -g -std=c++11 -Wall -pedantic

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CC) -o $@ $< TAVLtree.o

main.o: main.cpp TAVLtree.h AVLnode.h
	$(CC)  -c $<

TAVLtree.o: TAVLtree.cpp TAVLtree.h AVLnode.h
	$(CC)  -c $<

clean:
	rm -f *.o $(PROJECT)

