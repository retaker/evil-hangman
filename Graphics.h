//
//  Graphics.h
//  evilHangman
//
//  Created by Hayden Householder on 4/22/17.
//  Copyright © 2017 Hayden Householder. All rights reserved.
//


#include <iostream>
#include <fstream>
#include "SDL_Plotter.h"
#include "Point.h"

#ifndef Graphics_h
#define Graphics_h

void plotSquare(int x, int y, int size, SDL_Plotter& plotter);


/****                SIMPLE DRAWING FUNCTIONS               *******/

// Function that draws a line between two points
void drawLine(Point p1, Point p2, SDL_Plotter& plotter) {
    
    // Calculating m & b for y = mx + b between the two points
    double m, b;
    m = (p2.y-p1.y)/(p2.x-p1.x);
    b = p2.y-(m*p2.x);
    
    // Printing the line
    for (int i = p1.x; i < p2.x  && p1.x + i < plotter.getCol(); i++) {
        for (int j = p1.y; j < p2.y && p1.y + j < plotter.getRow(); j++) {
            
            if (p1.x + i != p2.x && p1.y + j != p2.y) {
                
                // Calcuating the m & b for y = mx + b for individual points,
                // to see if they are on the line
                double approximateM, approximateB;
                approximateM = (p2.y-(p1.y+j))/(p2.x-(p1.x+i));
                approximateB = (p1.y+j)-(m*(p1.x+i));
                
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
                    plotter.plotPixel(p1.x + i, p1.y + j, p1.R , p1.G, p1.B);
                }
                
            } // If the point isn't at the end point
            
        } // Inside for loop
        
    } // Outside for loop
    
}


// Function that draws a circle at (x, y) with a given width and height
// (x, y) represents the top left corner of the circle
void drawCircle(Point p, int radius, SDL_Plotter& plotter) {
    
    // Getting the center of the circle
    int centerX, centerY;
    
    centerX = p.x + radius;
    centerY = p.y + radius;
    
    // Plotting the edge of the circle
    for (int i = 0; i < radius*2 && p.x + i < plotter.getCol(); i++) {
        for (int j = 0; j < radius*2 && p.y + j < plotter.getRow(); j++) {
            
            int lineWidth = 10;
            // Checking to see if point is on the edge of the circle
            if ( pow(((p.x + i) - centerX), 2) + pow(((p.y + j) - centerY), 2) <=
                pow(radius - pow(lineWidth, 0.5), 2)) {
                plotter.plotPixel(p.x + i, p.y + j, 256, 256, 256);
            }
            
        }
    }
    
    
    
}

// Function that draws a rectangle at (x, y) with a given width and height
// (x, y) represents the top left corner
void drawRectangle(Point p, int height, int width, SDL_Plotter& plotter) {
    
    // Plotting the edges of the rectanlge
    for (int i = 0; i < width && p.x + i < plotter.getCol(); i++) {
        for (int j = 0; j < height && p.y + j < plotter.getRow();  j++) {
            
            int lineWidth = 10;
            // Checking to see if the point is on an edge
            if (i - (lineWidth-1) <= 0 || j - (lineWidth-1) <= 0||
                i + 1 >= width - (lineWidth-1) ||
                j + 1 >= height - (lineWidth-1)) {
                
                plotter.plotPixel(p.x + i, p.y + j, 256, 256, 256);
                
            }
            
        } // Inner for loop
        
    } // Outer for loop
    
}

void plotLetter(char letter, Point p, int size, SDL_Plotter& plotter) {
    
    // Getting the letter file to be read in
    ifstream input;
    string fileName = ".txt";
    
    // Finalizing the file name to be read in
    fileName.insert(0, 1, letter);

    // Opening the particular letter file to be read in
    input.open(fileName);
    cout << fileName << endl;
    
    int theLetter [7][5];
   
    int readInteger = 0;
    
    // Reading in the letter to a 2-D array
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 5; i++) {
            
            input >> readInteger;
            
            theLetter[j][i] = readInteger;
            
            cout << readInteger << " ";
            
            if (readInteger == 1) {
                plotSquare(p.x + (i*size), p.y + (j*size), size, plotter);
            }
            
        }
        cout << endl;
    }
    
    input.close();
    
}


// Function that plots a square, can be used to allow different size fonts
void plotSquare(int x, int y, int size, SDL_Plotter& plotter) {
    
    // Plotting the square
    for(int i = 0; i < size && x + i < plotter.getCol(); i++) {
        for (int j = 0; j < size && y + j < plotter.getRow(); j++){
            
            plotter.plotPixel(x + i, y + j, 256, 256, 256);
            
        }
    }
}


/*****                  DRAWING OF THE MAN & STOCK              *****/

// Plots a shelf at Point location
// location represents the top left corner of the shelf
void drawShelf(Point location, SDL_Plotter& plotter) {
    
    // Back bone of the shelf
    Point bottomLeft(location.x, location.y + 200);
    drawLine(location, bottomLeft, plotter);

    
    // Top middle of the shelf
    Point topMiddle(location.x + 50, location.y);
    drawLine(location, topMiddle, plotter);
    
    // Bottom of the shelf
    Point bottomRight(bottomLeft.x + 100, bottomLeft.y);
    drawLine(bottomLeft, bottomRight, plotter);
    
    
}



void drawMan() {
    
}


#endif /* Graphics_h */
