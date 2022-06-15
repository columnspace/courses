/*
http://bailian.openjudge.cn/practice/2760/
*/
#include <iostream>
#include <vector>
using namespace std;
void input(vector<vector<int>>& triangle) {
	for (int i = 0; i < triangle.size(); i++) {
		for (int j = 0; j <= i; j++) {
			cin >> triangle[i][j];
		}
	}
}

void calculate(vector<vector<int>>& triangle) {
	for (int i = triangle.size() - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
		}
	}
}

int main() {
	int N; cin >> N;
	vector<vector<int>> triangle(N, vector<int>(N, 0));
	input(triangle);
	calculate(triangle);
	cout << triangle[0][0] << endl;
}