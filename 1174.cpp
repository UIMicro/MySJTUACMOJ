#include <iostream>
#include <iomanip>

using namespace std;

struct Range {
	int start, end;
	Range(int s = 0, int e = 0) { start = s; end = e; }
};

void qsort(int arr[], const int len) {
	if (len <= 0) return;
	Range* r = new Range[len];
	int p = 0;
	r[p++] = Range(0, len - 1);
	while (p) {
		Range range = r[--p];
		if (range.start >= range.end) continue;
		int mid = arr[range.end];
		int left = range.start, right = range.end - 1;
		while (left < right) {
			while (arr[left] < mid && left < right) left++;
			while (arr[right] >= mid && left < right) right--;
			swap(arr[left], arr[right]);
		}
		if (arr[left] >= arr[range.end])
			std::swap(arr[left], arr[range.end]);
		else
			left++;
		r[p++] = Range(range.start, left - 1);
		r[p++] = Range(left + 1, range.end);
	}
	delete[] r;
}

int main() {
	int m, n, size;
	cin >> m >> n;
	size = m * n;
	int* dat = new int[size];
	for (int i = 0; i < size; ++i) cin >> dat[i];
	qsort(dat, size);
	long long v, curv = 0, tmp;
	cin >> v;
	int i;
	for (i = 1; i < size; ++i) {
		tmp = i * (dat[i] - dat[i - 1]);
		if (curv + i * (dat[i] - dat[i - 1]) >= v) break;
		curv += i * (dat[i] - dat[i - 1]);
	}
	cout.setf(ios::fixed);

	if (v == 0) {
		cout << setprecision(2) << (double)dat[0] << endl;
		cout << "0.00";
		return 0;
	}
	cout << setprecision(2) << (double)dat[i - 1] + (v - curv) / (double)i << endl;
	cout << setprecision(2) << (double)i / size * 100.0;
	delete[] dat;
	return 0;
}