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
#include <ctime>
#include "SDL_Plotter.h"

int fonts[38][5][7];
const int USERS_ON_LEADERBOARD = 5;

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

	void setLocation(int nx, int ny) {
		x = nx;
		y = ny;
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
	else if(pos == 58){
		pos = 37;
	}
	else {
		pos -= 48;
	}
	if (pos < 0 || pos>37) {
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

	for (int i = 0; i < 38; i++) {
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

void drawMan(Point &p, int size, SDL_Plotter& plotter, int step) {
	int lineWidth = 10;
	Point spine(p.x + (19.0 / 20)*size, p.y + 1.9*(size));
	Point arms(p.x + size*(1.05), p.y + size*2.5);
	Point legs(arms.x, p.y + (4)*(size));
	if (step >= 7) {
		p.setColor(255, 0, 0);
		spine.setColor(255, 0, 0);
		arms.setColor(255, 0, 0);
		legs.setColor(255, 0, 0);
	}
	switch (step) {
	case 1: drawHead(p, size, plotter); break;
	case 2: plotVerticalLine(spine, size*2.5, lineWidth, plotter); break;
	case 3: drawLeftLimb(arms, size, plotter); break;
	case 4: drawRightLimb(arms, size, plotter); break;
	case 5: drawRightLimb(legs, size, plotter); break;
	case 6: drawLeftLimb(legs, size, plotter); break;
	case 7: drawHead(p, size, plotter); break;
	case 8: plotVerticalLine(spine, size*2.5, lineWidth, plotter); break;
	case 9: drawLeftLimb(arms, size, plotter); break;
	case 10: drawRightLimb(arms, size, plotter); break;
	case 11: drawRightLimb(legs, size, plotter); break;
	case 12: drawLeftLimb(legs, size, plotter); break;
	}
}

/*****              Recording and Reading Scores        *****/

void readHighScores(string users[USERS_ON_LEADERBOARD], int scores[USERS_ON_LEADERBOARD]) {

	// Creating & opening the file stream to read the high scores from
	ifstream highScores;
	highScores.open("Highscores.txt");

	// User names and number of users displayed on the leaderboard
	string userNames[USERS_ON_LEADERBOARD];
	int userScores[USERS_ON_LEADERBOARD];

	// Reading in the users names as well as their individual scores
	for (int i = 0; i < USERS_ON_LEADERBOARD; i++) {
		highScores >> users[i];
		highScores >> scores[i];
	}

	// Closing the file stream
	highScores.close();
}

void updateHighScores(string users[], int scores[]) {

	// Creating a new output stream to the Highscores.txt
	ofstream highScores;
	highScores.open("Highscores.txt", ios::trunc);

	// Outputting the users and scores to the output filestream
	for (int i = 0; i < USERS_ON_LEADERBOARD; i++) {
		highScores << users[i] << " " << scores[i] << endl;
	}
}


void recordHighScore(string userName, int theHighScore) {

	string theUsers[USERS_ON_LEADERBOARD];
	int theScores[USERS_ON_LEADERBOARD];
	bool highScore = false;

	readHighScores(theUsers, theScores);

	int i;
	for (i = 0; i < USERS_ON_LEADERBOARD && !highScore; i++) {

		// Checking to see if the score makes it in the top five
		if (theHighScore > theScores[i]) {
			highScore = true;
		}

	}

	// Getting the actual location of the high score
	i--;

	// Putting the high score in the list and moving the rest down the list
	if (highScore) {

		// Inserting the user and their score in the correct position and moving
		// the rest of the users and their scores down
		while (i < USERS_ON_LEADERBOARD) {

			swap(userName, theUsers[i]);
			swap(theHighScore, theScores[i]);

			i++;
		}

		updateHighScores(theUsers, theScores);
	}

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
	plotter.initSound("BGM1");
	plotter.playSound("BGM1");
}

void MainMenu(SDL_Plotter& plotter, int level, bool music, bool & SoundIsPlaying, int pointer)
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

	Point Menu = Point(575, 50, 0, 0, 0);
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
	Point OpStart = Point(600, 180, r1, g1, b1);
	putString("Start", OpStart, 5, plotter);

	Point OpLevel = Point(600, 250, r2, g2, b2);
	putString("Level", OpLevel, 5, plotter);
	Point diff = Point(815, 255, r2, g2, b2);
	if (level == 4) {
		putString("EASY", diff, 4, plotter);
		Point lefttemp1 = Point(800, 250, r2, g2, b2);
		Point lefttemp2 = Point(780, 265, r2, g2, b2);
		Point righttemp1 = Point(920, 250, r2, g2, b2);
		Point righttemp2 = Point(940, 265, r2, g2, b2);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	else if (level == 5) {
		putString("Normal", diff, 4, plotter);
		Point lefttemp1 = Point(800, 250, r2, g2, b2);
		Point lefttemp2 = Point(780, 265, r2, g2, b2);
		Point righttemp1 = Point(960, 250, r2, g2, b2);
		Point righttemp2 = Point(980, 265, r2, g2, b2);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	else if (level == 6) {
		putString("Hard", diff, 4, plotter);
		Point lefttemp1 = Point(800, 250, r2, g2, b2);
		Point lefttemp2 = Point(780, 265, r2, g2, b2);
		Point righttemp1 = Point(920, 250, r2, g2, b2);
		Point righttemp2 = Point(940, 265, r2, g2, b2);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	Point Opmusic = Point(600, 320, r3, g3, b3);
	putString("MUSIC", Opmusic, 5, plotter);
	Point Status = Point(820, 325, r3, g3, b3);
	if (music == true) {
		putString("On", Status, 4, plotter);
		Point lefttemp1 = Point(800, 320, r3, g3, b3);
		Point lefttemp2 = Point(780, 335, r3, g3, b3);
		Point righttemp1 = Point(880, 320, r3, g3, b3);
		Point righttemp2 = Point(900, 335, r3, g3, b3);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	else if (music == false)
	{
		putString("Off", Status, 4, plotter);
		Point lefttemp1 = Point(800, 320, r3, g3, b3);
		Point lefttemp2 = Point(780, 335, r3, g3, b3);
		Point righttemp1 = Point(900, 320, r3, g3, b3);
		Point righttemp2 = Point(920, 335, r3, g3, b3);
		drawLeftLimb(lefttemp1, 20, plotter);
		drawRightLimb(lefttemp2, 20, plotter);
		drawLeftLimb(righttemp2, 20, plotter);
		drawRightLimb(righttemp1, 20, plotter);
	}
	Point OpPlayers = Point(600, 390, r4, g4, b4);
	putString("Players", OpPlayers, 5, plotter);

	Point Opexit = Point(600, 460, r5, g5, b5);
	putString("EXIT", Opexit, 5, plotter);
	if (music == true)
	{
		if (SoundIsPlaying == false)
		{
			plotter.initSound("backgroundNoise.wav");
			plotter.playSound("backgroundNoise.wav");
			cout << "Trying to play" << endl;
		}
		else if (SoundIsPlaying == true) {}
	}
	else if (music == false)
	{
		if (SoundIsPlaying == false) {}
		else if (SoundIsPlaying == true)
		{
			plotter.quitSound("backgroundNoise.wav");
			plotter.initSound("backgroundNoise.wav");
			cout << "Closed" << endl;
		}
	}
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
void userNameSpaces(SDL_Plotter& plotter, Point firstLine, int namePosition) {

	int r1 = 0, g1 = 0, b1 = 0;
	int r2 = 0, g2 = 0, b2 = 0;
	int r3 = 0, g3 = 0, b3 = 0;
	int r4 = 0, g4 = 0, b4 = 0;

	if (namePosition == 1) {
		r1 = 169;
		g1 = 169;
		b1 = 169;
	}
	else if (namePosition == 2) {
		r2 = 169;
		g2 = 169;
		b2 = 169;
	}
	else if (namePosition == 3) {
		r3 = 169;
		g3 = 169;
		b3 = 169;
	}
	else if (namePosition == 4) {
		r4 = 169;
		g4 = 169;
		b4 = 169;
	}

	// Creating the dimensions of the line
	const int LINE_SPACE = 150;
	const int LINE_THICKNESS = 4;
	const int LINE_LENGTH = 50;

	Point line1 = Point(firstLine.x, firstLine.y, r1, g1, b1);
	Point line2 = Point(firstLine.x + LINE_SPACE, firstLine.y, r2, g2, b2);
	Point line3 = Point(firstLine.x + (LINE_SPACE * 2), firstLine.y, r3, g3, b3);
	Point line4 = Point(firstLine.x + (LINE_SPACE * 3), firstLine.y, r4, g4, b4);


	plotHorizontalLine(line1, LINE_LENGTH, LINE_THICKNESS, plotter);
	plotHorizontalLine(line2, LINE_LENGTH, LINE_THICKNESS, plotter);
	plotHorizontalLine(line3, LINE_LENGTH, LINE_THICKNESS, plotter);
	plotHorizontalLine(line4, LINE_LENGTH, LINE_THICKNESS, plotter);
}

void WonScreen(SDL_Plotter& plotter)
{

	// Displaying the messages to the user as well as the points
	Point Title = Point(400, 50, 0, 0, 0);
	putString("YOU WON", Title, 10, plotter);
	Point Score = Point(400, 200, 0, 0, 0);
	putString("Your Score", Score, 6, plotter);
	Point Msg = Point(400, 300, 0, 0, 0);
	putString("Please Type your name", Msg, 6, plotter);

	// Drawing the shelf
	Point RopeBotton(125, 190, 0, 0, 0);
	drawShelf(RopeBotton, 75, plotter);

	// Displaying the options to the user
	Point Restart = Point(400, 500, 0, 0, 0);
	putString("Press B to Menu", Restart, 4, plotter);
	Point End = Point(400, 550, 0, 0, 0);
	putString("Press Esc to exit", End, 4, plotter);

	// Printing the lines for the user to print their name
	Point firstLine(400, 450);
	string userName;
	int userScore = 80;
	int namePosition = 1;

	userNameSpaces(plotter, firstLine, namePosition);
	plotter.update();

	// Getting the characters that the user inputs for their name
	while (namePosition < 5) {
		if (plotter.kbhit()) {
			char input = plotter.getKey();

			userName += input;

			userNameSpaces(plotter, firstLine, ++namePosition);

			plotter.update();
		}
	} // End of while

	  // Passing on the userName of the Highscore to the .txt file
	recordHighScore(userName, userScore);

}

void GamingScreen(SDL_Plotter& plotter, int level)
{
	Point ManPostion = Point(300, 275, 0, 0, 0);
	Point RopeBotton(200, 175, 0, 0, 0);
	drawShelf(RopeBotton, 75, plotter);
	//drawMan(ManPostion, 50, plotter);
	Point Msg = Point(550, 200, 250, 0, 0);
	putString("Please guess possible letters in this word", Msg, 2, plotter);
	int x = 550;
	int y = 550;
	int lineNumbers = level;

	if (level == 5) {
		lineNumbers = 7;
	}

	else if (level == 6) {
		lineNumbers = 8;
	}

	// Printing the lines for the correct letters to be printed on
	for (int i = 0; i <lineNumbers; i++) {
		Point line = Point(x, y, 0, 0, 0);
		plotHorizontalLine(line, 50, 4, plotter);
		x += 70;
	}
}

void ScoreBoard(SDL_Plotter& plotter)
{
	const int USER_X = 650;
	const int SCORE_X = 950;
	const int PLACE_X = 500;

	// Plotting the Man and the shelf
	Point ManPostion = Point(300, 230, 0, 0, 0);
	Point RopeBotton(200, 175, 0, 0, 0);

	// Plotting the shelf as well as the man to the left of the
	// scoreboard
	drawShelf(RopeBotton, 75, plotter);
	drawMan(ManPostion, 50, plotter);

	// Printing the titles of the columns for the users and their
	// high scores
	Point userID = Point(USER_X, 100, 0, 0, 0);
	putString("USER ID", userID, 4, plotter);
	Point Score = Point(SCORE_X, 100, 0, 0, 0);
	putString("SCORE", Score, 4, plotter);

	// Creating the variables to list out the users and their scores
	int Num = 1;
	int x;
	int y = 200;
	int theScores[USERS_ON_LEADERBOARD];
	string theUsers[USERS_ON_LEADERBOARD];

	string strnum;
	string userName;
	string userScore;

	Point listLocation;

	readHighScores(theUsers, theScores);
	// Plotting top 5 players with their user name entered and their
	// scores
	for (int i = 0;i < 5;i++) {

		y = 200 + (i * 80);

		for (int j = 0; j < 3; j++) {

			// Switching on the rank, username, and the score
			switch (j) {

				// Printing out the ranks
			case 0:
				x = PLACE_X;
				listLocation.setLocation(x, y);
				strnum = to_string(Num);
				putString(strnum, listLocation, 4, plotter);
				Num++;
				break;

				// Printing out the ssers names
			case 1:
				x = USER_X;
				listLocation.setLocation(x, y);
				userName = theUsers[i];
				putString(userName, listLocation, 4, plotter);
				break;

				// Printing out the users scores
			case 2:
				x = SCORE_X;
				listLocation.setLocation(x, y);
				userScore = to_string(theScores[i]);
				putString(userScore, listLocation, 4, plotter);
				break;
			default:
				break;
			}


		}
	}
}

#endif /* Graphics_h */