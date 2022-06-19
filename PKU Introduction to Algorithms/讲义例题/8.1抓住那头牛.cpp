/*
http://bailian.openjudge.cn/practice/4001/
*/
#include<iostream>
#include<queue>
#include<unordered_map>
using namespace std;

int main() {
	int N, K; cin >> N >> K;
	queue<int> q;
	unordered_map<int, int> time;
	q.push(N);
	time[N] = 0;
	while (!q.empty()) {
		int n = q.front();
		if (n == K) {
			cout << time[n] << endl;
			break;
		}
		if (n + 1 <= 100000 && time.find(n + 1) == time.end()) {
			time[n + 1] = time[n] + 1;
			q.push(n + 1);
		}
		if (n > 0 && time.find(n - 1) == time.end()) {
			time[n - 1] = time[n] + 1;
			q.push(n - 1);
		}
		if (2 * n <= 100000 && time.find(2 * n) == time.end()) {
			time[2 * n] = time[n] + 1;
			q.push(2 * n);
		}
		q.pop();
	}
	return 0;
}