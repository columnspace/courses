/*
http://bailian.openjudge.cn/practice/2812/
*/
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Point {
	int x;
	int y;
	Point(int x, int y):x(x), y(y){}
	bool operator<(const Point& p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

bool is_inside(int x, int y, int rows, int cols) {
	return x >= 1 && x <= rows&& y >= 1 && y <= cols;
}

int longest_path(const set<Point>& points, int rows, int cols) {
	int max_steps = 0;
	for (auto it1 = points.begin(); it1 != points.end(); it1++) {
		auto it2 = it1; it2++;
		for (; it2 != points.end(); it2++) {
			int dx = it2->x - it1->x;
			int dy = it2->y - it1->y;
			// 1. prev point should be out of field
			if (is_inside(it1->x - dx, it1->y - dy, rows, cols)) {
				continue;
			}
			// 2. should be longer than longest_path_length, otherwise early exit
			if (is_inside(it1->x + max_steps * dx, it1->y + max_steps * dy, rows, cols) == false) {
				continue;
			}
			int steps = 1;
			while (true) {
				Point p(it1->x + steps * dx, it1->y + steps * dy);
				if (is_inside(p.x, p.y, rows, cols) == false) {
					max_steps = steps > max_steps ? steps : max_steps;
					break;
				}
				else if (points.find(p)==points.end()) {
					break;
				}
				else {
					steps++;
				}
			}
		}
	}
	return max_steps < 3 ? 0 : max_steps;
}

int main() {
	int R, C, N;
	cin >> R >> C >> N;
	int x, y;
	set<Point> points;
	while (N--) {
		cin >> x >> y;
		points.insert(Point(x, y));
	}
	cout << longest_path(points, R, C) << endl;
	return 0;
}
