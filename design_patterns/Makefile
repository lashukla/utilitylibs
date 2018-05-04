CFLAGS = -O -std=c++11 
LDFLAGS = -pthread
CC = g++

ALL_TARGET = singleton factory abstractfactory prototype composite builder observer bridge

all: $(ALL_TARGET)

singleton: singleton.cpp
	$(CC) -o singleton singleton.cpp $(CFLAGS) $(LDFLAGS)

factory: factory.cpp
	$(CC) -o factory factory.cpp $(CFLAGS)

abstractfactory: abstractfactory.cpp
	$(CC) -o abstractfactory abstractfactory.cpp $(CFLAGS)

prototype: prototype.cpp
	$(CC) -o prototype prototype.cpp $(CFLAGS) 

composite: abstractfactory.cpp
	$(CC) -o composite composite.cpp $(CFLAGS)

builder: builder.cpp
	$(CC) -o builder builder.cpp $(CFLAGS)

observer: observer.cpp
	$(CC) -o observer observer.cpp $(CFLAGS)

bridge: bridge.cpp
	$(CC) -o bridge bridge.cpp $(CFLAGS)

clean:
	rm -f core $(ALL_TARGET) *.o
