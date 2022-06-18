/*
http://bailian.openjudge.cn/practice/1190/
*/
#include<iostream>
#include<vector>
#include <cmath>
using namespace std;
int N, M;
int minArea;

int maxVforNRH(int n, int r, int h) {
	int V = 0;
	for (int i = 0; i < n; i++) {
		V += (r - i) * (r - i) * (h - i);
	}
	return V;
}

void dfs(int V, int n, int maxH, int maxR, int area) {
	if (area >= minArea) {
		return;//剪枝
	}
	if (n == 0) {
		if (V == 0) {
			minArea = area;
		}
		return;
	}
	if (V < (n * (n + 1) / 2) * (n * (n + 1) / 2) || maxH < n || maxR < n) {
		return;//剪枝
	}
	if (area + n * (n + 1) * (2 * n + 1) / 3 >= minArea) {
		return;//剪枝
	}
	if (V > maxVforNRH(n, maxR, maxH)) {
		return;//剪枝
	}
	for (int h = n; h <= maxH; h++) {
		for (int r = n; r <= maxR && h * r * r <= V; r++) {
			dfs(V - h * r * r, n - 1, h - 1, r - 1, area > 0 ? area + 2 * r * h : r * (r + 2 * h));
		}
	}
	return;
}

int main() {
	cin >> N >> M;
	minArea = 1 << 30;
	int maxV = N - (M * (M - 1) / 2) * (M * (M - 1) / 2);
	int maxH = maxV / (M * M);
	int maxR = sqrt(maxV / M);
	dfs(N, M, maxH, maxR, 0);
	if (minArea < 1<<30) {
		cout << minArea << endl;
	}
	else {
		cout << 0 << endl;
	}
	return 0;
}