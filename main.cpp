#include <iostream>

#include "SDL_Plotter.h"

using namespace std;

void plotLetter(int, int, SDL_Plotter&);
void drawLine(int x1, int y1, int x2, int y2, SDL_Plotter& plotter);
void drawRectangle(int x, int y, int height, int width, SDL_Plotter& plotter);
void drawCircle(int x, int y, int radius, SDL_Plotter& plotter);

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
        
        drawRectangle(200, 200, 50, 50, thePlot);
        
        plotLetter(300, 300, thePlot);
        
        drawCircle(400, 400, 100, thePlot);
        
        thePlot.update();
        if (thePlot.kbhit()) {
            char a = thePlot.getKey();
        }
        
        
    }

    return 0;
}

// Function that draws a line between two points
void drawLine(int x1, int y1, int x2, int y2, SDL_Plotter& plotter) {
    
    // Calculating m & b for y = mx + b between the two points
    double m, b;
    m = (y2-y1)/(x2-x1);
    b = y2-(m*x2);
    
    // Printing the line
    for (int i = x1; i < x2  && x1 + i < plotter.getCol(); i++) {
        for (int j = y1; j < y2 && y1 + j < plotter.getRow(); j++) {
            
            if (x1 + i != x2 && y1 + j != y2) {
            
                // Calcuating the m & b for y = mx + b for individual points,
                // to see if they are on the line
                double approximateM, approximateB;
                approximateM = (y2-(y1+j))/(x2-(x1+i));
                approximateB = (y1+j)-(m*(x1+i));
            
                // Checking the differnce between the actual m & b and the
                // approximate m & b
                double differenceM, differenceB;
                differenceM = m - approximateM;
                differenceB = b - approximateB;
                
                int lineWidth = 10;
                // Adjust the Differences to set the width of the line
                if ((differenceM < lineWidth && differenceM > -1*lineWidth) &&
                    ((differenceB < lineWidth && differenceB > -1*lineWidth))){
                    
                    // Plotting the individual points on the
                    plotter.plotPixel(x1 + i, y1 + j, 256, 256, 256);
                }
                
            } // If the point isn't at the end point
            
        } // Inside for loop
        
    } // Outside for loop
    
}

// Function that draws a circle at (x, y) with a given width and height
// (x, y) represents the top left corner of the circle
void drawCircle(int x, int y, int radius, SDL_Plotter& plotter) {
    
    // Getting the center of the circle
    int centerX, centerY;
    
    centerX = x + radius;
    centerY = y + radius;
    
    // Plotting the edge of the circle
    for (int i = 0; i < radius*2 && x + i < plotter.getCol(); i++) {
        for (int j = 0; j < radius*2 && y + j < plotter.getRow(); j++) {
            
            int lineWidth = 10;
            // Checking to see if point is on the edge of the circle
            if ( pow(((x + i) - centerX), 2) + pow(((y + j) - centerY), 2) <=
                pow(radius - pow(lineWidth, 0.5), 2)) {
                plotter.plotPixel(x + i, y + j, 256, 256, 256);
            }
            
        }
    }
    
    
    
}

// Function that draws a rectangle at (x, y) with a given width and height
// (x, y) represents the top left corner
void drawRectangle(int x, int y, int height, int width, SDL_Plotter& plotter) {
    
    // Plotting the edges of the rectanlge
    for (int i = 0; i < width && x + i < plotter.getCol(); i++) {
        for (int j = 0; j < height && y + j < plotter.getRow();  j++) {
            
            int lineWidth = 10;
            // Checking to see if the point is on an edge
            if (i - (lineWidth-1) <= 0 || j - (lineWidth-1) <= 0||
                i + 1 >= width - (lineWidth-1) ||
                j + 1 >= width - (lineWidth-1)) {
                
                plotter.plotPixel(x + i, y + j, 256, 256, 256);
                
            }
            
        } // Inner for loop
    
    } // Outer for loop
    
}

void plotLetter(int x, int y, SDL_Plotter& plotter) {
    int letter [3*5] = {
        1, 0, 1, 0, 1,
        0, 1, 0, 1, 0,
        1, 0, 1, 0, 1};
        
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
                plotter.plotPixel(x + i, y + j, 100, 100, 100);
        }
    }
    
}
