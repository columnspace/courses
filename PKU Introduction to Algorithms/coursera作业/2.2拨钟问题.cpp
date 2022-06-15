/*
http://cxsjsxmooc.openjudge.cn/test/Z/
*/
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
	vector<int> clocks(9,0);
	for (int i = 0; i < clocks.size(); i++) {
		cin >> clocks[i];
	}
	vector<vector<int>> operations({ {0,1,3,4},
									 {0,1,2},
									 {1,2,4,5},
								     {0,3,6},
									 {1,3,4,5,7},
									 {2,5,8},
									 {3,4,6,7},
									 {6,7,8},
									 {4,5,7,8} });
	vector<int> num_operations(9,0);
	int min_steps = -1;
	vector<int> best_operations;
	for (int k = 0; k < (1 << (2 * 9)); k++, num_operations[0]++) {
		//enumerate number operations
		for (int i = 0; num_operations[i] > 3; i++) {
			num_operations[i] -= 4;
			num_operations[i + 1]++;
		}
		// check steps for early exit
		int steps = accumulate(num_operations.begin(), num_operations.end(), 0);
		if (min_steps > -1 && steps >= min_steps) {
			continue;
		}
		//apply operations
		vector<int> clocks_copy(clocks);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < operations[i].size(); j++) {
				clocks_copy[operations[i][j]]+=num_operations[i];
			}
		}
		// check whether is a solution
		bool is_solution = true;
		for (int i = 0; i < 9; i++) {
			if (clocks_copy[i] % 4 > 0) {
				is_solution = false;
				break;
			}
		}
		if (is_solution) {
			if (min_steps == -1 || steps < min_steps) {
				min_steps = steps;
				best_operations = num_operations;
			}
		}
	}
	for (int i = 0; i < best_operations.size(); i++) {
		for (int j = 0; j < best_operations[i]; j++) {
			cout << i + 1 << " ";
		}
	}
	return 0;
}