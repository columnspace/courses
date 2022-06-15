/*
http://bailian.openjudge.cn/practice/2806/
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int calc_longest_common_subseq(const string& s1, const string& s2) {
	vector<vector<int>> res(s1.size() + 1, vector<int>(s2.size() + 1, 0));
	for (int i = 1; i <= s1.size(); i++) {
		for (int j = 1; j <= s2.size(); j++) {
			if (s1[i - 1] == s2[j - 1]) {
				res[i][j] = res[i - 1][j - 1] + 1;
			}
			else {
				res[i][j] = max(res[i - 1][j], res[i][j - 1]);
			}
		}
	}
	return res[s1.size()][s2.size()];
}
int main() {
	string s1, s2;
	while (cin >> s1 >> s2) {
		cout << calc_longest_common_subseq(s1, s2) << endl;
	}
	return 0;
}