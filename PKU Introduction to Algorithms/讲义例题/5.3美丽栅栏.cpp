/*
http://bailian.openjudge.cn/practice/1037
*/
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
void update_count(vector<vector<vector<long long>>>& count, int N) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = 1; k <= j - 1; k++) {
				count[i][j][1] += count[i - 1][k][0];
			}
			for (int k = j; k <= i - 1; k++) {
				count[i][j][0] += count[i - 1][k][1];
			}
		}
	}
}

void print_permulation_from_order(const vector<vector<vector<long long>>>& count, int N, long long order) {
	vector<int> res;
	vector<int> used(N + 1, 0);
	for (int i = 1; i <= N; i++) { // the i-th number to put in vector
		long long to_check;
		for (int j = 1; j <= N; j++) { //try to put j at i-th position
			if (used[j] > 0) {
				continue;
			}
			int used_before_j = accumulate(used.begin() + 1, used.begin() + j, 0);
			if (i == 1) {
				to_check = count[N - i + 1][j - used_before_j][0] + count[N - i + 1][j - used_before_j][1];
			}
			else if (i == 2) {
				if (res[0] > j) {
					to_check = count[N - i + 1][j - used_before_j][0];
				}
				else {
					to_check = count[N - i + 1][j - used_before_j][1];
				}
			}
			else if (res[res.size() - 2] < res[res.size() - 1]) {
				if (res[res.size() - 1] < j) {
					continue;
				}
				else {
					to_check = count[N - i + 1][j - used_before_j][0];
				}
			}
			else {
				if (res[res.size() - 1] < j) {
					to_check = count[N - i + 1][j - used_before_j][1];
				}
				else {
					continue;
				}
			}
			if (order > to_check) {
				order -= to_check;
			}
			else {
				res.push_back(j);
				used[j] = 1;
				break;
			}
		}
	}
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	cout << endl;
}


int main() {
	int K; cin >> K;
	// count[N][start][dir]: number of legal solutions for N numbers, start with start, dir = UP or DOWN
	// N = 1,...,20, start = 1,...,N, dir=0 for UP, 1 for DOWN
	vector<vector<vector<long long>>> count(21, vector<vector<long long>>(21, vector<long long>(2, 0)));
	count[1][1][0] = 1;
	count[1][1][1] = 1;
	update_count(count, 20);
	while (K--) {
		int N;
		long long C;
		cin >> N >> C;
		print_permulation_from_order(count, N, C);
	}
	return 0;
}