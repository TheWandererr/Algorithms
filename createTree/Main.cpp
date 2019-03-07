#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool readFile(vector<long int> &values) {

	ifstream fileIn("input.txt");
	if (fileIn.is_open()) {
		vector<long int>::iterator it;
		long int item = 0l;
		char buffer[128];
		while (fileIn.getline(buffer, 128))
		{
			item = atol(buffer);
			values.push_back(item);
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

void writeToFile(Node *&Tree, vector<long int> &values,ofstream &out)
{
	if (Tree != NULL)              
	{
		out << Tree->x<<"\n";
		writeToFile(Tree->left, values,out);
		writeToFile(Tree->right, values,out);
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
	if(x > Tree->x) {
		if (Tree->right != NULL) add_element(x, Tree->right);
		else {
			Tree->right = new Node();
			Tree->right->left = Tree->right->right = NULL;
			Tree->right->x = x;
		}
	}
}

int main() {
	vector<long int> values;
	if (readFile(values)) {
		ofstream out("output.txt");
		if (out.is_open()) {
			Node *Tree = NULL;
			for (vector<long int>::iterator it = values.begin(); it != values.end(); ++it) {
				add_element(*it, Tree);
			}
			writeToFile(Tree, values, out);
			out.close();
		}
	}
	return 0;
}
