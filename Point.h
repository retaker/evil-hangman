#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

struct Point {
	int x, y;
	int R, G, B;

	Point(int nx = 0, int ny = 0, int nR = 255, int nG = 255, int nB = 255) {
		x = nx;
		y = ny;
		R = nR;
		G = nG;
		B = nB;
	}

	void setColor(int nR = 0, int nG = 0, int nB = 0) {
		R = nR;
		G = nG;
		B = nB;
	}
};


#endif // !POINT_H_INCLUDED