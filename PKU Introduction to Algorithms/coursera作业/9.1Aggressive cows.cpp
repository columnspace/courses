/*
http://bailian.openjudge.cn/practice/2456/
*/
#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
bool check(const vector<int>& stalls, int dist, int nCows) {
	int cnt = 1, prev = stalls[0];
	for (int i = 1; i < stalls.size(); i++) {
		if (stalls[i] - prev >= dist) {
			cnt++; prev = stalls[i];
			if (cnt >= nCows) {
			    return true;
			}
		}
	}
	return false;
}

int main() {
	int nStalls, nCows; cin >> nStalls >> nCows;
	vector<int> stalls(nStalls);
	for (int i = 0; i < nStalls; i++) {
	    scanf("%d",&stalls[i]);
	}
	sort(stalls.begin(), stalls.end());
	int left = 1, right = (stalls.back() - stalls.front()) / (nCows - 1);
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (check(stalls, mid, nCows)) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	cout << left - 1;
	return 0;
}