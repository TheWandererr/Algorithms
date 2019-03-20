#include <iostream> 
#include <fstream> 
#include <algorithm> 
#include <vector> 
using namespace std;

long int** getMTX(int size) {
	long int **matrix = new long int*[size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new long int[size];
	}
	for (int i = 0; i <= size-1; i++)
	{
		matrix[i][i] = 0;
	}
	return matrix;
}

long int multiplyOrder(vector<int > vct)
{
	int size = vct.size();
	int n = size - 1;
	long int**matrix = getMTX(size);
	
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			matrix[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; k++)
			{
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k + 1][j] + vct[i - 1] * vct[j] * vct[k]);
			}
		}
	}
	return matrix[1][n];
}
void main()
{
	int number;
	int element;
	vector<int> vct;
	ifstream fin("input.txt");
	ofstream out("output.txt");
	fin >> number;
	if (number > 1) {
		fin >> element;
		vct.push_back(element);
		while (!fin.eof())
		{
			fin >> element;
			vct.push_back(element);
			fin >> element;
		}

	}
	else {
		out << 0 << endl;
	}
    out << multiplyOrder(vct) << endl;
	fin.close();
	out.close();
	system("pause");
}