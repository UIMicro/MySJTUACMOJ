#include <iostream>
#include <vector>

using std::cin, std::vector, std::cout;

int n;
vector<int> swap_time;
vector<int> data;

void compute_reverse(vector<int>::iterator l, vector<int>::iterator r) {
	if (l == r) return;
	if (l + 1 == r) return;
	//if (r == l + 1) {
	//	if (*r < *l) {
	//		swap_time[*l]++;
	//		swap_time[*r]++;
	//		std::swap(l, r);
	//	}
	//	return;
	//}
	auto m = l + (r - l) / 2;
	compute_reverse(l, m);
	compute_reverse(m, r);
	vector<int> temp;
	temp.resize(r - l);
	auto f = temp.begin();
	auto lw = l, rw = m;
	while (lw < m && rw < r) {
		if (*rw < *lw) {
			swap_time[*rw] += (m - lw);
			*(f++) = *(rw++);
		}
		else {
			swap_time[*lw] += (rw - m);
			*(f++) = *(lw++);
		}
	}
	while (lw < m) {
		swap_time[*lw] += (rw - m);
		*(f++) = *(lw++);
	}
	while (rw < r) {
		*(f++) = *(rw++);
	}
	for (auto i : temp) {
		*(l++) = i;
	}
}

int main() {
	cin >> n;
	data.resize(n);
	swap_time.resize(n + 1);
	for (int i = 0; i < n; ++i) cin >> data[i];
	compute_reverse(data.begin(), data.end());
	for (auto i = swap_time.begin() + 1; i < swap_time.end(); ++i) cout << *i << ' ';
	return 0;
}