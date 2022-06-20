/*
http://bailian.openjudge.cn/practice/1753/
*/
#include<iostream>
#include<queue>
#include<unordered_map>
using namespace std;

int flip(int num, int pos) {
	num ^= (1 << pos);
	if (pos > 3) {
		num ^= (1 << (pos - 4));
	}
	if (pos < 12) {
		num ^= (1 << (pos + 4));
	}
	if (pos % 4 > 0) {
		num ^= (1 << (pos - 1));
	}
	if (pos % 4 < 3) {
		num ^= (1 << (pos + 1));
	}
	return num;
}

int main() {
	char c;
	int N = 0;
	for (int i = 0; i < 16; i++) {
		cin >> c;
		N = (N << 1) + (c == 'w');
	}
	queue<int> q;
	unordered_map<int, int> steps;
	q.push(N); steps[N] = 0;
	while (!q.empty()) {
		int x = q.front();
		int s = steps[x];
		if (x == 0 || x == 0xffff) {
			cout << s << endl;
			return 0;
		}
		for (int i = 0; i < 16; i++) {
			int y = flip(x, i);
			if (steps.find(y) == steps.end()) {
				steps[y] = s + 1;
				q.push(y);
			}
		}
		q.pop();
	}
	cout << "Impossible" << endl;
	return 0;
}