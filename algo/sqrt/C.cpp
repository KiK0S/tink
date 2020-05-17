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
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5 + 1;
#endif

int n, m;
string s;
ll hsh[MAXN];
int mod = 1e9 + 7;
ll t = 179;
struct Q {
	int id, k;
	ll h;
};
vector<Q> all[MAXN];
int ans[MAXN];
ll tpow[MAXN];
int need[MAXN];
queue<int> q[MAXN];


inline void init() {
	n = s.size();
	tpow[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		tpow[i] = tpow[i - 1] * t;
		tpow[i] %= mod;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		hsh[i] = (i == 0 ? 0ll : hsh[i - 1]) * t + s[i] - 'a' + 1;
		hsh[i] %= mod;
	}
	for (int i = 0; i < m; i++) {
		ans[i] = 1e9;
		string x;
		int k;
		cin >> k >> x;
		ll h = 0;
		for (auto c : x) {
			h = h * t + c - 'a' + 1;
			h %= mod;
		}
		all[x.size()].push_back({i, k, h});
	}
	for (int len = 1; len <= n; len++) {
		if (all[len].empty()) {
			continue;
		}
		map<ll, int> id;
		for (auto it : all[len]) {
			need[it.id] = it.k;
			id[it.h] = it.id;
		}
		for (int i = len - 1; i < n; i++) {
			ll cur = hsh[i] - ((i == len - 1 ? 0ll : hsh[i - len]) * tpow[len]) % mod + mod;
			cur %= mod;
			if (id.count(cur)) {
				int idx = id[cur];
				q[idx].push(i);
				if (q[idx].size() == need[idx]) {
					ans[idx] = min(ans[idx], i - q[idx].front() + len);
					q[idx].pop();
				}
			}
		}
	}
	for (int i = 0; i < m; i++) {
		if (ans[i] > MAXN + 10) {
			cout << "-1\n";
		}
		else {
			cout << ans[i] << '\n';
		}
	}
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
	while (cin >> s >> m)
		solve();
	return 0;
} 