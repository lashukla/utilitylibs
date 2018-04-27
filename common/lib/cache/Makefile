CFLAGS = -O -std=c++11
CC = g++
SRC = node.cpp 
OBJ = $(SRC:.cpp = .o)

lru: $(OBJ)
	$(CC) $(CFLAGS) -o lru $(OBJ)

clean:
	rm -f core lru *.o
