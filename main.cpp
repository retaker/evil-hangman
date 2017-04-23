#include <iostream>
#include <fstream>
#include <cstring>

#include "SDL_Plotter.h"
#include "Point.h"

using namespace std;


int main(int argc, char ** argv)
{

	SDL_Plotter g(720, 1280);
	
	loadFont("font.txt");

	/*
	for (int i = 0;i < 26;i++) {
		for (int y = 0;y < 7;y++) {
			for (int x = 0;x < 5;x++) {
				cout << fonts[i][x][y] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	*/
	Point p1 = Point(100, 100, 255, 255, 255);
	Point p2 = Point(100, 300, 255, 255, 255);
	Point p3 = Point(100, 500, 255, 255, 255);
	while (!g.getQuit()) {
		if (g.kbhit()) {
			g.getKey();
			g.clear();
		}
		putString("\"abcdefghijklmnopqrstuvwxyz\"", p1, 4, g);
		putString("\"ABCDEFGHIJKLMNOPQRSTUVWXYZ\"", p2, 4, g);
		putString("\"0123456789\"", p3, 4, g);
		g.update();
	}
	return 0;
}