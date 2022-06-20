/*
http://bailian.openjudge.cn/practice/4110/
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<stdio.h>
using namespace std;
struct Item {
	int value, weight;
	double density;
	Item(int v, int w) :value(v), weight(w) { density = 1.0 * value / weight; }
};

int main() {
	int n, maxW; cin >> n >> maxW;
	vector<Item> items;
	for (int i = 0; i < n; i++) {
		int v, w; cin >> v >> w;
		items.push_back(Item(v, w));
	}
	sort(items.begin(), items.end(), [](const Item& x, const Item& y) {return x.density > y.density; });
	int total_weight = 0;
	double total_value = 0;
	for (int i = 0; i < n; i++) {
		if (total_weight + items[i].weight <= maxW) {
			total_weight += items[i].weight;
			total_value += items[i].value;
		}
		else {
			total_value += items[i].density * (maxW - total_weight);
			total_weight = maxW;
			break;
		}
	}
	printf("%.1lf\n", total_value);
	return 0;
}