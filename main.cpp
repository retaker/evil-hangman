#include <iostream>

#include "SDL_Plotter.h"

using namespace std;

void plotLetter(int, int, SDL_Plotter);

int main(int argc, char ** argv)
{
    SDL_Plotter thePlot = SDL_Plotter();
    
    bool done = false;
    
    while (!done) {
        
        int x = 50;
        int y = 50;
        
        
        if (thePlot.getKey()) {
        
            for (int i = 0; i < 100 && x + i < thePlot.getRow(); i++) {
                for (int j = 0; j < 100 && y + j < thePlot.getCol(); j++) {
                    thePlot.plotPixel(x + i, y + j, 255, 0, 0);
                    
                }
            }
        }
        
        thePlot.update();
    }

    return 0;
}

void plotLetter(int x, int y, SDL_Plotter plotter) {
    int letter [][5] = {
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1}};
        
    
    for (int i =0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (letter[i][j] == 1) {
                plotter.plotPixel(x, y, 100, 100, 100);
            }
        }
    }
    
}
