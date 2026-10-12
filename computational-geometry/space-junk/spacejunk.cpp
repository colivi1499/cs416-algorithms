#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x1, y1, z1, r1, vx1, vy1, vz1;
        cin >> x1 >> y1 >> z1 >> r1 >> vx1 >> vy1 >> vz1;

        int x2, y2, z2, r2, vx2, vy2, vz2;
        cin >> x2 >> y2 >> z2 >> r2 >> vx2 >> vy2 >> vz2;

        int vx = vx1 - vx2;
        int vy = vy1 - vy2;
        int vz = vz1 - vz2;

        int dx = x1 - x2;
        int dy = y1 - y2;
        int dz = z1 - z2;

        double a = vx * vx + vy * vy + vz * vz;
        double b = 2 * (dx * vx + dy * vy + dz * vz);
        double c = dx * dx + dy * dy + dz * dz - (r1 + r2) * (r1 + r2);

        double time = -1;

        if (c <= 0) {
            time = 0;
        } else if (a > 0) {
            double discriminant = b * b - 4 * a * c;

            if (discriminant >= 0) {
                double t = (-b - sqrt(discriminant)) / (2 * a);
                if (t >= 0) {
                    time = t;
                }
            }
        }



        if (time < 0) {
            cout << "No collision" << "\n";
        } else {
            cout << fixed << setprecision(6) << time << "\n";
        }
    }
}