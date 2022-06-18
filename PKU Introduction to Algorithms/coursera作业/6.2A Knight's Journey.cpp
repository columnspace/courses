/*
http://bailian.openjudge.cn/practice/2488/
*/
#include<iostream>
#include<vector>
using namespace std;
int p, q;
vector<vector<bool>> visited;
vector<vector<int>> path;
vector<vector<int>> dir = { {-1,-2},{ 1,-2 },{-2,-1},{ 2,-1 }, {-2,1}, { 2,1 }, {-1,2},{ 1,2 } };

void print_path() {
	for (int i = 0; i < path.size(); i++) {
		char c = 'A' + path[i][1];
		int r = path[i][0] + 1;
		cout << c << r;
	}
	cout << endl;
}


bool dfs(int row, int col, int n_visited) {
	n_visited++;
	visited[row][col] = true;
	path.push_back({ row, col });
	bool res = false;
	if (n_visited == p * q) {
		print_path();
		res = true;
	}
	else {
		for (int i = 0; i < 8; i++) {
			int new_row = row + dir[i][0], new_col = col + dir[i][1];
			if (new_row >= 0 && new_row < p && new_col >= 0 && new_col < q && visited[new_row][new_col] == false) {
				res = dfs(new_row, new_col, n_visited);
				if (res) {
					break;
				}
			}
		}
	}
	visited[row][col] = false;
	path.pop_back();
	return res;
}
int main() {
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p >> q;
		visited = vector<vector<bool>>(p, vector<bool>(q, false));
		path = vector<vector<int>>();
		cout << "Scenario #" << i << ":" << endl;
		if (dfs(0, 0, 0) == false) {
			cout << "impossible" << endl;
		}
		cout << endl;
	}
	return 0;
}