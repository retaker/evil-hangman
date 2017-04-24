#include <iostream>
#include <string>

#include "SDL_Plotter.h"
#include "Graphics.h"

using namespace std;

SDL_Plotter thePlot(720, 1280);

int main(int argc, char ** argv)
{
    
    
    Point p1(100, 100), p2(300, 200), p3(500, 450), p4(550, 375), p5(255, 188);
    
    while (!thePlot.getQuit()) {
        
        loadFont("font.txt");
        WonScreen(thePlot);
       
        
        thePlot.update();
        
        
        
        
        
        
        if (thePlot.kbhit()) {
            char a = thePlot.getKey();
            
            if (a == 'A') {
                plotLetter(a, p4, 8, thePlot);
            }
        }
        
        
    }

    return 0;
}


