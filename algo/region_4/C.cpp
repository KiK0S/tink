#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif
#define int ll
int n;
string s;

inline void init() {

}

inline void solve() {
	init();
	vector<int> all;
	int minlen = 1e9;
	cin >> s;
	int cur = 0;
	s.push_back('.');
	for (auto c : s) {
		if (c == '.') {
			if (cur) {
				all.push_back(cur);
				minlen = min(minlen, cur);
			}
			cur = 0;
		}
		else {
			cur++;
		}
	}
	if (all.empty()) {
		for (int i = 0; i < n; i++) {
			cout << "-1 ";
		}
		cout << '\n';
		return;
	}
	vector<int> ans(n + 1, -1);
	set<int> st;
	for (int i = 1; i <= n; i++) {
		st.insert(i);
	}
	st.insert(1e18);
	for (int h = 1; h <= minlen; h++) {
		int min_add = 0;
		int max_add = 0;
		for (auto x : all) {
			min_add += (x + h - 1) / h;
			max_add += (x - h + 1);
		}
		auto it = st.lower_bound(min_add);
		vector<int> rm;
		while (*it <= max_add) {
			ans[*it] = h - 1;
			rm.push_back(*it);
			it++;
		}
		for (auto it : rm) {
			st.erase(it);
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}