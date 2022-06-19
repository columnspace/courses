/*
http://bailian.openjudge.cn/practice/1011/
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;
vector<int> sticks;
vector<bool> used;
int nUsed;

bool dfs(int target, int orig_target) {
	if (target == 0 && nUsed == sticks.size()) {
		return true;
	}
	if (target < 0) {
		return false;
	}
	if (target == 0) {
		return dfs(orig_target, orig_target);
	}
	for (int i = 0; i < sticks.size(); i++) {
		if (used[i]) {
			continue;
		}
		if (i > 0 && used[i - 1] == false && sticks[i] == sticks[i - 1]) {
			continue;//剪枝1
		}
		used[i] = true; nUsed++;
		int deeper = dfs(target - sticks[i], orig_target);
		if (deeper) {
			return true;
		}
		else {
			used[i] = false; --nUsed;
			if (target == orig_target) {
				return false;//剪枝2
			}
		}
	}
	return false;
}

bool try_to_recover(int target) {
	return dfs(target, target);
}

int main() {
	int N;
	while (cin>>N) {
		if (N == 0) {
			break;
		}
		sticks = vector<int>(N, 0);
		for (int i = 0; i < N; i++) {
			cin >> sticks[i];
		}
		sort(sticks.begin(), sticks.end(), greater<>());
		int total_len = accumulate(sticks.begin(), sticks.end(), 0);
		bool success = false;
		for (int target = sticks[0]; target <= total_len; target++) {
			if (total_len % target == 0) {
				used = vector<bool>(N, false); nUsed = 0;
				success = try_to_recover(target);
				if (success) {
					cout << target << endl;
					break;
				}
			}

		}
	}
	return 0;
}