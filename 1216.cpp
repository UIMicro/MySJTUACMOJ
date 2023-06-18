#include <iostream>

using namespace std;

class stack {
private:
	char* head;
	size_t top;
	size_t size;
	void doubleSpace();
public:
	stack(int defsize = 4096);
	~stack();
	//stack(const stack& s);
	void push(char c);
	void pop();
	char gettop();
	char at(size_t pos);
	size_t getsize();
};

char stack::at(size_t pos) {
	return head[pos];
}

stack::stack(int defsize) {
	size = defsize;
	top = 0;
	head = new char[size];
}

stack::~stack() {
	delete[] head;
}

//stack::stack(const stack& s) {
//	size = s.size;
//	top = s.top;
//	head = new char[size];
//	for (int i = 0; i < top; ++i) {
//		head[i] = s.head[i];
//	}
//}

void stack::push(char c) {
	if (top >= size) doubleSpace();
	head[top++] = c;
}

void stack::pop() {
	if (top == 0) return;
	--top;
}

char stack::gettop() {
	if (top == 0) return '\0';
	return head[top - 1];
}


size_t stack::getsize() {
	return top;
}

void stack::doubleSpace() {
	size *= 2;
	char* tmp = new char[size];
	for (int i = 0; i < size / 2; ++i) {
		tmp[i] = head[i];
	}
	delete[] head;
	head = tmp;
}

bool checkMatch(stack& s) {
	stack t(s.gettop());
	char tmp;
	for (int i = 0; i < s.getsize(); ++i) {
		tmp = s.at(i);
		if (tmp == '(' || tmp == '[' || tmp == '{') t.push(tmp);
		if (tmp == ')') {
			if (t.gettop() == '(') t.pop();
			else return false;
		}

		if (tmp == ']') {
			if (t.gettop() == '[') t.pop();
			else return false;
		}

		if (tmp == '}') {
			if (t.gettop() == '{') t.pop();
			else return false;
		}
	}
	return t.getsize() == 0;
}

int main() {
	int n, t;
	char tmp;
	cin >> n;
	stack s;
	bool flag = true;
	bool last = false;
	for (int i = 0; i < n; ++i) {
		cin >> t;
		switch (t)
		{
		case 1:
			cin >> tmp;
			s.push(tmp);
			flag = true;
			break;
		case 2:
			s.pop();
			flag = true;
			break;
		case 3:
			if (s.getsize()) cout << s.gettop() << endl;
			flag = true;
			break;
		case 4:
			if (flag) {
				last = checkMatch(s);
				cout << (last ? "YES" : "NO") << endl;
				flag = false;
			}
			else {
				cout << (last ? "YES" : "NO") << endl;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}