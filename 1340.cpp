// Two pass DFS
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> ginv;
int n, m;
int f_time = 0;
vector<int> torder;
bool* vis;
unsigned long long cnt;
unsigned long long sum = 0;

void dfs(int n) {
	vis[n] = true;
	for (auto i = g[n].begin(); i < g[n].end(); ++i) {
		if (!vis[*i]) {
			dfs(*i);
		}
	}
	torder.push_back(n);
}

void dfs01(int n) {
	vis[n] = true;
	for (auto i = ginv[n].begin(); i < ginv[n].end(); ++i) {
		if (!vis[*i]) {
			dfs01(*i);
		}
	}
	cnt++;
}

void dfs1() {
	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) {
			dfs(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		vis[i] = false;
	}
	for (int i = torder.size() - 1; i >= 0; i--) {
		cnt = 0;
		if (!vis[torder[i]]) {
			dfs01(torder[i]);
		}
		sum += cnt * (cnt - 1) / 2;
	}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	vis = new bool[n + 1];
	g.resize(n + 1);
	ginv.resize(n + 1);
	int u, v;
	for (int i = 0; i < m; ++i) {
		vis[i + 1] = false;
		cin >> u >> v;
		g[u].push_back(v);
		ginv[v].push_back(u);
	}
	dfs1();
	cout << sum;
	delete[] vis;
	return 0;
}