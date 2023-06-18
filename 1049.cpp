#include <cstdio>

int front_char_index[256];
int mid_char_index[256];

char* front_pointer, * mid_pointer;

int find(char targ, char* x, int n) {
	if (x - front_pointer < 1050) {
		return front_char_index[targ] - (x - front_pointer);
	}
	else {
		return mid_char_index[targ] - (x - mid_pointer);
	}
	//	for (int i = 0; i < n; ++i) {
	//		if (x[i] == targ) return i;
	//	}
	return -1;
}

void construct(char* front, char* mid, char* res, int n, int front_size, int mid_size) {
	res[n] = front[0];

	int root_pos = find(front[0], mid, mid_size);

	int max = 0, tmp;
	for (int i = 0; i < root_pos; ++i) {
		tmp = find(mid[i], front + 1, front_size - 1) + 1;
		if (tmp > max) max = tmp;
	}

	//construct left subtree
	if (max > 0) {
		construct(front + 1, mid, res, n * 2, max, root_pos);
	}

	if (front_size - max - 1 > 0) {
		construct(front + max + 1, mid + root_pos + 1, res, n * 2 + 1, front_size - max - 1, mid_size - root_pos - 1);
	}
}

int main() {
	char front[1100], mid[1100];
	front_pointer = front;
	mid_pointer = mid;
	char res[1100];

	for (int i = 0; i < 1100; ++i) {
		res[i] = 0;
	}
	fgets(front, 1010, stdin);
	fgets(mid, 1010, stdin);

	for (int i = 1010; i >= 0; --i) {
		if (front[i] < 'A' || front[i] > 'Z') front[i] = 0;
		if (mid[i] < 'A' || mid[i] > 'Z') mid[i] = 0;
		else break;
	}

	int size = 0;
	for (int i = 0; i < 1100; ++i) {
		if (!front[i]) {
			size = i;
			break;
		}
		front_char_index[front[i]] = i;
		mid_char_index[mid[i]] = i;
	}

	construct(front, mid, res, 1, size, size);

	int maxn = 1001;
	while (!res[maxn]) maxn--;
	for (int i = 1; i <= maxn; ++i) {
		if (res[i]) printf("%c ", res[i]);
		else printf("NULL ");
	}

	return 0;
}