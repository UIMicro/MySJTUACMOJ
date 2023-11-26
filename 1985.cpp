#include <iostream>
#include <vector>

using namespace std;

int m, n, s, t;
vector<int> ancestor;
vector<bool> vis;
vector<vector<int>> g;
bool flag = false;
int tim = 0;

void dfs(int n) {
	if (n == t) {
		flag = true;
		return;
	}
	tim++;

	vis[n] = true;
	for (auto i : g[n]) {
		if (!vis[i]) {
			ancestor[i] = n;
			dfs(i);
		}
	}
}

int main() {
	cin >> n >> m >> s >> t;
	if (s == t) {
		cout << "1\n" << s;
		return 0;
	}
	int tmp1, tmp2;
	ancestor.resize(n + 1);
	vis.resize(n + 1);
	g.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		cin >> tmp1 >> tmp2;
		g[tmp1].push_back(tmp2);
	}
	dfs(s);
	if (!flag) {
		cout << -1;
		return 0;
	}
	vector<int> path;
	do {
		path.push_back(t);
		t = ancestor[t];
	} while (t != s);
	path.push_back(s);
	cout << path.size() << '\n';
	for (int i = path.size() - 1; i >= 0; --i) {
		cout << path[i] << ' ';
	}
	return 0;
}