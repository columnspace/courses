/*
http://bailian.openjudge.cn/practice/4119/
*/
#include<iostream>
#include<cstring>
using namespace std;
// split N into K numbers, with max number <= M
int dp1[51][51][51];
// split N into multiple distinct numbers, with max number <= M
int dp2[51][51];
// split N into multiple odd numbers, with max number <= M
int dp3[51][51];
// max number <= M 等价于背包问题中使用前M个物品
// 如果使用滚动数组，可以降维
int main() {
	memset(dp1, 0, sizeof(dp1));
	memset(dp2, 0, sizeof(dp2));
	memset(dp3, 0, sizeof(dp3));
	// calc dp1
	// dp[0][0][M] = 1 for any M
	for (int m = 0; m < 51; m++) {
		dp1[0][0][m] = 1;
	}
	// dp[0][K][M] = 0 for K > 0
	// dp[N][0][M] = 0 for N > 0
	// dp[N][K][0] = 0 for N > 0
	for (int N = 0; N < 51; N++) {
		for (int K = 1; K < 51; K++) {
			for (int M = 1; M < 51; M++) {
				if (N >= M)
					dp1[N][K][M] = dp1[N][K][M - 1] + dp1[N - M][K - 1][M];
				else
					dp1[N][K][M] = dp1[N][K][M - 1];
			}
		}
	}

	// calc dp2
	dp2[0][0] = 1;
	//dp2[N][0] = 0 for N > 0
	for (int N = 0; N < 51; N++) {
		for (int M = 1; M < 51; M++) {
			if (N >= M)
				dp2[N][M] = dp2[N][M - 1] + dp2[N - M][M - 1];
			else
				dp2[N][M] = dp2[N][M - 1];
		}
	}
	// calc dp3
	dp3[0][0] = 1;
	for (int N = 0; N < 51; N++) {
		for (int M = 1; M < 51; M+=2) {
			if (M == 1) {
				dp3[N][M] = 1;
			}
			else if (N >= M) {
				dp3[N][M] = dp3[N][M - 2] + dp3[N - M][M];
			}
			else {
				dp3[N][M] = dp3[N][M - 2];
			}
		}
	}
	int N, K;
	while (cin >> N >> K) {
		cout << dp1[N][K][N] << endl;
		cout << dp2[N][N] << endl;
		cout << dp3[N][N - (N % 2 == 0)] << endl;
	}
	return 0;
}