#include <stdio.h>

int main() {
	int s, n, op;
	scanf("%d%d", &s, &n);
	int front = 0, rear = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &op);
		if (op) {
			if (front == rear) {
				printf("%d %d\n", front, (rear - front + s) % s);
			}
			else {
				front = (front + 1) % s;
				printf("%d %d\n", front, (rear - front + s) % s);
			}
		}
		else {
			scanf("%d", &op);
			if ((rear - front + s) % s == s - 1) {
				s = s * 2;
			}
			if ((rear - front + s) % s < s - 1) {
				rear = (rear + 1) % s;
			}
			printf("%d %d\n", rear, (rear - front + s) % s);
		}
	}
	return 0;
}