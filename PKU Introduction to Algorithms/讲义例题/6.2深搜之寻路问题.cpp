/*
http://bailian.openjudge.cn/practice/1724/
*/
#include<iostream>
#include<vector>
using namespace std;
struct Road {
	int dest, len, toll;
	Road(int dest, int len, int toll) : dest(dest), len(len), toll(toll) {}
};

int K, N, R;
vector<vector<Road>> roads;
vector<int> visited;
vector<vector<int>> shortest;//returns min len
int total_len = 0, total_toll = 0, shortest_len = 1 << 30;

void dfs(int n) {
	if (visited[n] > 0) {
		return;
	}
	if (total_toll > K || total_len >= shortest_len) {
		return;
	}
	if (n == N) {
		shortest_len = total_len;
		return;
	}
	if (shortest[n][total_toll] == -1 || total_len < shortest[n][total_toll]) {
		shortest[n][total_toll] = total_len;
	}
	else {
		return;
	}
	visited[n] = 1;
	for (int i = 0; i < roads[n].size(); i++) {
		Road r = roads[n][i];
		total_toll += r.toll; total_len += r.len;
		dfs(r.dest);
		total_toll -= r.toll; total_len -= r.len;
	}
	visited[n] = 0;
}

int main() {
	cin >> K >> N >> R;
	roads = vector<vector<Road>>(N + 1);
	int src, dest, len, toll;
	for (int i = 0; i < R; i++) {
		cin >> src >> dest >> len >> toll;
		roads[src].push_back(Road(dest, len, toll));
	}
	visited = vector<int> (N + 1, 0);
	shortest = vector<vector<int>> (N + 1, vector<int>(K + 1, -1));
	dfs(1);
	if (shortest_len < (1 << 30)) {
		cout << shortest_len << endl;
	}
	else {
		cout << -1 << endl;
	}
	return 0;
}