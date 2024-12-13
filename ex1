#include <iostream>
#include <graphics.h>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int x1, y1, x2, y2, flag;
};

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
        cout << "Enter the vertices: \n";
        for (int i = 0; i < n; ++i) {
            cout << "x[" << i << "]: ";
            cin >> x[i];
            cout << "y[" << i << "]: ";
            cin >> y[i];
        }
    }

    void draw() override {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

        vector<Edge> edges(n);
        int ymax = *max_element(y.begin(), y.end());
        int ymin = *min_element(y.begin(), y.end());

        for (int i = 0; i < n; ++i) {
            edges[i].x1 = x[i];
            edges[i].y1 = y[i];
            edges[i].x2 = x[(i + 1) % n];
            edges[i].y2 = y[(i + 1) % n];
            edges[i].flag = 0;

            line(edges[i].x1, edges[i].y1, edges[i].x2, edges[i].y2);
        }
    }

    void fill() override {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

        vector<Edge> edges(n);
        int ymax = *max_element(y.begin(), y.end());
        int ymin = *min_element(y.begin(), y.end());

        for (int i = 0; i < n; ++i) {
            edges[i].x1 = x[i];
            edges[i].y1 = y[i];
            edges[i].x2 = x[(i + 1) % n];
            edges[i].y2 = y[(i + 1) % n];
            edges[i].flag = 0;
        }

        for (auto &edge : edges) {
            if (edge.y1 < edge.y2) {
                swap(edge.x1, edge.x2);
                swap(edge.y1, edge.y2);
            }
        }

        vector<float> m(n), inter_x(n), x_int(n);
        for (int i = 0; i < n; ++i) {
            float dx = edges[i].x2 - edges[i].x1;
            float dy = edges[i].y2 - edges[i].y1;
            m[i] = (dy == 0) ? 0 : dx / dy;
            inter_x[i] = edges[i].x1;
        }

        for (int yy = ymax; yy >= ymin; --yy) {
            vector<float> x_int;

            for (int i = 0; i < n; ++i) {
                if (yy > edges[i].y2 && yy <= edges[i].y1 && edges[i].y1 != edges[i].y2) {
                    edges[i].flag = 1;
                } else {
                    edges[i].flag = 0;
                }
            }

            for (int i = 0; i < n; ++i) {
                if (edges[i].flag == 1) {
                    if (yy == edges[i].y1) {
                        x_int.push_back(edges[i].x1);
                    } else {
                        x_int.push_back(inter_x[i] + (yy - edges[i].y1) * m[i]);
                        inter_x[i] = x_int.back();
                    }
                }
            }

            sort(x_int.begin(), x_int.end());

            setcolor(10);
            for (size_t i = 0; i < x_int.size(); i += 2) {
                if (i + 1 < x_int.size()) {
                    line(static_cast<int>(x_int[i]), yy, static_cast<int>(x_int[i + 1]), yy);
                }
            }

            delay(50);
        }

        closegraph();
    }
};

int main() {
    int vertices;
    cout << "Enter the number of vertices of the polygon: ";
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
