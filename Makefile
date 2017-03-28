OPTIONS = -lSDL2main -lSDL2 -lSDL2_mixer
OBJECTS = main.o

main: $(OBJECTS)
	g++ $(OPTIONS) $(OBJECTS) -o main

main.o: main.cpp SDL_Plotter.h
	g++ $(OPTIONS) main.cpp -o main.o

clean:
	rm *.o main
