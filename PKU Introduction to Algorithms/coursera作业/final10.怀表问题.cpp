/*
http://noi.openjudge.cn/ch0407/7222/
*/
#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
using namespace std;
typedef long long ll;
ll ans[14641][2][2];
int lianCnt[4];
int lianCntOrig[4];
int char_to_int(const char& c) {
	return c == 'V' ? 1 : 0;
}
int string_to_int(const string &s) {
	if (s == "LL") {
		return 0;
	}
	else if (s == "LV") {
		return 1;
	}
	else if (s == "VL") {
		return 2;
	}
	else {
		return 3;
	}
}
int state_to_int() {
	int res = 0;
	for (int i = 0; i < 4; i++) {
		res += lianCnt[i];
		if (i < 3) {
			res *= lianCntOrig[i + 1] + 1;
		}
	}
	return res;
}
ll dfs(int length, int start, int end) {//dp中不需要length这一维度，因为length is implied in lianCnt
	int state_code = state_to_int();
	if (ans[state_code][start][end] >= 0) {
		return ans[state_code][start][end];
	}
	if (length == 1) {
		ll res = lianCnt[start * 2 + end] > 0 ? 1 : 0;
		ans[state_code][start][end] = res;
		return res;
	}
	int opt1 = start * 2, opt2 = start * 2 + 1;
	int cnt1 = lianCnt[opt1], cnt2 = lianCnt[opt2];
	ll res1 = 0, res2 = 0;
	if (cnt1 > 0) {
		lianCnt[opt1]--;
		res1 = dfs(length - 1, 0, end);
		lianCnt[opt1]++;
	}
	if (cnt2 > 0) {
		lianCnt[opt2]--;
		res2 = dfs(length - 1, 1, end);
		lianCnt[opt2]++;
	}
	ans[state_code][start][end] = res1 + res2;
	return res1 + res2;
}

int main() {
	int N, K;
	while (cin >> N >> K) {
		memset(ans, -1, sizeof(ans));
		memset(lianCnt, 0, sizeof(lianCnt));
		string pan; 
		cin >> pan;
		for (int i = 0; i < N; i++) {
			string lian; cin >> lian; 
			++lianCnt[string_to_int(lian)];
		}
		memcpy(lianCntOrig, lianCnt, sizeof(lianCnt));
		long long ans = dfs(K, char_to_int(pan[1]), char_to_int(pan[0]));
		if (ans > 0) {
			cout << "YES" << endl;
			cout << ans << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
