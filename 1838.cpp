#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

inline void swap(char& ch1, char& ch2) {
	char chtmp = ch1;
	ch1 = ch2;
	ch2 = chtmp;
}

void reflect(char* ch, int len) {
	for (int i = 0; i < len / 2; ++i) swap(ch[i], ch[len - i - 1]);
}

bool cmp0(char* a, char* b) {
	return (strcmp(a, b) < 0);
}

int search_front(char** begin, int left, int right, char* targ, int strlen) {
	int mid;
	char strtmp[110];
	while (left <= right) {
		mid = (left + right) / 2;
		for (int i = 0; i <= strlen; ++i) {
			strtmp[i] = begin[mid][i];
			if (begin[mid][i] == 0) break;
		}
		strtmp[strlen] = '\0';
		if (strcmp(strtmp, targ) < 0) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return left;
}

int search_back(char** begin, int left, int right, char* targ, int strlen) {
	int mid;
	char strtmp[110];
	while (left <= right) {
		mid = (left + right) / 2;
		for (int i = 0; i <= strlen; ++i) {
			strtmp[i] = begin[mid][i];
			if (begin[mid][i] == 0) break;
		}
		strtmp[strlen] = '\0';
		if (strcmp(strtmp, targ) <= 0) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return right;
}

int main() {
	int n, m;
	cin >> n >> m;
	char** str = new char*[n];
	int* len = new int[n];
	int t;
	for (int i = 0; i < n; ++i) {
		str[i] = new char[110];
		cin >> str[i];
		t = 0;
		while (t < 109 && str[i][t] != 0) t++;
		len[i] = t;
		reflect(str[i], t);
	}
	sort(str, str + n, cmp0);
	char ss[110];
	char strtmp[110];
	for (int i = 0; i < m; ++i) {
		cin >> ss;
		t = 0;
		while (t < 109 && ss[t] != 0) t++;
		reflect(ss, t);
		//binary search
		int left = search_front(str, 0, n - 1, ss, t);
		int right = search_back(str, 0, n - 1, ss, t);
		int cnt = 0;
//		for (int j = left; j <= right; ++j) {
//			for (int k = 0; k <= t; ++k) {
//				strtmp[k] = str[j][k];
//				if (strtmp[k] == 0) break;
//			}
//			strtmp[t] = '\0';
//			if (strcmp(strtmp, ss) == 0) cnt++;
//		}
//		cout << cnt << endl;
		cout << right - left  + 1 << endl;
	}
}