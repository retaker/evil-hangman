#include <iostream>
#include <string>

#include "SDL_Plotter.h"
#include "Graphics.h"

using namespace std;

int main(int argc, char ** argv)
{
    
    SDL_Plotter thePlot(1000, 1000);
    Point p1(100, 100), p2(200, 200), p3(200, 400), p4(200, 600), p5(600, 300);
    int x, y;
    int R, G, B;

    while (!thePlot.getQuit()) {

        x = thePlot.getCol() - 200;
        y = thePlot.getRow() - 200;
        R = rand()%256;
        G = rand()%256;
        B = rand()%256;
        
        
        
        // drawLine(p1, p2, thePlot);
        
        // drawRectangle(p3, 100, 500, thePlot);
                
        // drawCircle(p4, 100, thePlot);
        
        thePlot.update();
        if (thePlot.kbhit()) {
            char a = thePlot.getKey();
            
            if (a == 'A') {
                plotLetter(a, p5, 5, thePlot);
            }
        }
        
        
    }

    return 0;
}


