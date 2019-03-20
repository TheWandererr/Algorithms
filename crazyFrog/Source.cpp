#include<iostream>
#include<fstream>
#include <algorithm>
using namespace std;

int doIt(int *arr, int count) {

	int *maxCount = new int[count];
	maxCount[count - 1] = arr[count - 1];
	maxCount[count - 2] = 0;
	maxCount[count - 3] = arr[count - 1] + arr[count - 3];
	maxCount[count - 4] = arr[count - 4] + arr[count - 1];
	maxCount[count - 5] = arr[count - 5] + maxCount[count - 3];
	for (int i = count - 6; i >= 0; --i) {
		maxCount[i] = arr[i] + max(maxCount[i + 2], maxCount[i + 3]);
	}
	return maxCount[0];
}

int main() {
	ifstream fin("input.txt");
	ofstream out("output.txt");
	if (!fin.is_open()) {
		out << -1;
		return 0;
	}
	int count = 0;
	char *buff = new char[255];
	fin.getline(buff,255);
	count = atoi(buff);
	int *mosquitoesOnLily = new int[count];
	for (int i = 0; i < count; i++) {
		fin>>mosquitoesOnLily[i];
	}
	int answer;
	if (count == 1) {
		answer = mosquitoesOnLily[0];
		out << answer;
		return 0;
	}
	if (count == 2) {
		out << -1;
		return 0;
	}
	answer = doIt(mosquitoesOnLily,count);
	out << answer;
	out.close();
	fin.close();
	delete mosquitoesOnLily;
	return 0;
}