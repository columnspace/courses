/*
http://bailian.openjudge.cn/practice/1416/#include<iostream>
*/
#include<vector>
using namespace std;
int T, N;
int best_match;
bool duplicate;
vector<int> solution;

int dfs(int target, int num) {
	if (target < 0) {
		return 0; //剪枝
	}
	if (num <= target) {
		if (T - (target - num) > best_match) {
			duplicate = false;
			best_match = T - (target - num);
			solution.clear();
			solution.push_back(num);
			return num;
		}
		else {
			if (T - (target - num) == best_match) {
				duplicate = true;
			}
			return 0;
		}
	}
	int result = 0;
	for (int divisor = 10; num / divisor > 0; divisor *= 10) {
		int remainder = num % divisor;
		int recur = dfs(target - remainder, num / divisor);
		if (recur > 0) {
			result = remainder + recur;
			solution.push_back(remainder);
		}
	}
	return result;

}


int main() {
	while (cin >> T >> N) {
		if (T == 0 && N == 0) {
			break;
		}
		duplicate = false; solution.clear(); best_match = 0;
		int closest = dfs(T, N);
		if (closest == 0) {
			cout << "error" << endl;
		}
		else if (duplicate) {
			cout << "rejected" << endl;
		}
		else {
			cout << closest;
			for (int i = 0; i < solution.size(); i++) {
				cout << " " << solution[i];
			}
			cout << endl;
		}

	}
	return 0;
}