#include <iostream>
#include <string>
//#include <stack>

using namespace std;

struct node {
	char name;
	int left;
	int right;
	int parent;
};

class stack {
	int val[50];
	int toparr;
public:
	stack();
	int top();
	void pop();
	void push(int x);
	bool empty();
};

stack::stack() {
	toparr = -1;
}

void stack::pop() {
	if (toparr >= 0) --toparr;
}

int stack::top() {
	if (toparr >= 0) return val[toparr];
	else return 0;
}

void stack::push(int x) {
	val[++toparr] = x;
}

bool stack::empty() {
	return (toparr == -1);
}

int main() {
	ios::sync_with_stdio(false);
	int n1, n2;
	node t1[50], t2[50];
	bool b1[50], b2[50];
	char f1[50], f2[50];

	for (int i = 0; i < 50; ++i) {
		t1[i].name = '\0';
		t1[i].left = -1;
		t1[i].right = -1;
		t1[i].parent = -1;

		t1[i].name = '\0';
		t2[i].left = -1;
		t2[i].right = -1;
		t2[i].parent = -1;

		b1[i] = false;
		b2[i] = false;

		f1[i] = '\0';
		f2[i] = '\0';
	}

	string s;
	cin >> n1;
	for (int i = 0; i < n1; ++i) {
		cin >> t1[i].name;
		b1[t1[i].name - 'A'] = true;

		cin >> s;
		if (s.at(0) != '-') {
			t1[i].left = stoi(s);
			t1[t1[i].left].parent = i;
		}

		cin >> s;
		if (s.at(0) != '-') {
			t1[i].right = stoi(s);
			t1[t1[i].right].parent = i;
		}
	}

	cin >> n2;
	if (n2 != n1) {
		cout << "No";
		return 0;
	}

	for (int i = 0; i < n2; ++i) {
		cin >> t2[i].name;
		b2[t2[i].name - 'A'] = true;

		cin >> s;
		if (s.at(0) != '-') {
			t2[i].left = stoi(s);
			t2[t2[i].left].parent = i;
		}

		cin >> s;
		if (s.at(0) != '-') {
			t2[i].right = stoi(s);
			t2[t2[i].right].parent = i;
		}
	}

	for (int i = 0; i < 50; ++i) {
		if (b1[i] != b2[i]) {
			cout << "No";
			return 0;
		}
	}

	//find parent for tree 1&2
	int par1 = 0;
	while (t1[par1].parent != -1) par1 = t1[par1].parent;
	int par2 = 0;
	while (t2[par2].parent != -1) par2 = t2[par2].parent;


	//iterate
	stack st;

	int tmp = par1;
	f1[t1[tmp].name - 'A'] = 1;
	if (t1[tmp].left >= 0) st.push(t1[tmp].left);
	if (t1[tmp].right >= 0) st.push(t1[tmp].right);
	while (!st.empty()) {
		tmp = st.top();
		st.pop();
		if (t1[tmp].left >= 0) st.push(t1[tmp].left);
		if (t1[tmp].right >= 0) st.push(t1[tmp].right);
		if (t1[tmp].parent >= 0) {
			f1[t1[tmp].name - 'A'] = t1[t1[tmp].parent].name;
		}
	}

	stack st1;

	tmp = par2;
	f2[t2[tmp].name - 'A'] = 1;
	if (t2[tmp].left >= 0) st1.push(t2[tmp].left);
	if (t2[tmp].right >= 0) st1.push(t2[tmp].right);
	while (!st1.empty()) {
		tmp = st1.top();
		st1.pop();
		if (t2[tmp].left >= 0) st1.push(t2[tmp].left);
		if (t2[tmp].right >= 0) st1.push(t2[tmp].right);
		if (t2[tmp].parent >= 0) {
			f2[t2[tmp].name - 'A'] = t2[t2[tmp].parent].name;
		}
	}

	for (int i = 0; i < 50; ++i) {
		if (f2[i] != f1[i]) {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
	return 0;
}