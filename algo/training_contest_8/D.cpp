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
#include <numeric>
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
	const int MAXN = 1e5 + 10;
#endif
#define int ll
int n;

ll val[MAXN];
#define plus PLUS
#define minus MINUS
vector<int> plus(MAXN);
vector<int> minus(MAXN);

struct segtree {
	vector<int> all;
	vector<ll> pref;
};

vector<segtree> a(4 * MAXN), b(4 * MAXN);

inline void build(int v, int tl, int tr, vector<segtree> &t, vector<int> &vl) {
	if (tl == tr) {
		t[v].all.clear();
		t[v].pref.clear();
		// assert(vl[tl] >= -5000);
		t[v].all.push_back(vl[tl]);
		t[v].pref.push_back(vl[tl]);
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm, t, vl);
	build(2 * v + 1, tm + 1, tr, t, vl);
	t[v].all.resize(t[2 * v].all.size() + t[2 * v + 1].all.size());
	t[v].pref.resize(t[v].all.size());
	merge(t[2 * v].all.begin(), t[2 * v].all.end(), t[2 * v + 1].all.begin(), t[2 * v + 1].all.end(), t[v].all.begin());
	for (int i = 0; i < t[v].all.size(); i++) {
		t[v].pref[i] = (i == 0 ? 0 : t[v].pref[i - 1]) + t[v].all[i];
	}
	// partial_sum(t[v].all.begin(), t[v].all.end(), t[v].pref.begin());
}

inline ll get(int v, int tl, int tr, vector<segtree> &t, int l, int r, ll x) {
	if (tl > r || l > tr) {
		return 0;
	}
	if (l <= tl && tr <= r) {
		int pos = lower_bound(t[v].all.begin(), t[v].all.end(), x) - t[v].all.begin();
		ll ret = 0;
		if (pos) {
			ret += pos * x - t[v].pref[pos - 1];
		}
		ret += t[v].pref.back() - (pos == 0 ? 0ll : t[v].pref[pos - 1]) - (t[v].all.size() - pos) * x;
		return ret;
	}
	int tm = (tl + tr) >> 1;
	return get(2 * v, tl, tm, t, l, r, x) + get(2 * v + 1, tm + 1, tr, t, l, r, x);
}

ll res = 1e18;

// pair<int, ll> used[MAXN];
// int used[MAXN];

ll check(int pos, int fix) {
	ll rc = val[fix] + abs(pos - fix);
	if (rc - max(pos, n - 1 - pos) <= 0) {
		return 1e18;
	}
	ll prc = rc + pos;
	ll mrc = rc - pos;
	ll ans = get(1, 0, n - 1, a, pos, n - 1, prc) + get(1, 0, n - 1, b, 0, pos - 1, mrc);
	res = min(res, ans);
	// cerr << ans << '\n';
	return ans;
}

inline void init() {
	res = 1e18;
}

inline void solve() {
	init();
	// assert(n < 10000);
	int total = 0;
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		total += val[i];
		plus[i] = val[i] + i;
		minus[i] = val[i] - i;
	}
	int cursum = 0;
	int bestid = -1;
	for (int i = 0; i < n; i++) {
		cursum += val[i];
		if (cursum * 2 <= total) {
			bestid = i;
		}
	}
	build(1, 0, n - 1, a, plus);
	build(1, 0, n - 1, b, minus);
	for (int i = 0; i < n; i++) {
		check(i, i);
		// for (int j = -30; j <= 30; j++) {
		// 	if (bestid + j >= 0 && bestid + j < n) {
		// 		check(bestid + j, i);
		// 		check(i, bestid + j);
		// 	}
		// }
	}
	for (int i = 0; i < n; i++) {
		if (clock() * 1.0 / CLOCKS_PER_SEC >= 1.47) {
			continue;
		}
		int k = 20;
		int l;
		int r;
		int dx = 1;
		for (int j = 0; j <= (n - 1) / k; j++) {
			l = j * k;
			r = min(n - 1, j * k + k - 1);
			int cnt = 0;
			while (l + 1 < r) {
				cnt++;
				if (cnt == 4) {
					break;
				}
				check(l, i);
				check(r, i);
				// cerr << l << ' ' << r << '\n';
				int m1 = (2 * l + r) / 3;
				int m2 = (l + 2 * r) / 3;
				// cerr << m1 << ' ' << m2 << '\n';
				ll _a = 1e18;
				for (int j = -dx; j <= dx; j++) {
					if (m1 + j >= 0 && m1 + j < n) {
						_a = min(_a, check(m1 + j, i));
					}
				}
				ll _b = 1e18;
				for (int j = -dx; j <= dx; j++) {
					if (m2 + j >= 0 && m2 + j < n) {
						_b = min(_b, check(m2 + j, i));
					}
				}
				if (_a < _b) {
					r = m2 - 1;
				}
				else {
					l = m1 + 1;
				}		
			}
		}
		l = i + 1;
		r = n - 1;
		int cnt = 0;
		while (l + 1 < r) {
			cnt++;
			check(l, i);
			check(r, i);
			// cerr << l << ' ' << r << '\n';
			int m1 = (2 * l + r) / 3;
			int m2 = (l + 2 * r) / 3;
			// cerr << m1 << ' ' << m2 << '\n';
			ll _a = 1e18;
			for (int j = -dx; j <= dx; j++) {
				if (m1 + j >= 0 && m1 + j < n) {
					_a = min(_a, check(m1 + j, i));
				}
			}
			ll _b = 1e18;
			for (int j = -dx; j <= dx; j++) {
				if (m2 + j >= 0 && m2 + j < n) {
					_b = min(_b, check(m2 + j, i));
				}
			}
			if (_a < _b) {
				r = m2 - 1;
			}
			else {
				l = m1 + 1;
			}		
		}
		l = 0;
		r = i - 1;
		cnt = 0;
		while (l + 1 < r) {
			cnt++;
			// if (cnt == ) {
			// 	break;
			// }
			check(l, i);
			check(r, i);
			// cerr << l << ' ' << r << '\n';
			int m1 = (2 * l + r) / 3;
			int m2 = (l + 2 * r) / 3;
			// cerr << m1 << ' ' << m2 << '\n';
			ll _a = 1e18;
			for (int j = -dx; j <= dx; j++) {
				if (m1 + j >= 0 && m1 + j < n) {
					_a = min(_a, check(m1 + j, i));
				}
			}
			ll _b = 1e18;
			for (int j = -dx; j <= dx; j++) {
				if (m2 + j >= 0 && m2 + j < n) {
					_b = min(_b, check(m2 + j, i));
				}
			}
			if (_a < _b) {
				r = m2 - 1;
			}
			else {
				l = m1 + 1;
			}
		}
	}
	assert(res >= 0);
	cout << res << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}