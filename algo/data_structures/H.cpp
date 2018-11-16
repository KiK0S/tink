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
	const int MAXN = 45e4 + 1;
#endif

int n;

struct segtree {
	int l = -1, r = -1;
	int sum = 0;
};


segtree q[10000000];

int roots[MAXN];
int val[MAXN];
int sorted[MAXN];

int uk = 0;
int make() {
	assert(uk < 10000000);
	return uk++;
}

inline int getsum(int v) {
	if (v == -1) return 0;
	return q[v].sum;
}

inline int update(int v, int tl, int tr, int pos) {
	int nw = make();
	q[nw].sum = q[v].sum;
	if (tl == tr) {
		q[nw].sum++;
		return nw;
	}
	if (q[v].l == -1) {
		q[v].l = make();
	}
	if (q[v].r == -1) {
		q[v].r = make();
	}
	q[nw].l = q[v].l;
	q[nw].r = q[v].r;
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		q[nw].l = update(q[v].l, tl, tm, pos);
	}
	else {
		q[nw].r = update(q[v].r, tm + 1, tr, pos);
	}
	q[nw].sum = getsum(q[nw].l) + getsum(q[nw].r);
	return nw;
}

inline int get(int tl, int tr, int l, int r, int k) {
	// cerr << tl << ' ' << tr << '\n';
	if (tl == tr) {
		return sorted[tl];
	}
	int tm = (tl + tr) >> 1;
	int L = 0;
	if (r != -1) {
		L += getsum(q[r].l);
	}
	if (l != -1) {
		L -= getsum(q[l].l);
	}
	// cerr << tl << ' ' << tm << ' ' << tr << " - " << L << '\n';
	if (k <= L) {
		return get(tl, tm, (l == -1 ? -1 : q[l].l), (r == -1 ? -1 : q[r].l), k);
	}
	else {
		return get(tm + 1, tr, (l == -1 ? -1 : q[l].r), (r == -1 ? -1 : q[r].r), k - L);
	}
}

const int MOD = 1e9;

inline void init() {
	roots[0] = make();
	ll l, m;
	cin >> val[1] >> l >> m;
	for (int i = 2; i <= n; i++) {
		val[i] = (val[i - 1] * 1ll * l + m) % MOD;
		// val[i] %= MOD;
	}
	sorted[0] = -1;
	for (int i = 1; i <= n; i++) {
		sorted[i] = val[i];
	}
	sort(sorted, sorted + n + 1);
}

inline void solve() {
	init();
	// for (int i = 1; i <= n; i++) {
	// 	cerr << sorted[i] << ' ';
	// }
	// cerr << '\n';
	for (int i = 1; i <= n; i++) {
		roots[i] = update(roots[i - 1], 0, MAXN, lower_bound(sorted + 1, sorted + n + 1, val[i]) - sorted);
	}
	int m;
	cin >> m;
	ll ans = 0;
	for (int i = 0; i < m; i++) {
		int G;
		cin >> G;
		ll x1, lx, mx, y1, ly, my, k1, lk, mk;
		cin >> x1 >> lx >> mx >> y1 >> ly >> my >> k1 >> lk >> mk;
		ll x = x1;
		ll y = y1;
		ll k = k1;
		for (int j = 1; j <= G; j++) {
			ll L = min(x, y);
			ll R = max(x, y);
			ll ret = get(0, MAXN, roots[L - 1], roots[R], k);
			// cerr << "! " << L << ' ' << R << ' ' << k << " - " << ret << '\n';
			x = ((L - 1) * lx + mx) % n + 1;
			y = ((R - 1) * ly + my) % n + 1;
			k = ((k - 1) * lk + mk) % (max(x, y) - min(x, y) + 1) + 1;
			ans += ret;
		}
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("H.in", "r", stdin);
		freopen("H.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}