/*
http://noi.openjudge.cn/ch0201/7216/
*/
#include<iostream>
using namespace std;

int f(int N) {
	int minArea = 4 * (N + 1);
	for (int i = 1; i * i * i <= N; i++) {
		if (N % i == 0) {
			for (int j = i; i * j * j <= N; j++) {
				if (N % (i * j) == 0) {
					minArea = min(minArea, 2 * (i * j + N / i + N / j));
				}
			}
		}
	}
	return minArea;
}
int main() {
	int N;
    cin >> N;
    cout << f(N) << endl;
	return 0;
}