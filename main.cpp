#include <iostream>
#include <string>

#include "SDL_Plotter.h"
#include "Graphics.h"

using namespace std;

int main(int argc, char ** argv)
{
    
    SDL_Plotter thePlot(1000, 1000);
    int x, y;
    int R, G, B;

    while (!thePlot.getQuit()) {

        x = thePlot.getCol() - 200;
        y = thePlot.getRow() - 200;
        R = rand()%256;
        G = rand()%256;
        B = rand()%256;
        
        
        drawLine(100, 100, 200, 200, thePlot);
        
        drawRectangle(200, 200, 100, 500, thePlot);
                
        drawCircle(400, 400, 100, thePlot);
        
        thePlot.update();
        if (thePlot.kbhit()) {
            char a = thePlot.getKey();
            
            if (a == 'A') {
                plotLetter(a, 800, 400, 5, thePlot);
            }
        }
        
        
    }

    return 0;
}


