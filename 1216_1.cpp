#include <cstdio>
#include <stdlib.h>

inline char getm(char c) {
	switch (c)
	{
	case '}':
		return '{';
	case ')':
		return '(';
	case ']':
		return '[';
	default:
		return '\0';
	}
}

int main() {
	int n, op, top = 0, top1 = 0, left_cnt = 0;
	scanf("%d", &n);
	char tmp;
	char* c = (char*)malloc((n + 1) * sizeof(char));
	char* s = (char*)malloc((n + 1) * sizeof(char));
	int j;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			scanf("%*c%c%", &tmp);
			c[top++] = tmp;
			if (top1 == 0) {
				s[top1++] = tmp;
			}
			else {
				if (getm(tmp) == s[top1 - 1]) {
					top1--;
					break;
				}
				s[top1++] = tmp;
			}
			break;
		case 2:
			if (top > 0) {
				top--;
			}
			if (top == 0) {
				top1 = 0;
				break;
			}
			top1 = 0;
			s[top1++] = c[0];
			j = 1;
			while (j < top) {
				if (top1 > 0 && getm(c[j]) != '\0' && getm(c[j]) == s[top1 - 1]) {
					top1--;
					j++;
					continue;
				}
				s[top1++] = c[j];
				++j;
			}
			break;
		case 3:
			if (top > 0) printf("%c\n", c[top - 1]);
			break;
		case 4:
			if (!top1) printf("YES\n");
			else printf("NO\n");
			break;
		default:
			break;
		}
	}
	free(c);
	free(s);
	return 0;
}