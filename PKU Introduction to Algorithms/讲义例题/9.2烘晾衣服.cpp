/*
http://poj.org/problem?id=3104
*/
#include<functional>
#include<vector>
#include<stdio.h>
#include<algorithm>
using namespace std;
bool check(int time, const vector<int>& clothes, int k) {
	int time_required = 0;
	for (int i = 0; i < clothes.size(); i++) {
		int x = clothes[i];
		if (x <= time) {
			break;
		}
		else {
			time_required += (x - time) / (k - 1) + ((x - time) % (k - 1) > 0);
			if (time_required > time) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	int n, k;
	scanf("%d", &n);
	vector<int> clothes(n);
	int left = 0, right = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &clothes[i]);
		if (clothes[i] > right) {
			right = clothes[i];
		}
	}
	scanf("%d", &k);
	if (k == 1) {
		printf("%d\n", right);
	}
	else {
		sort(clothes.begin(), clothes.end(), greater<int>());
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (check(mid, clothes, k)) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		printf("%d\n", right + 1);
	}
	return 0;
}