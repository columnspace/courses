/*
http://bailian.openjudge.cn/practice/3248/
*/
#include<iostream>
using namespace std;
int gcd(int x, int y) {
	while (x > 0 && y > 0) {
		if (x >= y) {
			x %= y;
		}
		else {
			y %= x;
		}
	}
	if (x == 0) {
		return y;
	}
	else {
		return x;
	}
}

int main() {
	int M, N;
	while (cin >> M >> N) {
		cout << gcd(M, N) << endl;
	}
	return 0;
}