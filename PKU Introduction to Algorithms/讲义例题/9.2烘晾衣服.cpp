#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool check(int time, const vector<int>& clothes, int k) {
	int time_required = 0;
	for (auto& x : clothes) {
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
	cin >> n;
	vector<int> clothes(n);
	int left = 0, right = 0;
	for (int i = 0; i < n; i++) {
		cin >> clothes[i];
		if (clothes[i] > right) {
			right = clothes[i];
		}
	}
	cin >> k;
	if (k == 1) {
		cout << right << endl;
	}
	else {
		sort(clothes.begin(), clothes.end(), greater<>());
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (check(mid, clothes, k)) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		cout << right + 1 << endl;
	}
	return 0;
}