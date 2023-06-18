#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	int* s1 = new int[n + 100];
	bool* s2 = new bool[n + 100];
	for (int i = 0; i < n + 20; ++i) {
		s2[i] = false;
	}
	s1[0] = 1;
	s2[1] = true;
	int tmp;
	for (int i = 1; i < n; ++i) {
		cin >> tmp;
		if (s1[tmp] * 2 + 1 > n + 10) {
			cout << "false";
			return 0;
		}
		if (!s2[s1[tmp] * 2]) {
			s1[i] = s1[tmp] * 2;
			s2[s1[tmp] * 2] = true;
		}
		else {
			s1[i] = s1[tmp] * 2 + 1;
			s2[s1[tmp] * 2 + 1] = true;
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (!s2[i]) {
			cout << "false";
			return 0;
		}
	}
	cout << "true";
	delete[] s1;
	delete[] s2;
	return 0;
}