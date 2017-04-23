//
//  Graphics.h
//  evilHangman
//
//  Created by Hayden Householder on 4/22/17.
//  Copyright ?2017 Hayden Householder. All rights reserved.
//  Copyright ?2017 Vincent Yin. All rights reserved.
//  NoSenseOfMind@gmail.com
//

#ifndef Graphics_h
#define Graphics_h

#include <iostream>
#include <fstream>
#include <string>
#include "SDL_Plotter.h"

int fonts[37][5][7];

struct Point {
	int x, y;
	int R, G, B;

	Point(int nx = 0, int ny = 0, int nR = 0, int nG = 0, int nB = 0) {
		x = nx;
		y = ny;
		R = nR;
		G = nG;
		B = nB;
	}

	void setColor(int nR = 255, int nG = 255, int nB = 255) {
		R = nR;
		G = nG;
		B = nB;
	}
};



void plotSquare(Point p, int size, SDL_Plotter& plotter) {

	// Plotting the square
	for (int i = 0; i < size && p.x + i < plotter.getCol(); i++) {
		for (int j = 0; j < size && p.y + j < plotter.getRow(); j++) {
			plotter.plotPixel(p.x + i, p.y + j, p.R, p.G, p.B);
		}
	}
}

/****           SIMPLE DRAWING FUNCTIONS               *******/

