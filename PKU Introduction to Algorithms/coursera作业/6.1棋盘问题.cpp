/*
http://bailian.openjudge.cn/practice/1321/
*/
#include<iostream>
#include<vector>
using namespace std;
int n;
vector<vector<char>> board;
vector<bool> col_used;
int dfs(int num_to_put, int start_row) {
	if (num_to_put == 0) {
		return 1;
	}
	int res = 0;
	for (int i = start_row; i < n; i++) {
		if (n - i < num_to_put) {
			break; //剪枝
		}
		for (int j = 0; j < n; j++) {
			if (board[i][j] == '#' && col_used[j] == false) {
				col_used[j] = true;
				res += dfs(num_to_put - 1, i + 1);
				col_used[j] = false;
			}
		}
	}
	return res;
}
int main() {
	int k;
	while (cin >> n >> k) {
		if (n == -1 && k == -1) {
			break;
		}
		board = vector<vector<char>>(n, vector<char>(n));
		col_used = vector<bool>(n, false);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> board[i][j];
			}
		}
		cout << dfs(k, 0) << endl;
	}
	return 0;
}