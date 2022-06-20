/*
http://bailian.openjudge.cn/practice/1328/
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int main() {
	int nCases = 0;
	while (true) {
		++nCases;
		int n, d; cin >> n >> d;
		if (n == 0 && d == 0) {
			break;
		}
		vector<vector<int>> islands(n, vector<int>(2, 0));
		int maxY = 0;
		for (int i = 0; i < n; i++) {
			cin >> islands[i][0] >> islands[i][1];
			if (abs(islands[i][1]) > maxY) {
				maxY = abs(islands[i][1]);
			}
		}
		if (d < maxY) {
			cout << "Case " << nCases << ": " << -1 << endl;
			continue;
		}
		sort(islands.begin(), islands.end());
		int cnt = 1;
		double minRight = islands[0][0] + sqrt(d * d - islands[0][1] * islands[0][1]);
		for (int i = 1; i < islands.size(); i++) {
			int X = islands[i][0], Y = islands[i][1];
			double left = X - sqrt(d * d - Y * Y), right = X + sqrt(d * d - Y * Y);
			if (left > minRight) { //case 1: no intersection with current range, need to set a rador and update the range
				cnt++;
				minRight = right;
			}
			else { //case 2: intersection with current range
				minRight = min(minRight, right);
			}
		}
		cout << "Case " << nCases << ": " << cnt << endl;
	}
	return 0;
}