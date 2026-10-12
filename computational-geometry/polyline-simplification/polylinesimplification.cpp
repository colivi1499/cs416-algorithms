#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <cmath>

using namespace std;

#include <iostream>
#include <vector>

using namespace std;

class SegTree {
private:
    int n;
    int rootLength;
    vector<pair<double, int>> tree;

    int queryHelper(int node, int lnode, int rnode, int l, int r) {
        if (rnode < l || lnode > r) {
            return 0;
        }
        
        if (lnode >= l && rnode <= r) {
            return this->tree[node].second;
        }
        
        int mid = (lnode + rnode) / 2;
        
        int lsum = queryHelper(
            node * 2,
            lnode,
            mid,
            l,
            r
        );
        
        int rsum = queryHelper(
            node * 2 + 1,
            mid + 1,
            rnode,
            l,
            r
        );
        
        return lsum + rsum;
    }

public:
    SegTree(int n) {
        this->n = n;
        
        rootLength = 1;
        while (rootLength < n) {
            rootLength *=2;
        }
        
        this->tree = vector<pair<double, int>>(rootLength * 2, {INFINITY, -1});
    }
    
    void update(int i, double value) {
        int curr = rootLength + i;
        
        tree[curr] = {value, i};
        
        while (curr > 1) {
            curr /= 2;
            tree[curr] = min(tree[curr * 2], tree[curr * 2 + 1]);
        }
    }
    
    int query(int l, int r) {
        return this->queryHelper(
            1,
            1,
            this->rootLength,
            l,
            r
        );
    }

    int minimumIndex() {
        return this->tree[1].second;
    }
    
};


struct Point {
    double x, y;
    int og_index;
};

double area(int i, const vector<Point>& points, const vector<int>& prev, const vector<int>& next) {
    const Point& a = points[prev[i]];
    const Point& b = points[i];
    const Point& c = points[next[i]];

    return abs((a.x * (b.y - c.y)
              + b.x * (c.y - a.y)
              + c.x * (a.y - b.y)) / 2.0);
}

int main() {
    int n, m;
    cin >> n >> m;

    SegTree tree(n);
    vector<Point> points(n+1);
    for (int i = 0; i < n + 1; i++) {
        double x, y;
        cin >> x >> y;
        points[i] = {x, y, i};
    }

    vector<int> next(n + 1), prev(n + 1);
    for (int i = 0; i < n + 1; i++) {
        next[i] = i + 1;
        prev[i] = i - 1;
    }

    for (int i = 1; i < n; i++) {
        double a = area(i, points, prev, next);
        tree.update(i, a);
    }

    int remaining = n;
    while (remaining > m) {
        int minIndex = tree.minimumIndex();

        cout << points[minIndex].og_index << "\n";

        int left = prev[minIndex];
        int right = next[minIndex];

        tree.update(minIndex, INFINITY);

        next[left] = right;
        prev[right] = left;

        if (left > 0) {
            tree.update(left, area(left, points, prev, next));
        }

        if (right < n) {
            tree.update(right, area(right, points, prev, next));
        }

        remaining--;
    }
}