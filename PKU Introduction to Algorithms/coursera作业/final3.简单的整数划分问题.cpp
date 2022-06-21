/*
http://bailian.openjudge.cn/practice/4117/
*/
#include<iostream>
#include<cstring>
using namespace std;
int ans[51][51];
// ans[sum][lower_bound] = # of possible splits with sum up = sum, minimum number >= lower_bound
int main() {
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i < 51; i++) {
		ans[0][i] = 1;
	}
	for (int i = 1; i < 51; i++) {
		for (int j = i; j >= 1; j--) {
			ans[i][j] = ans[i][j + 1] + ans[i - j][j];
		}
	}
	int N;
	while (cin >> N) {
		cout << ans[N][1] << endl;
	}
}