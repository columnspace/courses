/*
http://noi.openjudge.cn/ch0205/7218/
*/
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
int main() {
	int T; cin >> T;
	vector<vector<int>> dir = { {0,1},{0,-1},{1,0},{-1,0} };
	while (T--) {
		int R, C; cin >> R >> C;
		vector<vector<char>> map(R, vector<char>(C));
		vector<vector<bool>> visited(R, vector<bool>(C, false));
		queue<vector<int>> q;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cin >> map[i][j];
				if (map[i][j] == 'S') {
					q.push({ i,j,0 });
					visited[i][j] = true;
				}
			}
		}
		bool found = false;
		while (!q.empty() && !found) {
			int x = q.front()[0], y = q.front()[1], steps = q.front()[2];
			for (int i = 0; i < 4; i++) {
				int newx = x + dir[i][0], newy = y + dir[i][1];
				if (newx >= 0 && newy >= 0 && newx < R && newy < C) {
					if (visited[newx][newy] == false && map[newx][newy] == '.') {
						visited[newx][newy] = true;
						q.push({ newx, newy, steps + 1 });
					}
					else if (map[newx][newy] == 'E') {
						cout << steps + 1 << endl;
						found = true;
						break;
					}
				}
			}
			q.pop();
		}
		if (!found) {
			cout << "oop!" << endl;
		}
	}
	return 0;
}