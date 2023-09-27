#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
typedef long long ll;

/*
   NOTE:
   std::pow is for floating point numbers.
   For integers, it's better to implement one.
*/

// FIXME: reimplement with long long int
ll pow_2(ll x) {
    return x * x;
}

struct point {
    int x, y;
    point(int _x, int _y) : x(_x), y(_y) {}
    ll distance_2(const point& other) const {
        return pow_2(x - other.x) + pow_2(y - other.y);
    }
};

// Directly translated from python... No optimizations...
long long solve(vector <point>& a, int l, int r) {
    if (l + 1 >= r) {
        return INF;
    }
    int m = (l + r) / 2;
    ll ret = min(solve(a, l, m), solve(a, m, r));
    vector<point> strip;
    for (int i = l; i < r; ++i) {
        if (pow_2(a[i].x - a[m].x) < ret) strip.push_back(a[i]);
    }
    sort(strip.begin(), strip.end(), [](point p1, point p2) -> bool {return p1.y < p2.y; });
    for (auto i = strip.begin(); i < strip.end(); ++i) {
        for (auto j = i + 1; j < strip.end(); ++j) {
            if (pow_2(i->y - j->y) >= ret) break;
            ret = min(ret, i->distance_2(*j));
        }
    }
    return ret;
}

int main() {
    int n;
    cin >> n;
    vector <point> a;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back(point(x, y));
    }
    sort(a.begin(), a.end(), [](auto& u, auto& v) {
        return u.x < v.x;
        });
    cout << solve(a, 0, n) << endl;
}