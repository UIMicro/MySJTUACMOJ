#include <iostream>
#include <string>

using namespace std;

int mid_walk(int* data, int i) {
	int size = 0;
	if (data[i + 1] == -2147483648) {
		cout << data[i] << ' ';
		if (data[i + 2] == -2147483648) {
			return 3;
		}
		else {
			return 2 + mid_walk(data, i + 2);
		}
	}
	else {
		size = mid_walk(data, i + 1);
		cout << data[i] << ' ';
		if (data[i + size + 1] == -2147483648) {
			return 2 + size;
		}
		else {
			return 1 + size + mid_walk(data, i + size + 1);
		}
	}
}

int back_walk(int* data, int i) {
	int size = 0;
	if (data[i + 1] == -2147483648) {
		if (data[i + 2] == -2147483648) {
			cout << data[i] << ' ';
			return 3;
		}
		else {
			size = 2 + back_walk(data, i + 2);
			cout << data[i] << ' ';
			return size;
		}
	}
	else {
		size = back_walk(data, i + 1);
		if (data[i + size + 1] == -2147483648) {
			cout << data[i] << ' ';
			return 2 + size;
		}
		else {
			size =  1 + size + back_walk(data, i + size + 1);
			cout << data[i] << ' ';
			return size;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	int n[100100];
	string data;
	//cin >> (char*)n;
	int t = 0;
	while (cin >> data) {
		if (data.at(0) == '.') {
			n[t] = -2147483648;
		}
		else {
			n[t] = stoi(data);
		}
		t++;
	}
	mid_walk(n, 0);
	cout << '\n';
	back_walk(n, 0);
	return 0;
}