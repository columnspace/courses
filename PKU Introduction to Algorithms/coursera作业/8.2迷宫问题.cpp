/*
http://bailian.openjudge.cn/practice/4127/
*/
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
void print_path(const int prev[5][5][2], int i, int j) {
	if (i > 0 || j > 0) {
		print_path(prev, prev[i][j][0], prev[i][j][1]);
	}
	cout << "(" << i << ", " << j << ")" << endl;
}
int main() {
	int maze[5][5];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> maze[i][j];
		}
	}
	int steps[5][5];
	int prev[5][5][2];
	memset(steps, 0, sizeof(steps));
	memset(prev, 0, sizeof(prev));
	vector<vector<int>> dir = { {-1,0},{0,-1},{1,0},{0,1} };
	queue<vector<int>>q;
	q.push({ 0,0 });
	while (!q.empty()) {
		vector<int> grid = q.front();
		for (int i = 0; i < 4; i++) {
			int x = grid[0], y = grid[1];
			int newx = x + dir[i][0], newy = y + dir[i][1];
			if (newx >= 0 && newx < 5 && newy >= 0 & newy < 5 && maze[newx][newy] == 0 && steps[newx][newy] == 0) {
				steps[newx][newy] = steps[x][y] + 1;
				prev[newx][newy][0] = x; prev[newx][newy][1] = y;
				if (newx == 4 && newy == 4) {
					break;
				}
				q.push({ newx,newy });
			}
		}
		q.pop();
	}
	if (steps[4][4] > 0) {
		print_path(prev, 4, 4);
	}
	return 0;
}