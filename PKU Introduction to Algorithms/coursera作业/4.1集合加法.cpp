/*
http://bailian.openjudge.cn/practice/2792/
*/
#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
	int n; cin >> n;
	while (n--) {
		int s, a, b;
		int ans = 0;
		cin >> s;
		unordered_map<int, int> A;
		cin >> a;
		while (a--) {
			int x; cin >> x; ++A[x];
		}
		cin >> b;
		while (b--) {
			int x; cin >> x;
			ans += A[s - x];
		}
		cout << ans << endl;
	}
	return 0;
}