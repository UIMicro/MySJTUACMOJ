#include <iostream>
#include <string>
#include <vector>

using namespace std;

class node {
private:
	node* left;
	node* right;
	int value;
public:
	node(int n);
	~node();
	friend void construct(vector<int>& T, node* n);
	friend void mid_walk(node* n);
	friend void back_walk(node* n);
};

node::node(int n) {
	value = n;
	left = NULL;
	right = NULL;
}

node::~node() {
	delete left;
	delete right;
}

void construct(vector<int>& T, node* n) {
	static auto i = T.begin();
	if (*(++i) != -1) {
		n->left = new node(*i);
		construct(T, n->left);
	}
	if (*(++i) != -1) {
		n->right = new node(*i);
		construct(T, n->right);
	}
}

void mid_walk(node* n) {
	if (n->left) mid_walk(n->left);
	cout << n->value << ' ';
	if (n->right) mid_walk(n->right);
}

void back_walk(node* n) {
	if (n->left) back_walk(n->left);
	if (n->right) back_walk(n->right);
	cout << n->value << ' ';
}

int main() {
	vector<int> s;
	string stmp;
	while (cin >> stmp) {
		if (stmp.at(0) == '.') {
			s.push_back(-1);
		}
		else {
			s.push_back(stoi(stmp));
		}
	}
	node head(s.at(0));
	construct(s, &head);
	mid_walk(&head);
	cout << '\n';
	back_walk(&head);
	return 0;
}
