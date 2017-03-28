OPTIONS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
OBJECTS = main.o

main: main.o
	g++ $(OPTIONS) main.o -o main

main.o: main.cpp
	g++ $(OBJECTS) main.cpp -o main.o

clean:
	rm *.o main