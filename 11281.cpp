#include <iostream>
#include <queue>
using namespace std;
inline bool valid(int x, int y, int m, int n) {
	return x >= 0 && y >= 0 && x < m && y < n;
}
int main() {
	int m, n, m1, m2;
	cin >> m >> n >> m1 >> m2;
	int startx = 0, starty = 0, endx = 0, endy = 0;
	int* data = new int[m * n];
	int* dist = new int[m * n];
	bool* vis = new bool[m * n];
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> data[n * i + j];
			dist[n * i + j] = 2147483647;
			vis[n * i + j] = false;
			if (data[n * i + j] == 3) {
				startx = i;
				starty = j;
				dist[n * i + j] = 0;
			}
			if (data[n * i + j] == 4) {
				endx = i;
				endy = j;
				data[n * i + j] = 1;
			}
		}
	}
	queue<int> q;
	q.push(startx * n + starty);
	vis[startx * n + starty] = true;
	int x, y, tmp;
	while (!q.empty()) {
		tmp = q.front();
		q.pop();
		x = tmp / n;
		y = tmp % n;
		if (x == endx && y == endy) {
			cout << dist[tmp];
			return 0;
		}
		for (int i = -1; i < 2; i += 2) {
			for (int j = -1; j < 2; j += 2) {
				if (valid(x + i * m1, y + j * m2, m, n) && data[(x + i * m1) * n + y + j * m2] == 1 && !vis[(x + i * m1) * n + y + j * m2]) {
					vis[(x + i * m1) * n + y + j * m2] = true;
					dist[(x + i * m1) * n + y + j * m2] = dist[tmp] + 1;
					q.push((x + i * m1) * n + y + j * m2);
				}
				if (valid(x + i * m2, y + j * m1, m, n) && data[(x + i * m2) * n + y + j * m1] == 1 && !vis[(x + i * m2) * n + y + j * m1]) {
					vis[(x + i * m2) * n + y + j * m1] = true;
					dist[(x + i * m2) * n + y + j * m1] = dist[tmp] + 1;
					q.push((x + i * m2) * n + y + j * m1);
				}
			}
		}
	}
	delete[] data;
	delete[] dist;
	delete[] vis;
	return 0;
}