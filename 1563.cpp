#include <iostream>
#include <stack>
#include <functional>

class Defer {
	std::function<void()> st[10010];
	int top = -1;
public:
	~Defer();
	Defer(std::function<void()> func);
	void operator() (std::function<void()> func) {
		st[++top] = func;
	}
};

Defer::Defer(std::function<void()> func) {
	st[++top] = func;
}

Defer::~Defer() {
	while (top >= 0) {
		st[top--]();
	}
}

using namespace std;

void hello()
{
	std::cout << "Hello world!" << std::endl;
}


int main() {
	int* p = new int[2];
	Defer defer([&]() {delete[] p; });
	defer([&]() {std::cout << p[0] << " " << p[1] << std::endl; });
	defer([&]() {p[0] = 0, p[1] = 1; });
	defer(hello);
	p[0] = 2, p[1] = 3;
	return 0;
}