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
	const int MAXN = 2e5;
#endif

#define int ll

int n, k;
int val[MAXN];
int dp[MAXN][2];

struct segtree {
	int val;
	int push;
	segtree() {
		val = 1e18;
		push = 0;
	}
};

segtree t[4 * MAXN];

void push(int v, int tl, int tr) {
	if (t[v].push != 0) {
		if (tl != tr) {
			t[2 * v].push += t[v].push;
			t[2 * v + 1].push += t[v].push;
		}
		t[v].val += t[v].push;
		t[v].push = 0;
	}
}

void upd(int v, int tl, int tr, int l, int r, int x) {
	push(v, tl, tr);
	if (tl > r || l > tr || l > r) {
		return;
	}
	if (l <= tl && tr <= r) {
		t[v].push += x;
		push(v, tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	upd(2 * v, tl, tm, l, r, x);
	upd(2 * v + 1, tm + 1, tr, l, r, x);
	t[v].val = min(t[2 * v].val, t[2 * v + 1].val);
}

void upds(int v, int tl, int tr, int id, int x) {
	push(v, tl, tr);
	if (tl == tr) {
		t[v].val = x;
		push(v, tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	if (tm >= id) {
		upds(2 * v, tl, tm, id, x);
	}
	else {
		upds(2 * v + 1, tm + 1, tr, id, x);
	}
	t[v].val = min(t[2 * v].val, t[2 * v + 1].val);
}

int get(int v, int tl, int tr, int l, int r) {
	push(v, tl, tr);
	if (tl > r || l > tr) {
		return 1e18;
	}
	if (l <= tl && tr <= r) {
		return t[v].val;
	}
	int tm = (tl + tr) >> 1;
	return min(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dp[i][0] = dp[i][1] = 1e18;
	}
}

inline void solve() {
	init();
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
	}
	dp[0][0] = dp[0][1] = 0;
	upd(1, 0, MAXN - 1, 0, 0, -1e18);
	for (int i = 1; i <= n; i++) {
		dp[i][1] = get(1, 0, MAXN - 1, 0, i - 1) + val[i];
		upds(1, 0, MAXN - 1, i, dp[i][1]);
		// cerr << "! " << dp[i][1] << '\n';
		// cerr << max(1ll, i - k) << ' ' << i - 1 << '\n';
		upd(1, 0, MAXN - 1, max(1ll, i - k), i - 1, val[i] / 2);
		// cerr << 0 << ' ' << max(0ll, i - k - 1) << '\n';
		upd(1, 0, MAXN - 1, 0, max(0ll, i - k - 1), val[i]);
		// cerr << '\t';
		// for (int j = 0; j < i; j++) {
		// 	cerr << get(1, 0, MAXN - 1, j, j) << ' ';
		// }
		// cerr << '\n';
		
	}
	// cerr << '\n';
	cout << get(1, 0, MAXN - 1, 0, n) << '\n';
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
	while (cin >> n >> k)
		solve();
	return 0;
}