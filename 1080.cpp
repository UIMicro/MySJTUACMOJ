#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
	string s;
	cin >> s;
	stack<int> st;
	int curnum = 0;
	int op1, op2;
	for (auto i : s) {
		if (i >= '0' && i <= '9') {
			curnum = curnum * 10 + i - '0';
		}
		else if (i == '.') {
			st.push(curnum);
			curnum = 0;
		}
		else if (i == '@') {
			cout << st.top();
		}
		else {
			switch (i)
			{
			case '+':
				op1 = st.top();
				st.pop();
				op2 = st.top();
				st.pop();
				st.push(op1 + op2);
				break;
			case '-':
				op1 = st.top();
				st.pop();
				op2 = st.top();
				st.pop();
				st.push(op2 - op1);
				break;
			case '*':
				op1 = st.top();
				st.pop();
				op2 = st.top();
				st.pop();
				st.push(op1 * op2);
				break;
			case '/':
				op1 = st.top();
				st.pop();
				op2 = st.top();
				st.pop();
				st.push(op2 / op1);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}