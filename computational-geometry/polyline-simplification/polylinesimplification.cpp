#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    int og_index;
};

int main() {
    int n, m;
    cin >> n >> m;


    vector<Point> points(n+1);
    for (int i = 0; i < n + 1; i++) {
        double x, y;
        cin >> x >> y;
        points[i] = {x, y, i};    }

    while (n > m) {
        double min_area = INFINITY;
        int index_to_remove = -1;

        for (int j = 0; j < n - 1; j++) {
            double x1 = points[j].x;
            double y1 = points[j].y;
            double x2 = points[j + 1].x;
            double y2 = points[j + 1].y;
            double x3 = points[j + 2].x;
            double y3 = points[j + 2].y;

            double area = abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
            if (area < min_area) {
                min_area = area;
                index_to_remove = j + 1;
            }
        }
        if (index_to_remove != -1) {
            cout << points[index_to_remove].og_index << "\n";
            points.erase(points.begin() + index_to_remove);
            n--;
        }
    }
}