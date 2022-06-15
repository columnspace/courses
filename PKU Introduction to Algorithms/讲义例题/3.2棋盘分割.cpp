/*
http://bailian.openjudge.cn/practice/1191/
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

void input(vector<vector<int>>& board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			cin >> board[i][j];
		}
	}
}

void calculate_sum(vector<vector<int>>& sum, const vector<vector<int>>& board) {
	for (int i = 0; i < sum.size(); i++) {
		for (int j = 0; j < sum[0].size(); j++) {
			int A = i > 0 ? sum[i - 1][j] : 0;
			int B = j > 0 ? sum[i][j - 1] : 0;
			int C = (i > 0 && j > 0) ? sum[i - 1][j - 1] : 0;
			sum[i][j] = board[i][j] + A + B - C;
		}
	}
}

int get_sum(const vector<vector<int>>& sum, int x1, int y1, int x2, int y2) {
	int A = (x1 > 0 && y1 > 0) ? sum[x1 - 1][y1 - 1] : 0;
	int B = x1 > 0 ? sum[x1 - 1][y2] : 0;
	int C = y1 > 0 ? sum[x2][y1 - 1] : 0;
	int D = sum[x2][y2];
	return A + D - B - C;
}

int get_min_sumsquare(vector<vector<vector<vector<vector<int>>>>>& sumsquare, const vector<vector<int>>& sum,
	int n, int x1, int y1, int x2, int y2) {
	if (sumsquare[n][x1][x2][y1][y2] > -1) {
		return sumsquare[n][x1][x2][y1][y2];
	}
	if (n == 1) {
		int s = get_sum(sum, x1, y1, x2, y2);
		sumsquare[n][x1][x2][y1][y2] = s * s;
		return sumsquare[n][x1][x2][y1][y2];
	}
	int min_ss = -1;
	for (int i = x1; i < x2; i++) {
		int ss = get_min_sumsquare(sumsquare, sum, 1, x1, y1, i, y2) + get_min_sumsquare(sumsquare, sum, n - 1, i + 1, y1, x2, y2);
		if (min_ss == -1 || ss < min_ss) {
			min_ss = ss;
		}
	}
	for (int i = x1; i < x2; i++) {
		int ss = get_min_sumsquare(sumsquare, sum, n - 1, x1, y1, i, y2) + get_min_sumsquare(sumsquare, sum, 1, i + 1, y1, x2, y2);
		if (min_ss == -1 || ss < min_ss) {
			min_ss = ss;
		}
	}
	for (int j = y1; j < y2; j++) {
		int ss = get_min_sumsquare(sumsquare, sum, 1, x1, y1, x2, j) + get_min_sumsquare(sumsquare, sum, n - 1, x1, j + 1, x2, y2);
		if (min_ss == -1 || ss < min_ss) {
			min_ss = ss;
		}
	}
	for (int j = y1; j < y2; j++) {
		int ss = get_min_sumsquare(sumsquare, sum, n - 1, x1, y1, x2, j) + get_min_sumsquare(sumsquare, sum, 1, x1, j + 1, x2, y2);
		if (min_ss == -1 || ss < min_ss) {
			min_ss = ss;
		}
	}
	sumsquare[n][x1][x2][y1][y2] = min_ss;
	return min_ss;
}

int main() {
	int num_parts; cin >> num_parts;
	int N = 8;
	vector<vector<int>> board(N, vector<int>(N, 0));
	input(board);
	vector<vector<int>> sum(N, vector<int>(N, 0));
	calculate_sum(sum, board);
	vector<vector<vector<vector<vector<int>>>>> sumsquare(num_parts + 1, vector<vector<vector<vector<int>>>>(N,
		vector<vector<vector<int>>>(N, vector<vector<int>>(N, vector<int>(N, -1)))));
	int min_sumsquare = get_min_sumsquare(sumsquare, sum, num_parts, 0, 0, N - 1, N - 1);
	double xbar = 1.0 * sum[N - 1][N - 1] / num_parts;
	cout << setiosflags(ios::fixed) << setprecision(3) << sqrt(1.0 * min_sumsquare / num_parts - xbar * xbar) << endl;
	return 0;
}