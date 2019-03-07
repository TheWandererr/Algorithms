#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;



struct Node
{
	long int x;
	Node *left, *right;
	int depth = 0;
	set<pair<long int, string>> ways;
	bool isGreat = false;
};

bool readFile(vector<long int> &values, long int *&key) {

	ifstream fileIn("in.txt");
	if (fileIn.is_open()) {
		vector<long int>::iterator it;
		long int item = 0l;
		char buffer[128];
		short index = 0;
		while (fileIn.getline(buffer, 128))
		{
			if (index == 0) { *key = atol(buffer); index += 1; }
			else {
				item = atol(buffer);
				values.push_back(item);
			}
		}
		fileIn.close();
		return true;
	}
	return false;
}
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
		Tree->depth = 0;
	}
	if (x < Tree->x) {
		if (Tree->left != NULL) { add_element(x, Tree->left); }
		else {
			Tree->left = new Node();
			Tree->left->left = Tree->left->right = NULL;
			Tree->left->x = x;
			Tree->left->depth = Tree->depth + 1;
		}
	}
	if (x > Tree->x) {
		if (Tree->right != NULL) add_element(x, Tree->right);
		else {
			Tree->right = new Node();
			Tree->right->left = Tree->right->right = NULL;
			Tree->right->x = x;
			Tree->right->depth = Tree->depth + 1;
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
void delete_element(Node *Tree, long int key) {

	Node *parent = NULL;

	while (true) {
		if (Tree == NULL) return;
		if (Tree->x < key) {
			parent = Tree;
			Tree = Tree->right;
		}
		else if (Tree->x > key) {
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
	else if (Tree->right == NULL)
	{
		result = Tree->left;
	}
	else {
		Node *node_parent = Tree;
		Node *node_child = Tree->left;
		while (node_child->right != NULL) {
			node_parent = node_child;
			node_child = node_child->right;
		}
		result = Tree;
		Tree->x = node_child->x;
		replace_child(node_parent, node_child, node_child->left);
	}
	replace_child(parent, Tree, result);
}

void find_params_for_vertex(Node *Tree, long int *&K, set<pair<long int, long int>> &vertexes) {

	if (Tree->left == NULL && Tree->right == NULL) {
		Tree->ways.insert(make_pair(0, "list"));
	}
	else if (Tree->left == NULL) {

		for (auto &i : Tree->right->ways) {
			Tree->ways.insert(make_pair(i.first + 1, "right"));
		}
		for (auto itr : Tree->ways) {
			for (auto itr_ : Tree->ways) {
				if (itr.second != itr_.second) {
					if (itr.first + itr_.first == *K) {
						Tree->isGreat = true;
						vertexes.insert(make_pair(Tree->depth, Tree->x));
						break;
					}
				}
			}
		}
	}
	else if (Tree->right == NULL) {
		for (auto &i : Tree->left->ways) {
			Tree->ways.insert(make_pair(i.first + 1, "left"));
		}
		for (auto itr : Tree->ways) {
			for (auto itr_ : Tree->ways) {
				if (itr.second != itr_.second) {
					if (itr.first + itr_.first == *K) {
						Tree->isGreat = true;
						vertexes.insert(make_pair(Tree->depth, Tree->x));
						break;
					}
				}
			}
		}
	}
	else {
		for (auto &i : Tree->left->ways) {
			Tree->ways.insert(make_pair(i.first + 1, "left"));
		}
		for (auto &i : Tree->right->ways) {
			Tree->ways.insert(make_pair(i.first + 1, "right"));
		}
		for (auto itr : Tree->ways) {
			for (auto itr_ : Tree->ways) {
				if (itr.second != itr_.second) {
					if (itr.first + itr_.first == *K) {
						vertexes.insert(make_pair(Tree->depth, Tree->x));
						Tree->isGreat = true;
						break;
					}
				}
			}
		}
	}


}
void reverse_running(Node *Tree, long int *&K, set<pair<long int, long int>> &vertexes) {

	if (Tree != NULL)
	{
		reverse_running(Tree->left, K, vertexes);
		reverse_running(Tree->right, K, vertexes);
		find_params_for_vertex(Tree, K, vertexes);
	}
}



int main() {
	vector<long int> values;
	long int key = 0;
	long int *pkey = &key;
	if (readFile(values, pkey)) {
		ofstream out("out.txt");
		if (out.is_open()) {
			Node *Tree = NULL;
			for (vector<long int>::iterator it = values.begin(); it != values.end(); ++it) {
				add_element(*it, Tree);
			}
			set<pair<long int, long int>> vertexes; //глубина, значение
			reverse_running(Tree, pkey, vertexes);

			auto it = vertexes.begin();
			long int min_lvl = 0;
			if (it != vertexes.end()) { min_lvl = (*it).first; }
			set<long int> final_vertexes;
			for (auto iter = vertexes.begin(); iter != vertexes.end(); iter++) {
				if ((*iter).first == min_lvl) {
					final_vertexes.insert((*iter).second);
				}
			}
			if (final_vertexes.size() % 2 != 0) {
				auto it = final_vertexes.begin();
				advance(it, final_vertexes.size() / 2);
				delete_element(Tree, *it);
			}
			writeToFile(Tree, values, out);
			values.clear();
			out.close();
		}
	}
	system("pause");
	return 0;
}