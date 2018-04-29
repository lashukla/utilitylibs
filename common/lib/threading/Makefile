CFLAGS = -O -std=c++11 -lpthread
CC = g++
SRC = threadpool_example.cpp 
OBJ = $(SRC:.cpp = .o)

threadpool_example: $(OBJ)
	$(CC) -o threadpool_example $(OBJ) $(CFLAGS)

clean:
	rm -f core threadpool_example *.o
