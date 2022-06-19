/*
http://bailian.openjudge.cn/practice/2373
*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int INF = 1 << 30;
struct Pair {
	int x, f;
	Pair(int x, int f):x(x),f(f){}
	bool operator <(const Pair& a) const { return f > a.f; };
};

int main() {
	int N, L, A, B;
	cin >> N >> L >> A >> B;
	vector<int> has_cow(L + 1, 0);
	// 标记每只奶牛范围的开始与结束点
	for (int i = 0; i < N; i++) {
		int S, E; cin >> S >> E;
		has_cow[S + 1]++;
		has_cow[E]--;
	}
	// cumsum计算每个点的奶牛数量，若大于0则表明此处有奶牛
	int ncow = 0;
	for (int i = 0; i <= L; i++) {
		ncow += has_cow[i];
		has_cow[i] = ncow > 0 ? 1 : 0;
	}
	// ans[x]记录当恰好覆盖[0, x]范围时，最少需要多少水龙头
	/*
	ans[X] =
	1. INF，若X为奇数
	2. INF，若X<2A
	3. INF, 若has_cow[X] == 1
	4. 1, 若2A<=X<=2B 且 has_cow[X] == 0
	5. 1 + min([ans[Y] for X-2B<=Y<=X-2A])，若X>2*B且X为偶数且has_cos[X] == 0
	*/
	vector<int> ans(L + 1, INF);
	priority_queue<Pair> q; //这里使用priority queue来加快寻找rolling window的最小值，不优化（用线性搜索）也能过。POJ：线性488ms，pq29ms
	for (int i = 2 * A; i <= 2 * B; i += 2) {
		if (has_cow[i] == 0) {
			ans[i] = 1;
		}
		if (ans[i - 2 * A + 2] < INF) {
			q.push(Pair(i - 2 * A + 2, ans[i - 2 * A + 2]));
		}
	}
	for (int i = 2 * B + 2; i <= L; i += 2) {
		if (has_cow[i] == 0) {
			while (!q.empty()) {
				if (q.top().x < i - 2 * B) {
					q.pop();
				}
				else {
					break;
				}
			}
			if (!q.empty()) {
				ans[i] = 1 + q.top().f;
			}
		}
		if (ans[i - 2 * A + 2] < INF) {
			q.push(Pair(i - 2 * A + 2, ans[i - 2 * A + 2]));
		}
	}
	if (ans[L] < INF) {
		cout << ans[L] << endl;
	}
	else {
		cout << -1 << endl;
	}
	return 0;
}