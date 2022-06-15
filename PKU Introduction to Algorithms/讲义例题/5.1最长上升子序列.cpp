/*
http://bailian.openjudge.cn/practice/2757/
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	int N; cin >> N;
	vector<int> seq(N);
	for (int i = 0; i < N; i++) {
		cin >> seq[i];
	}
	vector<int> ans(N, 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (seq[i] > seq[j]) {
				ans[i] = max(ans[i], ans[j] + 1);
			}
		}
	}
	cout << *max_element(ans.begin(), ans.end()) << endl;
	return 0;
}