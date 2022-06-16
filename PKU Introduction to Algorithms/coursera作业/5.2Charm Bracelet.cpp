/*
http://bailian.openjudge.cn/practice/4131/
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	int N, M;
	cin >> N >> M;
	vector<int> weight(N + 1), score(N + 1);
	for (int i = 1; i <= N; i++) {
		cin >> weight[i] >> score[i];
	}
	// 背包问题：使用维度为num_items x weight_capacity的数组进行递归，但是这种方法使用内存过多
	// 优化方法：使用一维数组即可，因为在num_item这个维度上只会往前看一步
	// 但是注意在weight这个维度上必须从大到小遍历，否则会出错
	/*
	* 原代码：memory limit exceeded
	vector<vector<int>> max_score(N + 1, vector<int>(M + 1, 0));
	// max_score[n][w] returns the max score with the first n items, total weight capacity w
	for (int n = 1; n <= N; n++) {
		for (int w = 1; w <= M; w++) {
			if (w < weight[n]) {
				max_score[n][w] = max_score[n - 1][w];
			}
			else {
				max_score[n][w] = max(max_score[n - 1][w], score[n] + max_score[n - 1][w - weight[n]]);
			}
		}
	}
	cout << max_score[N][M] << endl;
	*/
	vector<int> max_score(M + 1, 0);
	for (int n = 1; n <= N; n++) {
		for (int w = M; w >= 1; w--) {
			if (w >= weight[n]) {
				max_score[w] = max(max_score[w], score[n] + max_score[w - weight[n]]);
			}
		}
	}
	cout << max_score[M] << endl;
	return 0;
}
