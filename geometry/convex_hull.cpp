#include <bits/stdc++.h>
using namespace std;

bool ccw(point2d a, point2d b, point2d c) {
    return cross(b - a, c - a) >= 0;
    // Change to > to mantain collinear
}

vector<point2d> convex_hull(vector<point2d>& a) {
    sort(a.begin(), a.end(), [&](const point2d& p1, const point2d& p2) {
        if (p1.x < p2.x) return true;
        else {
            if (p1.x == p2.x) {
                if (p1.y < p2.y) return true;
                else return false;
            }
            else return false;
        }
    });
    a.erase(unique(a.begin(), a.end()), a.end());
    vector<point2d> c({a[0], a[1]});
    for (int i = 2; i < SZ(a); i++) {
        while (SZ(c) >= 2
               && ccw(c[SZ(c) - 2], c[SZ(c) - 1], a[i]))
            c.pop_back();
        c.push_back(a[i]);
    }
    int upper_hull_sz = SZ(c);
    for (int i = SZ(a) - 2; i >= 0; i--) {
        while (SZ(c) > upper_hull_sz
               && ccw(c[SZ(c) - 2], c[SZ(c) - 1], a[i]))
            c.pop_back();
        c.push_back(a[i]);
    }
    c.pop_back();
    reverse(c.begin(), c.end());
    return c;
}
