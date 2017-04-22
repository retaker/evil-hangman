#include <iostream>

#include "SDL_Plotter.h"
#include "Graphics.h"

using namespace std;

int main(int argc, char ** argv)
{
    /**
    SDL_Plotter g(1000,1000);
    int x,y, xd, yd;
    int R,G,B;
    
    while (!g.getQuit())
    {
        x = rand()%g.getCol();
        y = rand()%g.getRow();
        R = rand()%256;
        G = rand()%256;
        B = rand()%256;
        for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
            for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
                g.plotPixel( x + xd, y + yd, R, G, B);
                g.plotPixel( x + xd, y + yd, 0, G, 0);
                
            }
        }
        g.update();
        if(g.kbhit()){
            g.getKey();
        }
    }
     */
    
    SDL_Plotter thePlot(1000, 1000);
    int x, y;
    int R, G, B;
     
    while (!thePlot.getQuit()) {

        x = thePlot.getCol() - 200;
        y = thePlot.getRow() - 200;
        R = rand()%256;
        G = rand()%256;
        B = rand()%256;
        
        
        drawLine(100, 10, 200, 20, thePlot);
        
        drawRectangle(200, 200, 100, 500, thePlot);
        
        // plotLetter(300, 300, thePlot);
        
        drawCircle(400, 400, 100, thePlot);
        
        thePlot.update();
        if (thePlot.kbhit()) {
            char a = thePlot.getKey();
        }
        
        
    }

    return 0;
}


