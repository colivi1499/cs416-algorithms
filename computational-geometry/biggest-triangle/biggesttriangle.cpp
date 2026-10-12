#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <cmath>

using namespace std;

struct line {
    double a, b, c;
};

pair<double, double> intersection(const line& first, const line& second) {
    double det = first.a * second.b - second.a * first.b;
    if (det == 0) {
        return {0, 0};
    }
    double x = (second.b * first.c - first.b * second.c) / det;
    double y = (first.a * second.c - second.a * first.c) / det;
    return {x, y};
}

int main() {
    int n;
    cin >> n;
    
    vector<line> lines(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;

        cin >> x1 >> y1 >> x2 >> y2;
        lines[i].a = y2 - y1;
        lines[i].b = x1 - x2;
        lines[i].c = x2 * y1 - x1 * y2;
    }
    
    double max = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (lines[i].a * lines[j].b - lines[j].a * lines[i].b == 0) {
                    continue;
                }
                if (lines[i].a * lines[k].b - lines[k].a * lines[i].b == 0) {
                    continue;
                }
                if (lines[j].a * lines[k].b - lines[k].a * lines[j].b == 0) {
                    continue;
                }
                double det = lines[i].a * (lines[j].b * lines[k].c - lines[k].b * lines[j].c) -
                             lines[i].b * (lines[j].a * lines[k].c - lines[k].a * lines[j].c) +
                             lines[i].c * (lines[j].a * lines[k].b - lines[k].a * lines[j].b);
                if (det == 0) {
                    continue;
                }
                double x1 = intersection(lines[i], lines[j]).first;
                double y1 = intersection(lines[i], lines[j]).second;
                double x2 = intersection(lines[j], lines[k]).first;
                double y2 = intersection(lines[j], lines[k]).second;
                double x3 = intersection(lines[k], lines[i]).first;
                double y3 = intersection(lines[k], lines[i]).second;

                double perimeter = hypot(x1 - x2, y1 - y2) + hypot(x2 - x3, y2 - y3) + hypot(x3 - x1, y3 - y1);
                if (perimeter > max) {
                    max = perimeter;
                }
            }
        }
    }

    if (max == 0) {
        cout << "no triangle" << endl;
    } else {
        cout << fixed << setprecision(6) << max << endl;
    }

}