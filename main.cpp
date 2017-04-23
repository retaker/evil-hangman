#include <iostream>
#include <string>

#include "SDL_Plotter.h"
#include "Graphics.h"

using namespace std;

SDL_Plotter thePlot(1000, 1000);

int main(int argc, char ** argv)
{
    
    
    Point p1(103, 100), p2(300, 200), p3(200, 400), p4(200, 600), p5(600, 300);
    
    while (!thePlot.getQuit()) {
        
        drawRightLimb(p1, 100, thePlot);
        drawLeftLimb(p1, 100, thePlot);

        // drawHead(p1, 100, thePlot);
        
        // drawLine(p1, p2, thePlot);
        
        // drawRectangle(p3, 100, 500, thePlot);
                
        // drawCircle(p4, 100, thePlot);
        
        // plotHorizontalLine(p1, 50, 10, thePlot);
        
        // plotVerticalLine(p1, 100, 10, thePlot);
        
       
        
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


