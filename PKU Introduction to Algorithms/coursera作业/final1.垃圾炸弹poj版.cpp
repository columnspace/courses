/*
http://bailian.openjudge.cn/practice/4133/
*/
#include<iostream>
#include<cstring>
using namespace std;

int grid[1025][1025];

int main() {
    int d, n; cin >> d >> n;
    memset(grid, 0, sizeof(grid));
    for (int i = 0; i < n; i++) {
        int x, y, v; cin >> x >> y >> v;
        for (int r = max(x - d, 0); r <= x + d && r <= 1024; r++) {
            for (int c = max(y - d, 0); c <= y + d && c <= 1024; c++) {
                grid[r][c]+=v;
            }
        }
    }
    int maxValue = 0;
    int numMaxPoints = 0;
    for (int i = 0; i <= 1024; i++) {
        for (int j = 0; j <= 1024; j++) {
            if (grid[i][j] > maxValue) {
                maxValue = grid[i][j];
                numMaxPoints = 1;
            }
            else if (grid[i][j] == maxValue) {
                ++numMaxPoints;
            }
        }
    }
    cout << numMaxPoints << " " << maxValue << endl;
	return 0;
}