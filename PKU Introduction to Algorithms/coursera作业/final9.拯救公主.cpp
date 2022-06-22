/*
http://bailian.openjudge.cn/practice/4105/
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct State {
	int x, y, gem;
	State(int x, int y, int gem = 0) :x(x), y(y), gem(gem) {}
};

int num_bit_one(int x) {
	int res = 0;
	while (x) {
		x &= x - 1;
		++res;
	}
	return res;
}

int main() {
	int t; cin >> t;
	while (t--) {
		int r, c, k;
		cin >> r >> c >> k;
		vector<vector<char>> map(r, vector<char>(c));
		vector<vector<int>> doors;//传送门
		vector<vector<vector<int>>> steps(r, vector<vector<int>>(c, vector<int>(32, -1)));
		queue<State> q;
		const vector<vector<int>> dir = { {1,0},{0,1},{-1,0},{0,-1} };
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cin >> map[i][j];
				if (map[i][j] == '$') {
					doors.push_back({ i,j });
				}
				else if (map[i][j] == 'S') {
					steps[i][j][0] = 0;
					q.push({ i,j,0 });
				}
			}
		}
		bool found = false;
		while (!q.empty()) {
			State s = q.front(); q.pop();
			if (map[s.x][s.y] == 'E' && num_bit_one(s.gem) >= k) {
				cout << steps[s.x][s.y][s.gem] << endl;
				found = true;
				break;
			}
			for (int i = 0; i < 4; i++) {
				int newx = s.x + dir[i][0], newy = s.y + dir[i][1];
				if (newx >= 0 && newy >= 0 && newx < r && newy < c && map[newx][newy] != '#') {
					int newgem = s.gem;
					if (map[newx][newy] >= '0' && map[newx][newy] <= '9') {
						newgem |= (1 << (map[newx][newy] - '0'));
					}
					if (steps[newx][newy][newgem] == -1) {
						steps[newx][newy][newgem] = steps[s.x][s.y][s.gem] + 1;
						q.push({ newx, newy, newgem });
					}
				}
			}
			if (map[s.x][s.y] == '$') {
				for (int i = 0; i < doors.size(); i++) {
					int newx = doors[i][0], newy = doors[i][1];
					int newgem = s.gem;
					if (steps[newx][newy][newgem] == -1) {
						steps[newx][newy][newgem] = steps[s.x][s.y][s.gem];
						q.push({ newx, newy, newgem });
					}
				}
			}
		}
		if (!found) {
			cout << "oop!" << endl;
		}
	}
	return 0;
}