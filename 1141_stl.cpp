#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
	unordered_map<string, bool> m;
	int n;
	cin >> n;
	string s;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		m[s] = true;
	}
	cout << m.size();
	return 0;
}