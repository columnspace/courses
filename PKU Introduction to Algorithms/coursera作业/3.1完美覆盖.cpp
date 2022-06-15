/*
http://bailian.openjudge.cn/practice/2663/
*/
#include <iostream>
using namespace std;
/*
	f(n) is the number of possible solutions for 3*n board
	 _ _
	|_|_|
	|_|_|
	|_|_|

	f(0) = 1, f(2) = 3

	g(n) is the number of possible solutions for 3*n board - 2 extra grid (consecutive in the same column), as shown
	 _
	|_|
	|_|_
	|_|_|

	g(2) = 1. Let g(0) = 0.

	f(n+2) = 3*f(n) + 2*g(n), n>=2
	g(n+2) = f(n) + g(n), n >= 2

*/
int main() {
	int n;
	while (true) {
		cin >> n;
		if (n == -1) {
			break;
		}
		if (n % 2 == 1) {
			cout << 0 << endl;
			continue;
		}
		int f = 1, g = 0;
		for (int i = 2; i <= n; i += 2) {
			int tmp = f;
			f = 3 * f + 2 * g;
			g = tmp + g;
		}
		cout << f << endl;
	}
	return 0;
}