
//this code show both clipped part and orignal  
#include <iostream>
#include <graphics.h>
using namespace std;

struct Point {
    int x, y;
};

void drawWindow() {
    // Drawing the rectangle
    rectangle(150, 100, 450, 350);
}

void drawLine(Point p1, Point p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

// Cohen-Sutherland line clipping function
int computeCode(Point p) {
    int code = 0;
    if (p.y < 100) code |= 8; // Top
    if (p.y > 350) code |= 4; // Bottom
    if (p.x > 450) code |= 2; // Right
    if (p.x < 150) code |= 1; // Left
    return code;
}

int clipLine(Point& p1, Point& p2) {
    int code1 = computeCode(p1);
    int code2 = computeCode(p2);
    
    // Case 1: Both endpoints are inside the window
    if ((code1 | code2) == 0) {
        return 0;
    }
    
    // Case 2: Both endpoints are outside the window in the same region
    if ((code1 & code2) != 0) {
        return 1;
    }
    
    // Case 3: One endpoint is inside, one is outside
    int codeOut = code1 ? code1 : code2;
    Point p = p1;
    float slope = float(p2.y - p1.y) / float(p2.x - p1.x);
    
    // Calculate the intersection point
    if (codeOut & 8) { // Top
        p.x = p1.x + (100 - p1.y) / slope;
        p.y = 100;
    } else if (codeOut & 4) { // Bottom
        p.x = p1.x + (350 - p1.y) / slope;
        p.y = 350;
    } else if (codeOut & 2) { // Right
        p.y = p1.y + slope * (450 - p1.x);
        p.x = 450;
    } else if (codeOut & 1) { // Left
        p.y = p1.y + slope * (150 - p1.x);
        p.x = 150;
    }

    if (codeOut == code1) {
        p1 = p;
    } else {
        p2 = p;
    }
    
    return 2;
}

int main() {
    int gd = DETECT, gm;
    Point p1, p2;
    
    cout << "Enter x1 y1: ";
    cin >> p1.x >> p1.y;
    cout << "Enter x2 y2: ";
    cin >> p2.x >> p2.y;

    initgraph(&gd, &gm, NULL);
    drawWindow();
    delay(500);
    drawLine(p1, p2);
    delay(500);

    int result = clipLine(p1, p2);
    cleardevice();
    delay(500);

    switch (result) {
        case 0:
            drawWindow();
            drawLine(p1, p2);
            break;
        case 1:
            drawWindow();
            break;
        case 2:
            drawWindow();
            drawLine(p1, p2);
            break;
    }

    delay(5000);
    closegraph();
    return 0;
}
