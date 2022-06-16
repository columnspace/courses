/*
http://bailian.openjudge.cn/practice/2815/
*/
#include<iostream>
#include<vector>
using namespace std;
void dfs(int i, int j, vector<vector<int>>& color, const vector<vector<int>>& castle, int& num_rooms, int& area, int& max_area) {
	if (color[i][j]) {
		return;
	}
	color[i][j] = num_rooms;
	area++;
	if (area > max_area) {
		max_area = area;
	}
	if ((castle[i][j] & 1) == 0) { dfs(i, j - 1, color, castle, num_rooms, area, max_area); }
	if ((castle[i][j] & 2) == 0) { dfs(i - 1, j, color, castle, num_rooms, area, max_area); }
	if ((castle[i][j] & 4) == 0) { dfs(i, j + 1, color, castle, num_rooms, area, max_area); }
	if ((castle[i][j] & 8) == 0) { dfs(i + 1, j, color, castle, num_rooms, area, max_area); }
}

int main() {
	int m, n; cin >> m >> n;
	vector<vector<int>> castle(m + 2, vector<int>(n + 2, 0));
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> castle[i][j];
		}
	}
	vector<vector<int>> color(m + 2, vector<int>(n + 2, 0));
	int num_rooms = 0;
	int max_area = 0;
	int area = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (color[i][j]) {
				continue;
			}
			++num_rooms; area = 0;
			dfs(i, j, color, castle, num_rooms, area, max_area);
		}
	}
	cout << num_rooms << endl << max_area << endl;
	return 0;
}