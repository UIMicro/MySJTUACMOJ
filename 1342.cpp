#include <iostream>

using namespace std;
typedef unsigned long long ull;

int main() {
	int n, m, s, t;
	cin >> n >> m >> s >> t;

	bool* flag = new bool[n + 10];
	int* prev = new int[n + 10];
	ull** w = new ull*[n + 10];
	ull* dist = new ull[n + 10];
	for (int i = 0; i < n + 10; ++i) {
		flag[i] = false;
		prev[i] = 0;
		w[i] = new ull[n + 10];
		dist[i] = 1e16;
		for (int j = 0; j < n + 10; ++j) {
			w[i][j] = 1e16;
		}
	}

	int tmp1, tmp2, tmp3;
	for (int i = 0; i < m; ++i) {
		cin >> tmp1 >> tmp2 >> tmp3;
		if (tmp1 == s) {
			if (dist[tmp2] > tmp3) dist[tmp2] = tmp3;
		}
		if (tmp2 == s) {
			if (dist[tmp1] > tmp3) dist[tmp1] = tmp3;
		}
		if (w[tmp1][tmp2] > tmp3) w[tmp1][tmp2] = tmp3;
		if (w[tmp2][tmp1] > tmp3) w[tmp2][tmp1] = tmp3;
	}

	flag[s] = true;
	dist[s] = 0;
	flag[s] = 1;

	int tmp = s;
	ull min, tmpd = 1e16;
	for (int i = 0; i < n; ++i) {
		min = 1e17;
		for (int j = 1; j <= n; ++j) {
			if (!flag[j] && dist[j] < min) {
				min = dist[j];
				tmp = j;
			}
		}
		flag[tmp] = true;
		for (int i = 1; i <= n; ++i) {
			if (!flag[i] && w[tmp][i] != (ull)(1e16) && dist[i] > min + w[tmp][i]) {
				dist[i] = min + w[tmp][i];
				prev[i] = tmp;
			}
		}
	}

	cout << dist[t];

	for (int i = 0; i < n + 10; ++i) {
		delete[] w[i];
	}
	delete[] w;
	delete[] flag;
	delete[] dist;
	delete[] prev;

	return 0;
}