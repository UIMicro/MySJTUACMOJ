#include <iostream>

using namespace std;

char str[2000];
const int modder1 = 999983;
const int modder2 = 999979;
bool hash1[modder1 + 10] = { false };
bool hash2[modder2 + 10] = { false };

inline int ctoii(char ch) {
	if (ch >= '0' && ch <= '9') return ch - '0' + 1;
	if (ch >= 'a' && ch <= 'z') return ch - 'a' + 11;
	if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 37;
	return 0;
}

bool myhash1(char* ch) {
	int h = 0;
	for (int i = 0; ch[i] != 0 && i < 1999; ++i) {
		h = (long long)(h * 353 + ctoii(ch[i])) % modder1;
	}
	if (hash1[h]) return false;
	else return hash1[h] = true;
	return h;
}

bool myhash2(char* ch) {
	int h = 0;
	for (int i = 0; ch[i] != 0 && i < 1999; ++i) {
		h = (long long)(h * 61 + ctoii(ch[i])) % modder2;
	}
	if (hash2[h]) return false;
	else return hash2[h] = true;
}

int main() {
	int n, cnt = 0;
	cin >> n;
	bool res1, res2;
	for (int i = 0; i < n; ++i) {
		cin >> str;
		res1 = myhash1(str);
		res2 = myhash2(str);
		if (res1 || res2) cnt++;
	}
	cout << cnt << endl;
	return 0;
}