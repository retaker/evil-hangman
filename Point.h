//
//  Point.h
//  evilHangman
//
//  Created by Hayden Householder on 4/22/17.
//  Copyright © 2017 Hayden Householder. All rights reserved.
//

#ifndef Point_h
#define Point_h

struct Point {
    int x, y;
    int R, G, B;
    
    Point(int nx = 0, int ny = 0, int nR = 256, int nG = 256, int nB = 256) {
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

#endif /* Point_h */
