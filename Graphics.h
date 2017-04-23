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
    
    
    // Picking = 0 the starting and ending y values
    
    if(p1.y < p2.y) {
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
                    plotter.plotPixel(p1.x + i, p1.y + j, p1.R, p1.G, p1.B);
                }
                
            } // If the point isn't at the end point
            
        } // Inside for loop
        
    } // Outside for loop
    }
    
    else {
        // Printing the line
        for (int i = p1.x; i < p2.x  && p1.x + i < plotter.getCol(); i++) {
            for (int j = p1.y; j > p2.y && p1.y - j > 0; j--) {
                
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
                        plotter.plotPixel(p1.x + i, p1.y + j, p1.R, p1.G, p1.B);
                    }
                    
                } // If the point isn't at the end point
                
            } // Inside for loop
            
        } // Outside for loop
        
    }
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
            if ( pow(((p.x + i) - centerX), 2) + pow(((p.y + j) - centerY), 2)
                <= pow(radius - pow(lineWidth, 0.5), 2)) {
                plotter.plotPixel(p.x + i, p.y + j, p.R, p.G, p.B);
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

// Prints a veritcal line starting at point p1 with a given height and size
void plotVerticalLine(Point p1, int height, int size, SDL_Plotter& plotter) {
    
    int increment = height/size;
    
    for (int j = 0; j < increment; j++){
        plotSquare(p1.x, p1.y + (j*size), size, plotter);
    }
    
}

// Prints a horizontal line starting at point p1 with a given width and size
void plotHorizontalLine(Point p1, int width, int size, SDL_Plotter& plotter) {
    
    int increment = width/size;
    
    for (int i = 0; i < increment; i++) {
        plotSquare(p1.x + (i * size), p1.y, size, plotter);
    }
}


/*****                  DRAWING OF THE MAN & STOCK              *****/

// Plots a shelf at Point location
// location represents the top left corner of the shelf
void drawShelf(Point location, int size, SDL_Plotter& plotter) {
    
    int lineWidth = 10;
    int shelfHeight = size*5;
    int topArmLength = size*2;
    int ropeHeight = size*1.5;
    
    // Back bone of the shelf
    plotVerticalLine(location, shelfHeight, lineWidth, plotter);

    // Top piece of the shelf
    plotHorizontalLine(location, topArmLength, lineWidth, plotter);
    
    // Rope of the shelf
    Point topMiddle(location.x + topArmLength, location.y);
    plotVerticalLine(topMiddle, ropeHeight, lineWidth, plotter);
    
    // Bottom of the shelf
    Point bottomLeft(location.x - topArmLength/2, location.y + shelfHeight);
    plotHorizontalLine(bottomLeft, topArmLength*2, lineWidth, plotter);
    
    

}

// Draws the head of the Hangman at point p with a give size
//
void drawHead(Point p, int size, SDL_Plotter& plotter) {
    
    int prevR = p.R;
    int prevG = p.G;
    int prevB = p.B;
    
    int lineWidth = 10;
    
    p.setColor(0, 0, 0);
    drawCircle(p, size, plotter);
    
    // Changing the inner circle's color to white and positioning it correctly
    p.setColor(255, 255, 255);
    
    // Getting new coordinates for the inner circle
    p.x = p.x + lineWidth;
    p.y = p.y + lineWidth;
    
    // Getting new
    drawCircle(p, size-lineWidth, plotter);
    p.setColor(prevR,prevG, prevB);
}

void drawRightLimb(Point p, int size, SDL_Plotter& plotter) {
    
    // Creating the endpoint for the right limb
    Point endpoint(p.x + size, p.y + size);
    
    drawLine(p, endpoint, plotter);
    
    
}

void drawLeftLimb(Point p, int size, SDL_Plotter& plotter) {
    
    // Creating the beginning for the left limb
    Point beginning(p.x - size, p.y + size);
    
    drawLine(beginning, p, plotter);
    
}

void drawMan(Point p, int size, SDL_Plotter& plotter) {
    
}


#endif /* Graphics_h */
