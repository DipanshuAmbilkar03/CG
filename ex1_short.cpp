#include <iostream>
#include <vector>
#include <graphics.h>
#include <algorithm>

using namespace std;

class Polygon {
protected:
    vector<int> x, y;
    int n;

public:
    Polygon(int vertices) : n(vertices) {
        x.resize(n);
        y.resize(n);
    }

    virtual void draw() = 0;
    virtual void fill() = 0;
};

class ConcavePolygon : public Polygon {
public:
    ConcavePolygon(int vertices) : Polygon(vertices) {}

    void readVertices() {
        cout << "Enter the vertices (x, y): \n";
        for (int i = 0; i < n; ++i) {
            cout << "Vertex " << i + 1 << ": ";
            cin >> x[i] >> y[i];
        }
    }

    void draw() override {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "");

        for (int i = 0; i < n; ++i) {
            line(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
        }
    }

    void fill() override {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "");

        // Find bounding box of the polygon
        int ymin = *min_element(y.begin(), y.end());
        int ymax = *max_element(y.begin(), y.end());

        // Scanline algorithm
        for (int yy = ymin; yy <= ymax; ++yy) {
            vector<int> x_intersections;

            for (int i = 0; i < n; ++i) {
                int x1 = x[i], y1 = y[i];
                int x2 = x[(i + 1) % n], y2 = y[(i + 1) % n];

                if ((yy >= min(y1, y2)) && (yy < max(y1, y2))) {
                    int intersect_x = x1 + (yy - y1) * (x2 - x1) / (y2 - y1);
                    x_intersections.push_back(intersect_x);
                }
            }

            sort(x_intersections.begin(), x_intersections.end());

            // Fill the polygon between pairs of intersections
            for (size_t i = 0; i < x_intersections.size(); i += 2) {
                if (i + 1 < x_intersections.size()) {
                    line(x_intersections[i], yy, x_intersections[i + 1], yy);
                }
            }
        }

        delay(5000);  // Wait before closing
        closegraph();
    }
};

int main() {
    int vertices;
    cout << "Enter the number of vertices of the polygon (min 3): ";
    cin >> vertices;

    if (vertices < 3) {
        cerr << "A polygon must have at least 3 vertices." << endl;
        return 1;
    }

    ConcavePolygon poly(vertices);
    poly.readVertices();
    poly.draw();
    poly.fill();

    return 0;
}
