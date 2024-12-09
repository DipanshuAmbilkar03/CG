#include <iostream>
#include <cmath>
#include <graphics.h>
using namespace std;

class Matrix {
public:
    int n, tx, ty, sx, sy;
    double a[3][3] = { {1,0,0}, {0,1,0}, {0,0,1} };
    double b[6][3], mat3[6][3];
    
    void get() {
        cout << "Enter the number of vertices: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Enter x and y coordinates: ";
            cin >> b[i][0] >> b[i][1];
            b[i][2] = 1;
        }
        cout << "\nOriginal coordinates:\n";
        displayCoords(b);
    }

    void identityMatrix() { 
        for (int i = 0; i < 3; i++) 
            for (int j = 0; j < 3; j++) 
                a[i][j] = (i == j) ? 1 : 0; 
    }

    void transformMatrix(int choice) {
        if (choice == 1) {  // Translation
            cout << "Enter tx and ty: "; cin >> tx >> ty;
            a[2][0] = tx; a[2][1] = ty;
        } 
        else if (choice == 2) {  // Scaling
            cout << "Enter sx and sy: "; cin >> sx >> sy;
            a[0][0] = sx; a[1][1] = sy;
        }
        else if (choice == 3) {  // Rotation
            double ang, cosA, sinA;
            cout << "Enter rotation angle: "; cin >> ang;
            ang = (ang * M_PI) / 180;
            cosA = cos(ang); sinA = sin(ang);
            a[0][0] = cosA; a[0][1] = -sinA; a[1][0] = sinA; a[1][1] = cosA;
        }
        displayMatrix(choice);
    }

    void multiply() {
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < 3; j++) {
                mat3[i][j] = 0;
                for (int k = 0; k < 3; k++) 
                    mat3[i][j] += b[i][k] * a[k][j];
            }
    }

    void display() {
        cout << "\nTransformed coordinates:\n";
        displayCoords(mat3);
        drawGraph(b, mat3);
    }

private:
    void displayCoords(double coords[6][3]) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) 
                cout << coords[i][j] << "\t";
            cout << "\n";
        }
    }

    void displayMatrix(int choice) {
        const char* msg[] = {"Translation Matrix", "Scaling Matrix", "Rotation Matrix"};
        cout << msg[choice - 1] << ":\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) 
                cout << a[i][j] << "\t";
            cout << "\n";
        }
    }

    void drawGraph(double orig[6][3], double trans[6][3]) {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, NULL);
        for (int i = 0; i < n - 1; i++) 
            line(orig[i][0], orig[i][1], orig[i+1][0], orig[i+1][1]);
        line(orig[n-1][0], orig[n-1][1], orig[0][0], orig[0][1]);
        
        for (int i = 0; i < n - 1; i++) 
            line(trans[i][0], trans[i][1], trans[i+1][0], trans[i+1][1]);
        line(trans[n-1][0], trans[n-1][1], trans[0][0], trans[0][1]);

        delay(5000);
        closegraph();
    }
};

int main() {
    Matrix g;
    int choice;
    char ans;
    g.get();
    
    do {
        cout << "Menu\n1. Translation\n2. Scaling\n3. Rotation\nChoose a transformation: ";
        cin >> choice;
        g.identityMatrix();
        g.transformMatrix(choice);
        g.multiply();
        g.display();
        
        cout << "\nDo you want to continue? (Y/N): ";
        cin >> ans;
    } while (ans == 'Y' || ans == 'y');
    return 0;
}
