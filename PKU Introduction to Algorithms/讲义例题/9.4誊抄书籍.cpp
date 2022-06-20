/*
http://bailian.openjudge.cn/practice/1505/
*/
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
bool check(const vector<int>& books, ll pages_per_person, int num_person_available) {
	int num_persons_required = 0;
	ll pages_current_person = 0;
	for (int i = 0; i < books.size(); i++) {
		if (pages_current_person == 0) {
			++num_persons_required; pages_current_person = books[i];
		}
		else if (pages_current_person <= pages_per_person - books[i]) {
			pages_current_person += books[i];
		}
		else {
			++num_persons_required; pages_current_person = books[i];
		}
	}
	return num_persons_required <= num_person_available;
}

void print(vector<int>& books, int i, ll pages_per_person, int scriber, ll now) {
	bool sepa = false;
	if (i < 0) return;
	//若当前书不能放入当前堆, 则说明要加入分隔符
	if (i == scriber - 1 || now + books[i] > pages_per_person) {
		print(books, i - 1, pages_per_person, scriber - 1, books[i]);
		sepa = true;
	}
	else {
		print(books, i - 1, pages_per_person, scriber, now + books[i]);
	}
	//输出当前书的页数和分隔符
	if (i > 0) {
		printf(" %d", books[i]);
	}
	else {
		printf("%d", books[i]);
	}
	if (sepa) {
		printf(" /");
	}
}

int main() {
	int nCases; cin >> nCases;
	while (nCases--) {
		int m, k; cin >> m >> k;
		vector<int> books(m);
		ll max_pages = 0;
		ll total_pages = 0;
		for (int i = 0; i < m; i++) {
			cin >> books[i];
			if (books[i] > max_pages) {
				max_pages = books[i];
			}
			total_pages += books[i];
		}
		ll pages_per_person = total_pages;
		for (ll left = max_pages, right = total_pages; left <= right; ) {
			ll mid = left + (right - left) / 2;
			if (check(books, mid, k)) {
				pages_per_person = mid;
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		print(books, m - 1, pages_per_person, k - 1, 0);
		cout << endl;
	}
	return 0;
}