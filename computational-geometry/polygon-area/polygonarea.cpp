#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n != 0) {
        
        vector<pair<int, int>> points(n);
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            points[i] = {x, y};
        }
        
        double sum = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            sum += points[i].first * points[j].second;
            sum -= points[j].first * points[i].second;
        }
        string dir = (sum < 0) ? "CW" : "CCW";
        cout << dir << " ";
        cout << fixed << setprecision(1) << abs(sum) / 2 << "\n";
        cin >> n;
    }

}