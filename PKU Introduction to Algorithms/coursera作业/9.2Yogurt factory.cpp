/*
http://bailian.openjudge.cn/practice/2393/
*/
#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
	int nWeeks, storageCost;
	cin >> nWeeks >> storageCost;
	vector<int> produceCost(nWeeks), demand(nWeeks);
	for (int i = 0; i < nWeeks; i++) {
		scanf("%d %d", &produceCost[i], &demand[i]);
	}
	long long ans = 0;
	int bestWeek = 0;
	for (int i = 0; i < nWeeks; i++) {
		int lowestCost = produceCost[i];
		if (produceCost[bestWeek] + storageCost * (i - bestWeek) < lowestCost) {
			lowestCost = produceCost[bestWeek] + storageCost * (i - bestWeek);
		}
		else {
			bestWeek = i;
		}
		ans += lowestCost * demand[i];
	}
	cout << ans;
	return 0;
}