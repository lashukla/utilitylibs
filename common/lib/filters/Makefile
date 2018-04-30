CFLAGS = -O -std=c++11
CC = g++
SRC = myregex.cpp regex_example.cpp
OBJ = $(SRC:.cpp = .o)

regex_example: $(OBJ)
	$(CC) $(CFLAGS) -o regex_example $(OBJ)

clean:
	rm -f core regex_example *.o
