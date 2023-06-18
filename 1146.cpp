#include <iostream>
#include <string>

using namespace std;

class BST;

class Node {
	friend class BST;
private:
	int value;
	Node* left;
	Node* right;
public:
	Node(int x) {
		value = x;
		left = nullptr;
		right = nullptr;
	}
};

class BST {
private:
	Node* root;
	static bool search(const Node* const node, string& str, const int x) {
		if (!node) return false;
		if (node->value == x) return true;
		if (node->value > x) {
			str.push_back('l');
			return search(node->left, str, x);
		}
		if (node->value < x) {
			str.push_back('r');
			return search(node->right, str, x);
		}
	}
	static void remove(Node*& node, const int x) {
		if (!node) return;
		if (node->value == x) {
			if (node->right) {
				Node** p = &(node->right);
				while ((*p)->left) p = &((*p)->left);
				node->value = (*p)->value;
				Node* q = *p;
				(*p) = (*p)->right;
				delete q;
			}
			else {
				node = node->left;
			}
		}
		else if (node->value < x) {
			remove(node->right, x);
		}
		else {
			remove(node->left, x);
		}
	}
public:
	BST() {
		root = nullptr;
	}
	void Append(int x) {
		if (root == nullptr) root = new Node(x);
		else {
			Node* node = root;
			while (node) {
				if (x == node->value) return;
				if (x < node->value) {
					if (node->left) {
						node = node->left;
					}
					else {
						node->left = new Node(x);
					}
				}
				else {
					if (node->right) {
						node = node->right;
					}
					else {
						node->right = new Node(x);
					}
				}
			}
		}
	}
	void Search(int x) const {
		string str = "*";
		if (search(root, str, x)) {
			cout << str << endl;
		}
		else cout << "Nothing." << endl;
	}
	void Remove(int x) {
		remove(root, x);
	}
};

int main() {
	int n;
	char op;
	int val;
	BST bst;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> op >> val;
		switch (op)
		{
		case '+':
			bst.Append(val);
			break;
		case '-':
			bst.Remove(val);
			break;
		case '*':
			bst.Search(val);
			break;
		default:
			break;
		}
	}
	return 0;
}