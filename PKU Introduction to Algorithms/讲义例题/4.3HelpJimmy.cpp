/*
http://bailian.openjudge.cn/practice/2978/
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1 << 30;
class Platform {
public:
	int left, right, height, left_time, right_time;
	Platform* left_lower, * right_lower;
	Platform(int l, int r, int h) :left(l), right(r), height(h), left_time(-1), right_time(-1), left_lower(nullptr), right_lower(nullptr) {}
	bool operator<(const Platform& p) const { return height > p.height; }
};

void find_lower_platforms(vector<Platform>& platforms, int maxHeight, int i) {
	Platform& p = platforms[i];
	if (p.left_lower && p.right_lower) {
		return;
	}
	for (int j = i + 1; j < platforms.size(); j++) {
		Platform& q = platforms[j];
		if (p.height - q.height > maxHeight) {
			return;
		}
		if (p.left_lower == nullptr && p.left >= q.left && p.left <= q.right && p.height > q.height) {
			p.left_lower = &q;
			find_lower_platforms(platforms, maxHeight, j);
		}
		if (p.right_lower == nullptr && p.right >= q.left && p.right<= q.right && p.height > q.height) {
			p.right_lower = &q;
			find_lower_platforms(platforms, maxHeight, j);
		}
	}
}

void calc_left_right_time(vector<Platform>& platforms, int maxHeight) {
	for (int i = platforms.size() - 1; i >= 0; i--) {
		Platform& p = platforms[i];
		if (p.left_lower == nullptr) {
			p.left_time = p.height <= maxHeight ? p.height : INF;
		}
		else {
			p.left_time = (p.height - p.left_lower->height) + min(p.left_lower->left_time + p.left - p.left_lower->left, p.left_lower->right_time + p.left_lower->right - p.left);
		}
		if (p.right_lower == nullptr) {
			p.right_time = p.height <= maxHeight ? p.height : INF;
		}
		else {
			p.right_time = (p.height - p.right_lower->height) + min(p.right_lower->left_time + p.right - p.right_lower->left, p.right_lower->right_time + p.right_lower->right - p.right);
		}
	}
}
int main() {
	int t; cin >> t;
	while (t--) {
		int N, X, Y, MAX; cin >> N >> X >> Y >> MAX;
		vector<Platform> platforms;
		platforms.push_back(Platform(X, X, Y));
		int l, r, h;
		for (int i = 0; i < N; i++) {
			cin >> l >> r >> h;
			platforms.push_back(Platform(l, r, h));
		}
		sort(platforms.begin(), platforms.end());
		// find the left_lower and right_lower for platforms in all possible paths, from high to low
		find_lower_platforms(platforms, MAX, 0);
		// calculate left time and right time, from low to high
		calc_left_right_time(platforms, MAX);
		cout << platforms[0].right_time << endl;
	}
}