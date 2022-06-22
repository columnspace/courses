/*
http://noi.openjudge.cn/ch0201/7217/
*/
#include<iostream>
using namespace std;
// closed form solution : f(N) = N ^ N - (N - 1) for N > 2
int main() {
	int N;
	while (cin >> N) {
		if (N == 0) {
			break;
		}
		else if (N == 2) {
			cout << 7 << endl;
		}
		else {
			int ans = 1;
			for (int i = 0; i < N; i++) {
				ans *= N;
			}
			ans -= (N - 1);
			cout << ans << endl;
		}
	}
	return 0;
}