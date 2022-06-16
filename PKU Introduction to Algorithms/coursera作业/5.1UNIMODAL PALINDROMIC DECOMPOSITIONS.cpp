/*
http://bailian.openjudge.cn/practice/1221/
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void calc(vector<vector<long long>>& UPD) {
	int n = UPD.size() - 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (i == j) {
				UPD[i][j] = 1;
			}
			else if(i == 2 * j) {
				UPD[i][j] = 1;
			}
			else if (i > 2 * j) {
				for (int k = j; 2 * j + k <= i; k++) {
					UPD[i][j] += UPD[i - 2 * j][k];
				}
			}
		}
	}
}

int main() {
	vector<int> inputs;
	int n;
	vector<vector<long long>> UPD(250, vector<long long>(250, 0));
	//UPD[N][init] returns the number of feasible solutions with sum of N, and the first/last value of init
	calc(UPD);
	while (cin >> n) {
		if (n > 0) {
			long long ans = 0;
			for (int i = 1; i <= n; i++) {
				ans += UPD[n][i];
			}
			cout << n << " " << ans << endl;
		}
		else {
			break;
		}
	}
	return 0;
}