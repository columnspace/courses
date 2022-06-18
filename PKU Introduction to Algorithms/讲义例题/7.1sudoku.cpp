/*
http://bailian.openjudge.cn/practice/2982/
*/
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int board[9][9];
int blankPositions[81][2];
bool row_taken[9][10];
bool col_taken[9][10];
bool square_taken[9][10];

bool is_legal(int r, int c, int val) {
	return (!row_taken[r][val]) && (!col_taken[c][val]) && (!square_taken[r / 3 * 3 + c / 3][val]);
}
void put_number(int r, int c, int val, bool put_or_remove) {
	row_taken[r][val] = put_or_remove;
	col_taken[c][val] = put_or_remove;
	square_taken[r / 3 * 3 + c / 3][val] = put_or_remove;
}

bool dfs(int nBlanks) {
	if (nBlanks == 0) {
		return true;
	}
	int i = blankPositions[nBlanks - 1][0], j = blankPositions[nBlanks - 1][1];
	for (int v = 1; v <= 9; v++) {
		if (is_legal(i, j, v)) {
			board[i][j] = v;
			put_number(i, j, v, true);
			if (dfs(nBlanks - 1)) {
				return true;
			}
			else {
				board[i][j] = 0;
				put_number(i, j, v, false);
			}
		}
	}
	return false;
}

int main() {
	int nCases; cin >> nCases;
	while (nCases--) {
		// initialize
		memset(row_taken, 0, sizeof(row_taken));
		memset(blankPositions, 0, sizeof(blankPositions));
		memset(col_taken, 0, sizeof(col_taken));
		memset(square_taken, 0, sizeof(square_taken));
		int nBlanks = 0;
		// input
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				char c; cin >> c;
				board[i][j] = c - '0';
				if (board[i][j] > 0) {
					put_number(i, j, board[i][j], true);
				}
				else {
					blankPositions[nBlanks][0] = i;
					blankPositions[nBlanks][1] = j;
					++nBlanks;
				}
			}
		}
		if (dfs(nBlanks)) {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					cout << board[i][j];
				}
				cout << endl;
			}
		}
	}
	return 0;
}