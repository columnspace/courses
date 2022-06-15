/*
http://bailian.openjudge.cn/practice/2811/
*/
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> add_border(const vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> res(m + 1, vector<int>(n + 2, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            res[i][j] = mat[i - 1][j - 1];
        }
    }
    return res;
}

vector<vector<int>> remove_border(const vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> res(m - 1, vector<int>(n - 2, 0));
    for (int i = 1; i <= m - 1; i++) {
        for (int j = 1; j <= n - 2; j++) {
            res[i - 1][j - 1] = mat[i][j];
        }
    }
    return res;
}

vector<vector<int>> turn_off_lights(vector<vector<int>> lights) {
    int m = lights.size(), n = lights[0].size();
    lights = add_border(lights);
    vector<vector<int>> switches(m + 1, vector<int>(n + 2, 0));
    switches[1][1] = -1;
    for (int k = 0; k < (1 << n); k++) {
        // enumerate the first row
        switches[1][1]++;
        int l = 1;
        while (switches[1][l] > 1) {
            switches[1][l + 1]++;
            switches[1][l] %= 2;
            l++;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j <= n; j++) {
                switches[i + 1][j] = (lights[i][j] + switches[i - 1][j] + switches[i][j - 1] + switches[i][j] + switches[i][j + 1]) % 2;
            }
        }
        bool is_solution = true;
        for (int j = 1; j <= n; j++) {
            if ((lights[m][j] + switches[m - 1][j] + switches[m][j - 1] + switches[m][j] + switches[m][j + 1]) % 2 == 1) {
                is_solution = false;
                break;
            }
        }
        if (is_solution) {
            return remove_border(switches);
        }
    }
    return { {} };
}


int main() {
    vector<vector<int>> lights(5, vector<int>(6, 0));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> lights[i][j];
        }
    }
    vector<vector<int>> ans = turn_off_lights(lights);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}