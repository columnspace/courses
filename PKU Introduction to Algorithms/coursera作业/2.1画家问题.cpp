/*
http://cxsjsxmooc.openjudge.cn/test/Y/
*/
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
void input(vector<vector<int>>& wall) {
	int n = wall.size() - 2;
	char c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> c;
			wall[i][j] = c == 'w' ? 1 : 0;//white = 1, yellow = 0, target all 0
		}
	}
}

void enumerate(const vector<vector<int>>& wall, int& min_steps) {
	int n = wall.size() - 2;
	vector<vector<int>> switches(n + 2, vector<int>(n + 2, 0));
	for (int k = 0; k < (1 << n); k++, switches[1][1]++) {
		for (int i = 1; switches[1][i] > 1; i++) {
			switches[1][i] = 0;
			switches[1][i+1]++;
		}
		bool is_solution = true;
		int steps = accumulate(switches[1].begin(), switches[1].end(), 0);
		if (min_steps >= 0 && steps >= min_steps) {
			is_solution = false;
		}
		for (int i = 1; i < n && is_solution; i++) {
			for (int j = 1; j <= n && is_solution; j++) {
				switches[i + 1][j] = (wall[i][j] + switches[i - 1][j] + switches[i][j - 1] + switches[i][j] + switches[i][j + 1]) % 2;
				steps += switches[i + 1][j];
				if (min_steps >= 0 && steps >= min_steps) {
					is_solution = false;
				}
			}
		}
		for (int j = 1; j <= n && is_solution; j++) {
			int i = n;
			if ((wall[i][j] + switches[i - 1][j] + switches[i][j - 1] + switches[i][j] + switches[i][j + 1]) % 2 == 1) {
				is_solution = false;
				break;
			}
		}
		if (is_solution && (min_steps == -1 || steps < min_steps)) {
			min_steps = steps;
		}
	}
}
int main() {
	int n; cin >> n;
	vector<vector<int>> wall(n + 2, vector<int>(n + 2, 0));
	input(wall);
	int min_steps = -1;
	enumerate(wall, min_steps);
	if (min_steps >= 0) {
		cout << min_steps << endl;
	}
	else {
		cout << "inf" << endl;
	}
	return 0;
}