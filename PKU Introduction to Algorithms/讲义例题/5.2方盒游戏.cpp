/*
http://bailian.openjudge.cn/practice/1390
*/
#include <iostream>
#include <vector>
using namespace std;
struct Block {
	int color, count;
	Block(int col, int cnt) :color(col), count(cnt) {}
};

vector<Block> input(int n) {
	int color = -1, cnt = 0, new_color;
	vector<Block> blocks;
	while (n--) {
		cin >> new_color;
		if (new_color == color) {
			cnt++;
		}
		else {
			blocks.push_back(Block(color, cnt));
			color = new_color;
			cnt = 1;
		}
	}
	blocks.push_back(Block(color, cnt));
	return blocks;
}

int calc_max_score(const vector<Block>& blocks, vector<vector<vector<int>>>& score, int start, int end, int extra_len) {
	if (score[start][end][extra_len] > 0) {
		return score[start][end][extra_len];
	}
	if (start == end) {
		int n = blocks[start].count + extra_len;
		score[start][end][extra_len] = n * n;
		return n * n;
	}
	// option 1: click (blocks[end] + extra_len) directly
	int ans = (blocks[end].count + extra_len) * (blocks[end].count + extra_len) + calc_max_score(blocks, score, start, end - 1, 0);
	// option 2: scan [start, end -1], merge (blocks[end] + extra_len) with possible blocks
	for (int i = start; i <= end - 1; i++) {
		if (blocks[i].color == blocks[end].color) {
			ans = max(ans, calc_max_score(blocks, score, start, i, blocks[end].count + extra_len) + calc_max_score(blocks, score, i + 1, end - 1, 0));
		}
	}
	score[start][end][extra_len] = ans;
	return ans;
}

int main() {
	int t; int n;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cin >> n;
		vector<Block> blocks = input(n);
		vector<vector<vector<int>>> score(blocks.size(), vector<vector<int>>(blocks.size(), vector<int>(n, 0)));
		cout << "Case " << i << ": " << calc_max_score(blocks, score, 0, blocks.size() - 1, 0) << endl;
	}
	return 0;
}