/*
http://bailian.openjudge.cn/practice/1088/
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1 << 30;
struct Point {
	int h, len;
	Point(int h):h(h), len(0){}
};

void input(vector<vector<Point>>& points, int R, int C) {
	int h;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> h;
			points[i][j].h = h;
		}
	}
}

int calc_len(vector<vector<Point>>& points, int i, int j, const vector<vector<int>>& dir) {
	if (points[i][j].len > 0) {
		return points[i][j].len;
	}
	int ans = 1;
	for (int k = 0; k < dir.size(); k++) {
		int ii = i + dir[k][0], jj = j + dir[k][1];
		if (points[i][j].h > points[ii][jj].h) {
			ans = max(ans, 1 + calc_len(points, ii, jj, dir));
		}
	}
	points[i][j].len = ans;
	return ans;
}

int main() {
	int R, C;
	cin >> R >> C;
	vector<vector<Point>> points(R + 2, vector<Point>(C + 2, Point(INF)));
	input(points,  R, C);
	vector<vector<int>> dir = { {1,0},{0,1},{-1,0},{0,-1} };
	int ans = 1;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			ans = max(ans, calc_len(points, i, j, dir));
		}
	}
	cout << ans << endl;
	return 0;
}