// Function that draws a line between two points
void drawLine(Point p1, Point p2, SDL_Plotter& plotter) {

	// Calculating m & b for y = mx + b between the two points
	double m, b;
	m = (p2.y - p1.y) / (p2.x - p1.x);
	b = p2.y - (m*p2.x);

	// Picking = 0 the starting and ending y values

	if (p1.y < p2.y) {
		// Printing the line
		for (int i = p1.x; i < p2.x && i < plotter.getCol(); i++) {
			for (int j = p1.y; j < p2.y && j < plotter.getRow(); j++) {

				if (p1.x + i != p2.x && p1.y + j != p2.y) {

					// Calcuating the m & b for y = mx + b for individual points,
					// to see if they are on the line
					double approximateM, approximateB;
					approximateM = (p2.y - j) / (p2.x - (i));
					approximateB = (j)-(m*(i));

					// Checking the differnce between the actual m & b and the
					// approximate m & b
					double differenceM, differenceB;
					differenceM = m - approximateM;
					differenceB = b - approximateB;

					int lineWidth = 10;
					// Adjust the Differences to set the width of the line
					if ((differenceM < lineWidth && differenceM > -1 * lineWidth) &&
						((differenceB < lineWidth && differenceB > -1 * lineWidth))) {

						// Plotting the individual points on the
						plotter.plotPixel(i, j, p1.R, p1.G, p1.B);
					}

				} // If the point isn't at the end point

			} // Inside for loop

		} // Outside for loop
	}
	else {
		// Printing the line
		for (int i = p1.x; i < p2.x && i < plotter.getCol(); i++) {
			for (int j = p1.y; j > p2.y && j < plotter.getRow(); j--) {

				if (p1.x + i != p2.x && p1.y + j != p2.y) {


					// Calcuating the m & b for y = mx + b for individual points,
					// to see if they are on the line
					double approximateM, approximateB;
					approximateM = (p2.y - j) / (p2.x - i);
					approximateB = (j)-(m*(i));


					// Checking the differnce between the actual m & b and the
					// approximate m & b
					double differenceM, differenceB;
					differenceM = m - approximateM;
					differenceB = b - approximateB;



					int lineWidth = 10;
					// Adjust the Differences to set the width of the line
					if ((differenceM < lineWidth && differenceM > -1 * lineWidth) &&
						((differenceB < lineWidth && differenceB > -1 * lineWidth))) {

						// Plotting the individual points on the
						plotter.plotPixel(i, j, p2.R, p2.G, p2.B);
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
	for (int i = 0; i < radius * 2 && p.x + i < plotter.getCol(); i++) {
		for (int j = 0; j < radius * 2 && p.y + j < plotter.getRow(); j++) {

			int lineWidth = 10;
			// Checking to see if point is on the edge of the circle
			if (pow(((p.x + i) - centerX), 2) + pow(((p.y + j) - centerY), 2)
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
		for (int j = 0; j < height && p.y + j < plotter.getRow(); j++) {

			int lineWidth = 10;
			// Checking to see if the point is on an edge
			if (i - (lineWidth - 1) <= 0 || j - (lineWidth - 1) <= 0 ||
				i + 1 >= width - (lineWidth - 1) ||
				j + 1 >= height - (lineWidth - 1)) {

				plotter.plotPixel(p.x + i, p.y + j, p.R, p.G, p.B);

			}

		} // Inner for loop

	} // Outer for loop

}

void plotLetter(char letter, Point p, int size, SDL_Plotter& plotter) {
	int pos = (int)letter;
	if (pos > 96 && pos < 123) {
		pos -= 87;
	}
	else if (pos > 64 && pos < 91) {
		pos -= 55;
	}
	else if (pos == 34) {
		pos = 36;
	}
	else {
		pos -= 48;
	}
	if (pos < 0 || pos>36) {
		return;
	}
	Point tmp = p;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			if (fonts[pos][i][j] == 1) {
				tmp.x = p.x + i*size;
				tmp.y = p.y + j*size;
				plotSquare(tmp, size, plotter);
			}
		}
	}
}

void putString(string str, Point p, int size, SDL_Plotter& plotter) {
	int length = str.length();
	for (int i = 0;i < length;i++) {
		plotLetter(str[i], p, size, plotter);
		p.x = p.x + size * 6;
	}
}

bool loadFont(char* fileName) {
	ifstream input;
	input.open(fileName);

	if (!input) {
		return false;
	}

	for (int i = 0; i < 37; i++) {
		for (int y = 0; y < 7; y++) {
			for (int x = 0; x < 5; x++) {
				input >> fonts[i][x][y];
			}
		}
	}
	input.close();
	return true;
}

// Prints a veritcal line starting at point p1 with a given height and size
void plotVerticalLine(Point p1, int height, int size, SDL_Plotter& plotter) {

	int increment = height / size;

	Point temp = p1;
	for (int j = 0; j < increment; j++) {
		temp.y = p1.y + (j*size);
		plotSquare(temp, size, plotter);
	}

}

// Prints a horizontal line starting at point p1 with a given width and size
void plotHorizontalLine(Point p1, int width, int size, SDL_Plotter& plotter) {

	int increment = width / size;

	Point temp = p1;
	for (int i = 0; i < increment; i++) {
		temp.x = p1.x + (i*size);
		plotSquare(temp, size, plotter);
	}
}


/*****                  DRAWING OF THE MAN & STOCK              *****/

// Plots a shelf at Point location
// location represents the top left corner of the shelf
void drawShelf(Point location, int size, SDL_Plotter& plotter) {

	int lineWidth = 10;
	int shelfHeight = size * 5;
	int topArmLength = size * 2;
	int ropeHeight = size*1.5;

	// Back bone of the shelf
	plotVerticalLine(location, shelfHeight, lineWidth, plotter);

	// Top piece of the shelf
	plotHorizontalLine(location, topArmLength, lineWidth, plotter);

	// Rope of the shelf
	Point topMiddle(location.x + topArmLength, location.y);
	plotVerticalLine(topMiddle, ropeHeight, lineWidth, plotter);

	// Bottom of the shelf
	Point bottomLeft(location.x - topArmLength / 2, location.y + shelfHeight);
	plotHorizontalLine(bottomLeft, topArmLength * 2, lineWidth, plotter);



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
	drawCircle(p, size - lineWidth, plotter);
	p.setColor(prevR, prevG, prevB);
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

	int lineWidth = 10;
	// Drawing the head at the top left of the points
	drawHead(p, size, plotter);

	// Drawing the arms of the man
	// Creating the arm point of the man
	Point arms(p.x + size*(1.05), p.y + size*2.5);
	drawLeftLimb(arms, size, plotter);
	drawRightLimb(arms, size, plotter);

	// Drawing the legs of the man
	// Creating the left point of the man
	Point legs(arms.x, p.y + (4)*(size));
	drawRightLimb(legs, size, plotter);
	drawLeftLimb(legs, size, plotter);

	// Drawing the spine of the man
	// Creating the spine starting point
	Point spine(p.x + (19.0 / 20)*size, p.y + 1.9*(size));
	plotVerticalLine(spine, size*2.5, lineWidth, plotter);
}

void DefaultScreen(SDL_Plotter& plotter)
{
	Point P1 = Point(280, 50, 0, 0, 0);
	Point P2 = Point(280, 125, 0, 0, 0);
	Point P3 = Point(376, 600, 0, 0, 0);
	Point ManPostion = Point(600, 200, 0, 0, 0);
	Point P5 = Point(850, 700, 0, 0, 0);
	Point RopeBotton(500, 175, 0, 0, 0);
	putString("HangMan Game", P1, 10, plotter);
	putString("Infinite Loop Production", P2, 2, plotter);
	putString("Press ANY Key to Start", P3, 4, plotter);
	putString("Copyright 2017.All rights reserved", P5, 2, plotter);
	drawShelf(RopeBotton, 75, plotter);
	drawMan(ManPostion, 50, plotter);
}

void MainMenu(SDL_Plotter& plotter, int level, bool music, int pointer) 
{
	Point ManPostion = Point(300, 200, 0, 0, 0);
	Point RopeBotton(200, 175, 0, 0, 0);
	drawShelf(RopeBotton, 75, plotter);
	drawMan(ManPostion, 50, plotter);
	int r1 = 0, g1 = 0, b1 = 0;
	int r2 = 0, g2 = 0, b2 = 0;
	int r3 = 0, g3 = 0, b3 = 0;
	int r4 = 0, g4 = 0, b4 = 0;
	int r5 = 0, g5 = 0, b5 = 0;

	Point Menu = Point(780, 50, 0, 0, 0);
	putString("Menu", Menu, 9, plotter);

	if (pointer == 1) {
		r1 = 169;
		b1 = 169;
		g1 = 169;
	}
	else if (pointer == 2) {
		r2 = 169;
		b2 = 169;
		g2 = 169;
	}
	else if (pointer == 3) {
		r3 = 169;
		b3 = 169;
		g3 = 169;
	}
	else if (pointer == 4) {
		r4 = 169;
		b4 = 169;
		g4 = 169;
	}
	else if (pointer == 5) {
		r5 = 169;
		b5 = 169;
		g5 = 169;
	}
	Point OpStart = Point(810, 180, r1, g1, b1);
	putString("Start", OpStart, 5, plotter);

	Point OpLevel = Point(810, 250, r2, g2, b2);
	putString("Level", OpLevel, 5, plotter);
	Point diff = Point(1015, 255, r2, g2, b2);
	if (level == 4) {
		putString("EASY", diff, 4, plotter);
		Point lefttemp1 = Point(1000, 250, r2, g2, b2);
		Point lefttemp2 = Point(980, 265, r2, g2, b2);
		Point righttemp1 = Point(1120, 250, r2, g2, b2);
		Point righttemp2 = Point(1140, 265, r2, g2, b2);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	else if (level == 5) {
		putString("Normal", diff, 4, plotter);
		Point lefttemp1 = Point(1000, 250, r2, g2, b2);
		Point lefttemp2 = Point(980, 265, r2, g2, b2);
		Point righttemp1 = Point(1160, 250, r2, g2, b2);
		Point righttemp2 = Point(1180, 265, r2, g2, b2);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	else if (level == 6) {
		putString("Hard", diff, 4, plotter);
		Point lefttemp1 = Point(1000, 250, r2, g2, b2);
		Point lefttemp2 = Point(980, 265, r2, g2, b2);
		Point righttemp1 = Point(1120, 250, r2, g2, b2);
		Point righttemp2 = Point(1140, 265, r2, g2, b2);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	Point Opmusic = Point(810, 320, r3, g3, b3);
	putString("MUSIC", Opmusic, 5, plotter);
	Point Status = Point(1020, 325, r3, g3, b3);
	if (music == true) {
		putString("On", Status, 4, plotter);
		Point lefttemp1 = Point(1000, 320, r3, g3, b3);
		Point lefttemp2 = Point(980, 335, r3, g3, b3);
		Point righttemp1 = Point(1080, 320, r3, g3, b3);
		Point righttemp2 = Point(1100, 335, r3, g3, b3);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	else if (music == false) 
	{
		putString("Off", Status, 4, plotter);
		Point lefttemp1 = Point(1000, 320, r3, g3, b3);
		Point lefttemp2 = Point(980, 335, r3, g3, b3);
		Point righttemp1 = Point(1100, 320, r3, g3, b3);
		Point righttemp2 = Point(1120, 335, r3, g3, b3);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	Point Opplayers = Point(810, 390, r4, g4, b4);
	putString("Players", Opplayers, 5, plotter);

	Point Opexit = Point(810, 460, r5, g5, b5);
	putString("EXIT", Opexit, 5, plotter);
}

void GameOver(SDL_Plotter& plotter) 
{
	Point ManPostion = Point(225, 290, 0, 0, 0);
	Point RopeBotton(125, 190, 0, 0, 0);
	drawShelf(RopeBotton, 75, plotter);
	drawMan(ManPostion, 50, plotter);
	Point Title = Point(400, 50, 0, 0, 0);
	putString("Game Over", Title, 10, plotter);
	Point Score = Point(450, 200, 0, 0, 0);
	putString("Your Score", Score, 7, plotter);
	Point Restart = Point(450, 500, 0, 0, 0);
	putString("Press R to retry", Restart, 4, plotter);
	Point End = Point(450, 550, 0, 0, 0);
	putString("Press Esc to exit", End, 4, plotter);
}
void WonScreen(SDL_Plotter&plotter) 
{
	Point Title = Point(400, 50, 0, 0, 0);
	putString("YOU WON", Title, 10, plotter);
	Point Score = Point(400, 200, 0, 0, 0);
	putString("Your Score", Score, 6, plotter);
	Point Msg = Point(400, 300, 0, 0, 0);
	putString("Please Type your name", Msg, 6,plotter);
	Point line1 = Point(400, 450, 0, 0, 0);
	Point line2 = Point(550, 450, 0, 0, 0);
	Point line3 = Point(700, 450, 0, 0, 0);
	Point line4 = Point(850, 450, 0, 0, 0);
	plotHorizontalLine(line1, 50, 4, plotter);
	plotHorizontalLine(line2, 50, 4, plotter);
	plotHorizontalLine(line3, 50, 4, plotter);
	plotHorizontalLine(line4, 50, 4, plotter);
	Point RopeBotton(125, 190, 0, 0, 0);
	drawShelf(RopeBotton, 75, plotter);
	Point Restart = Point(400, 500, 0, 0, 0);
	putString("Press B to Menu", Restart, 4, plotter);
	Point End = Point(400, 550, 0, 0, 0);
	putString("Press Esc to exit", End, 4, plotter);
}

void GamingScreen(SDL_Plotter& plotter, int level) 
{
	Point ManPostion = Point(300, 275, 0, 0, 0);
	Point RopeBotton(200, 175, 0, 0, 0);
	drawShelf(RopeBotton, 75, plotter);
	drawMan(ManPostion, 50, plotter);
	Point Msg = Point(550, 300, 250, 0, 0);
	putString("Please guess possiable letters in this word", Msg, 2, plotter);
	int x = 550;
	int y = 550;
	for (int i = 0; i < level; i++) {
		Point line = Point(x, y, 0, 0, 0);
		plotHorizontalLine(line, 50, 4, plotter);
		x += 100;
	}
}

bool Timer(int seconds)
{
	clock_t startTime = clock(); //Start timer

	clock_t testTime;
	clock_t timePassed;
	double secondsPassed;

	while (true)
	{
		testTime = clock();
		timePassed = startTime - testTime;
		secondsPassed = timePassed / (double)CLOCKS_PER_SEC;

		if (secondsPassed > 60)
		{
			return false;
		}
		else if (secondsPassed <= 60)
		{
			//print second numbers
		}
	}
}

#endif /* Graphics_h */