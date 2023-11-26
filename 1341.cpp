#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> g;
vector<int> DFN;
vector<int> LOW;
stack<int> st;
vector<bool> inStack;
vector<bool> vis;
vector<int> sccid;
int timestamp = 0;
int scccnt = 0;

void tarjan(int u) {
	DFN[u] = LOW[u] = ++timestamp;
	vis[u] = true;
	st.push(u);
	inStack[u] = true;
	for (auto i = g[u].begin(); i < g[u].end(); ++i) {
		if (!vis[*i]) {
			tarjan(*i);
			LOW[u] = min(LOW[u], LOW[*i]);
		}
		else if (inStack[*i]) {
			LOW[u] = min(LOW[u], LOW[*i]);
		}
	}

	int v;
	if (DFN[u] == LOW[u]) {
		scccnt++;
		do {
			v = st.top();
			st.pop();
			inStack[v] = false;
			sccid[v] = scccnt;
			//cout << v << '.';
		} while (u != v);
		//cout << '\n';
	}
}

int main() {
	int m, n, i, j, a, b;
	cin >> n >> m;
	g.resize(n * 2 + 1);
	inStack.resize(n * 2 + 1);
	DFN.resize(n * 2 + 1);
	LOW.resize(n * 2 + 1);
	sccid.resize(n * 2 + 1);
	vis.resize(n * 2 + 1);
	// 2i-1: i=1 2i: i=0
	for (int tmp = 0; tmp < m; ++tmp) {
		cin >> i >> a >> j >> b;
		g[i * 2 - 1 + a].push_back(j * 2 - b);
		g[j * 2 - 1 + b].push_back(i * 2 - a);
	}
	for (int i = 1; i <= n * 2; ++i) {
		if (!vis[i]) tarjan(i);
	}
	for (int i = 1; i <= n; ++i) {
		if (sccid[i * 2] == sccid[i * 2 - 1]) {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; ++i) {
		if (sccid[i * 2] < sccid[i * 2 - 1]) {
			cout << "0 ";
		}
		else {
			cout << "1 ";
		}
	}
	return 0;
}