#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<string> s1(n);
	vector<string> s2(n);
	map<string, string> m;
	for (int i = 0; i < n; ++i) {
		cin >> s1[i];
	}
	for (int i = 0; i < n; ++i) {
		cin >> s2[i];
	}

	for (int i = 0; i < n; ++i) {
		if (m.count(s1[i]) == 1) {
			if (m[s1[i]] != s2[i]) {
				cout << "No";
				return 0;
			}
		}
		else m[s1[i]] = s2[i];
	}
	cout << "Yes";
	return 0;
}