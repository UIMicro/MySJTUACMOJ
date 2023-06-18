#include <iostream>

using namespace std;

int main() {
	int m, k, mnum;
	cin >> m;
	mnum = m;
	int it = 1, itbef = m;
	int* x = new int[m + 1];

	for (int i = 1; i < m; ++i) x[i] = i + 1;
	x[m] = 1;
	for (int _ = 0; _ < m - 1; ++_) {
		cin >> k;
		k--;
		k = k % mnum;
		for (int __ = 0; __ < k; ++__) {
			itbef = it;
			it = x[it];
		}
		x[itbef] = x[it];
		it = x[it];
		mnum--;
	}
	delete [] x;
	cout << it;
	return 0;
}