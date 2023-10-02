// Inspired by https://blog.csdn.net/C20181220_xiang_m_y/article/details/89003706

#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const long long INF = 1e20;
typedef long long ll;

struct p {
	ll x, y;
	inline ll pow2(ll x) { return x * x; };
	inline double d(vector<p>::iterator o) { return sqrt(pow2(x - o->x) + pow2(y - o->y)); }
};

double solve(vector<p>::iterator l, vector<p>::iterator r) {
	if (r - l < 3) return INF;
	if (r - l == 3) return l->d(l + 1) + l->d(l + 2) + (l+1)->d(l + 2);
	auto m = l + (r - l) / 2;
	double d = min(solve(l, m), solve(m, r));

	// merge
	// consider only points with mid-d/2 <= x <= mid+d/2, and Δy < d / 2
	vector<p> tmp;
	auto t = l;
	auto llim = m->x - d / 2, rlim = m->x + d / 2;
	while (t->x < llim) ++t;
	while (t < r && t->x <= rlim) tmp.push_back(*(t++));
	sort(tmp.begin(), tmp.end(), [](auto x1, auto x2) {return x1.y < x2.y; });

	//enumerate all valid points
	for (auto i = tmp.begin(); i < tmp.end(); ++i) {
		for (auto j = i + 1; j < tmp.end(); ++j) {
			if ((j->y - i->y) > d / 2) break;
			for (auto k = j + 1; k < tmp.end(); ++k) {
				if ((k->y - i->y) > d / 2) break;
				d = min(d, i->d(j) + i->d(k) + j->d(k));
			}
		}
	}
	
	return d;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<p> ps(n);
	for (auto i = ps.begin(); i < ps.end(); ++i) {
		cin >> i->x >> i->y;
	}
	sort(ps.begin(), ps.end(), [](auto x1, auto x2) {return x1.x < x2.x; });
	cout << fixed << setprecision(9) << solve(ps.begin(), ps.end());
	return 0;
}