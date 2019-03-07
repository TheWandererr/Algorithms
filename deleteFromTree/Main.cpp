#include <fstream>
#include <iostream>
#include <vector>
using namespace std;


bool readFile(vector<long int> &values, long int *&key) {

	ifstream fileIn("input.txt");
	if (fileIn.is_open()) {
		bool flag = false;
		vector<long int>::iterator it;
		long int item = 0l;
		char buffer[128];
		while (fileIn.getline(buffer, 128))
		{
			if (buffer[0] == '\0') {flag =  true;}
			if (flag == false) {
				*key = atol(buffer);
			}
			else {
				if (buffer[0] != '\0') {
				item = atol(buffer);
				values.push_back(item);
			}
			}
		}
		fileIn.close();
		return true;
	}
	return false;
}

struct Node
{
	long int x;
	Node *left, *right;
};

void writeToFile(Node *&Tree, vector<long int> &values, ofstream &out)
{
	if (Tree != NULL)
	{
		out << Tree->x << "\n";
		writeToFile(Tree->left, values, out);
		writeToFile(Tree->right, values, out);
	}
}

void add_element(long int x, Node *&Tree)
{
	if (Tree == NULL)
	{
		Tree = new Node();
		Tree->x = x;
		Tree->left = Tree->right = NULL;
	}
	if (x < Tree->x) {
		if (Tree->left != NULL) add_element(x, Tree->left);
		else {
			Tree->left = new Node();
			Tree->left->left = Tree->left->right = NULL;
			Tree->left->x = x;
		}
	}
	if (x > Tree->x) {
		if (Tree->right != NULL) add_element(x, Tree->right);
		else {
			Tree->right = new Node();
			Tree->right->left = Tree->right->right = NULL;
			Tree->right->x = x;
		}
	}
}

void replace_child(Node *&parent, Node *&old_, Node *&new_) {
	if (parent == NULL) *old_ = *new_;
	else if (parent->left == old_) {
		parent->left = new_;
	}
	else if (parent->right == old_) {
		parent->right = new_;
	}
}

void delete_element(Node *Tree, long int *&key) {

	Node *parent = NULL;

	while (true) {
		if (Tree == NULL) return;
		if (Tree->x < *key) {
			parent = Tree;
			Tree = Tree->right;
		}
		else if (Tree->x > *key) {
			parent = Tree;
			Tree = Tree->left;
		}
		else {
			break;
		}
	}
	Node *result = NULL;

	if (Tree->left == NULL) {
		result = Tree->right;
	}
	else if(Tree->right == NULL)
	{
		result = Tree->left;
	}
	else {
		Node *node_parent = Tree;
		Node *node_child = Tree->right;
		while (node_child->left != NULL) {
			node_parent = node_child;
			node_child = node_child->left;
		}
		result = Tree;
		Tree->x = node_child->x;
		replace_child(node_parent, node_child, node_child->right);
	}
	replace_child(parent, Tree, result);
}



int main() {
	vector<long int> values;
	long int key = 0;
	long int *pkey = &key;
	bool isExist = false;
	if (readFile(values, pkey)) {
		ofstream out("output.txt");
		if (out.is_open()) {
			Node *Tree = NULL;
			for (vector<long int>::iterator it = values.begin(); it != values.end(); ++it) {
				add_element(*it, Tree);
				if (*pkey == *it) isExist = true;
			}
			if (isExist) {
				if (Tree->left == NULL && Tree->right == NULL) {
					Tree = NULL;
			}
				else {
					delete_element(Tree, pkey);
				}
			}
			writeToFile(Tree, values, out);
			out.close();
		}
	}
	system("pause");
	return 0;
}
