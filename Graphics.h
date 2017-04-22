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

#ifndef Graphics_h
#define Graphics_h

void plotSquare(int x, int y, int size, SDL_Plotter& plotter);


/****                SIMPLE DRAWING FUNCTIONS               *******/

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
                j + 1 >= height - (lineWidth-1)) {
                
                plotter.plotPixel(x + i, y + j, 256, 256, 256);
                
            }
            
        } // Inner for loop
        
    } // Outer for loop
    
}

void plotLetter(char letter,int x, int y, int size, SDL_Plotter& plotter) {
    
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
                plotSquare(x + (i*size), y + (j*size), size, plotter);
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



#endif /* Graphics_h */
