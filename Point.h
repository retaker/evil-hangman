#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <fstream>
#include <cstring>
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

void plotLetter(char letter, Point p, int size, SDL_Plotter& plotter) {
	int pos = (int)letter;
	if (pos > 96 && pos < 123) {
		pos -= 87;
	}
	else if(pos > 64 && pos < 91) {
		pos -= 55;
	}else if(pos == 34){
		pos = 36;
	}else{
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

#endif // !POINT_H_INCLUDED