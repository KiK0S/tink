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
#include <ctime>
#include <bitset>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

int m, k;

inline void init() {

}


vector<pair<int, ll>> cnt;
vector<int> divs;

inline void gen(int pos, int cur, vector<pair<int, int>> &all, vector<int> &divs) {
	if (pos == all.size()) {
		divs.push_back(cur);
		return;
	}
	int mn = 1;
	for (int i = 0; i < all[pos].second; i++) {
		mn *= all[pos].first;
	}
	for (int i = all[pos].second; i >= 0; i--) {
		gen(pos + 1, cur * mn, all, divs);
		mn /= all[pos].first;
	}
}


inline ll f(int n) {
	cnt.clear();
	for (auto cur : divs) {
		cnt.push_back({cur, n / cur});
		for (auto kek : cnt) {
			if (kek.first != cur && kek.first % cur == 0) {
				cnt.back().second -= kek.second;
			}
		}
	}
	ll ans = 0;
	for (auto it : cnt) {
		ans += 1ll * it.second * ((1ll * n * it.first) / m);
	}
	return ans;
}

inline void solve() {
	init();
	vector<pair<int, int>> all;
	int q = m;
	for (int i = 2; i * i <= m; i++) {
		if (q % i == 0) {
			all.push_back({i, 0});
		}
		while (q % i == 0) {
			q /= i;
			all.back().second++;
		}
	}
	if (q != 1) {
		all.push_back({q, 1});
	}
	divs.clear();
	gen(0, 1, all, divs);
	int l = 0;
	int r = 1e9 + 1;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (f(mid) < k) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	if (f(r) == k) {
		cout << r << '\n';
	}
	else {
		cout << "-1\n";
	}
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		cin >> m >> k;
		solve();
	}
	return 0;
}