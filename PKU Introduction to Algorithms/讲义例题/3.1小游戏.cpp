/*
http://bailian.openjudge.cn/practice/2802/
*/
#include <iostream>
#include <vector>
using namespace std;

bool is_inside(const vector<vector<char>>& board, int x, int y) {
	return x >= 0 & y >= 0 && y < board.size() && x < board[0].size();
}

void dfs(const vector<vector<char>>& board, vector<vector<int>>& visited, int x1, int y1, int x2, int y2, int steps, int& min_steps, int d) {
	const vector<vector<int>> dir = { {-1,0},{0,-1},{0,1},{1,0} };
	if (steps >= min_steps) {
		return;
	}
	if (x1 == x2 && y1 == y2) {
		if (steps < min_steps) {
			min_steps = steps;
		}
		return;
	}
	visited[y1][x1] = 1;
	for (int i = 0; i < 4; i++) {
		int x = x1 + dir[i][0], y = y1 + dir[i][1];
		if (is_inside(board, x, y) == false || visited[y][x] > 0) {
			continue;
		}
		else if (board[y][x] != ' ' && (x != x2 || y != y2)) {
			continue;
		}
		else if (i == d) {
			dfs(board, visited, x, y, x2, y2, steps, min_steps, i);
		}
		else {
			dfs(board, visited, x, y, x2, y2, steps + 1, min_steps, i);
		}
	}
	visited[y1][x1] = 0;
}

void input_board(vector<vector<char>>& board, int w, int h) {
	for (int i = 1; i <= h; i++) {
		getchar();
		for (int j = 1; j <= w; j++) {
			board[i][j] = getchar();
		}
	}
}
int main() {
	int w, h;
	int nBoard = 0;
	const vector<vector<int>> dir = { {-1,0},{0,-1},{0,1},{1,0} };
	while (true) {
		nBoard++;
		cin >> w >> h;
		if (w == 0 && h == 0) {
			break;
		}
		vector<vector<char>> board(h + 2, vector<char>(w + 2, ' '));
		input_board(board, w, h);
		cout << "Board #" << nBoard << ":" << endl;
		int nPairs = 0;
		int x1, y1, x2, y2;

		while (true) {
			nPairs++;
			cin >> x1 >> y1 >> x2 >> y2;
			if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) {
				cout << endl;
				break;
			}
			else {
				if (board[y1][x1] == ' ' || board[y2][x2] == ' ') {
					cout << "Invalid input. Start and end must be cards" << endl;
					continue;
				}
				int min_steps = (w + 2) * (h + 2);
				vector<vector<int>> visited(h + 2, vector<int>(w + 2, 0));
				dfs(board, visited, x1, y1, x2, y2, 0, min_steps, -1);
				if (min_steps < (w + 2) * (h + 2)) {
					cout << "Pair " << nPairs << ": " << min_steps << " segments." << endl;
				}
				else {
					cout << "Pair " << nPairs << ": impossible." << endl;
				}

			}
		}
	}
	return 0;
}