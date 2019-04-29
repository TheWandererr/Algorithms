#pragma comment(linker, "/STACK:66777216")
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <math.h>
using namespace std;
int n = 0, m = 0, k = 0;
int TOP = 0;
int* entries;
int *exits;
int** matrix;
const int WAYS = 8;
int people = 0;
int byRow[] = {-1, -1, 0, 1, 1, 1, 0, -1 };
int byColumn[] = {0, -1, -1, -1, 0, 1, 1, 1 };
stack<int> I;
stack<int> J;
bool yes = false;
int startWay = 0;
void takeOne(int, int, int, int);
int getPairIndex(int, int);
void writeAnswer() {
	FILE *out = fopen("labyrinth.out", "w");
	if (out != NULL) {
		fprintf(out, "%d", people);
		fprintf(out, "%s", "\n");
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				fprintf(out, "%d", matrix[i][j]);
				fprintf(out, "%s", " ");
			}
			fprintf(out, "%s", "\n");
		}
		fclose(out);
	}
}
void clearStack() {
	while (!I.empty()) {
		I.pop();
		J.pop();
	}
}
void readFile() {
	FILE *in = fopen("labyrinth.in", "r");
	fscanf(in, "%d", &n);
	fscanf(in, "%d", &m);
	fscanf(in, "%d", &k);
	if (k == 0 || k>m) {
		writeAnswer();
		return;
	}
	entries = new int[k];
	exits = new int[k];
	matrix = new int*[n];
	for (int i = 0; i < k; i++) {
		fscanf(in,"%d", &entries[i]);
		entries[i]--;
	}
	for (int i = 0; i < k; i++) {
		fscanf(in, "%d", &exits[i]);
		exits[i]--;
	}
	for (int i = 0; i < n; ++i) {
		matrix[i] = new int[m];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			fscanf(in, "%d", &matrix[i][j]);
		}
	}
	fclose(in);
}
bool isExist(int i, int j) {
	return i >= 0 && j >= 0 && i < n && j < m;
}
bool isExit(int posJ, int currentI) {
	if (currentI != n - 1) {

		return false;
	}
	for (int i = 0; i < k; i++) {
		if (exits[i] == posJ) {
			return true;
		}
	}
	return false;
}
bool isStart(int posJ, int currentI) {
	if (currentI != 0) {
		return false;
	}
	for (int i = 0; i < k; i++) {
		if (entries[i] == posJ) {
			return true;
		}
	}
	return false;
}
void start() {
	for (int enterNum = 0; enterNum < k; enterNum++) {
		I.push(0);
		J.push(entries[enterNum]);
		TOP++;
		matrix[I.top()][J.top()] = enterNum + 2;
		takeOne(enterNum, I.top(), J.top(), 0);
		clearStack();
		TOP = 0;
		startWay = 0;
		yes = false;
	}
}
int findNextWay(int i, int j) {
	if (i == 0 && j == -1) return getPairIndex(-1, 0);
	else if (i == 0 && j == 1) return getPairIndex(1, 0);
	else if (i == 1 && j == 0) return getPairIndex(0, -1);
	else if (i == 1 && j == 1) return getPairIndex(1, -1);
	else if (i == 1 && j == -1) return getPairIndex(-1, -1);
	else if (i == -1 && j == 1) return getPairIndex(1, 1);
	else if (i == -1 && j == -1) return getPairIndex(-1, 1);
	else if (i == -1 && j == 0) return getPairIndex(0, 1);
	return 0;
}
int getPairIndex(int fist, int second) {
	int index = 0;
	for (; index < WAYS; index++) {
		if (byRow[index] == fist && byColumn[index] == second) {
			break;
		}
	}
	return index;
}
void refactorLastRow() {
	for (int i = 0; i < m; i++) {
		if (matrix[n - 1][i] < 0) {
			matrix[n - 1][i] = -(matrix[n - 1][i]);
		}
	}
}
void takeOne(int enterNum, int startI, int startJ, int wayRoute) {
	int way = wayRoute;
	int posI = startI;
	int posJ = startJ;
	for (; ; way++) {
		if (yes) {
			break;
		}
		if (way == WAYS) {
			way = 0;
		}
		if (way == startWay - 1 || startWay == 0 && way == WAYS - 1) {
			if (!I.empty()) {
				int tmpI = I.top();
				int tmpJ = J.top();
				I.pop();
				J.pop();
				TOP--;
				if (TOP == 0) {
					yes = true;
					return;
				}
				startWay = findNextWay(I.top() - tmpI, J.top() - tmpJ);
				//takeOne(enterNum, I.top(), J.top(), startWay);
				posI = I.top();
				posJ = J.top();
				way = startWay - 1;
			}
			else {
				yes = true;
				return;
			}
		}
		if (isExist(posI + byRow[way], posJ + byColumn[way])) {
			if (matrix[posI + byRow[way]][posJ + byColumn[way]] <= 0) {
				if (!isStart(posJ + byColumn[way], posI + byRow[way])) {
					posI += byRow[way];
					posJ += byColumn[way];
					matrix[posI][posJ] = enterNum + 2;
					I.push(posI);
					J.push(posJ);
					TOP++;
					startWay = findNextWay(byRow[way], byColumn[way]);
					way = startWay - 1;
					if (isExit(posJ, posI)) {
						matrix[posI][posJ] = -matrix[posI][posJ];
						people++;
						yes = true;
						return;
					}
				}
			}
		}
	}
}
int main() {
	readFile();
	if (k > 0 && k <= m) {
		start();
		refactorLastRow();
		writeAnswer();
	}
	return 0;
}
