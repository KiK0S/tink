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
const int MOD = 1e9 + 7;

int n, m;
vector<int> g[MAXN];
int p[MAXN];
int val[MAXN];
int up[MAXN];
int tin[MAXN];
int pos[MAXN];
int sz[MAXN];
int timer = 0;

struct segtree {
	ll val;
	ll push;
	segtree() {
		val = 0;
		push = 0;
	}
	segtree(int x) {
		val = x;
		push = 0;
	}
};

segtree t[4 * MAXN];

void dfs(int v) {
	sz[v] = 1;
	if (g[v].empty()) {
		return;
	}
	int id = 0;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		dfs(to);
		if (sz[to] > sz[g[v][id]]) {
			id = i;
		}
		sz[v] += sz[to];
	}
	swap(g[v][id], g[v][0]);
}

void build(int v) {
	if (up[v] == -1) {
		up[v] = up[p[v]];
	}
	pos[timer] = v;
	tin[v] = timer++;
	bool f = 0;
	for (auto to : g[v]) {
		if (f) {
			up[to] = to;
		}
		build(to);
		f = 1;
	}
}

void push(int v, int tl, int tr) {
	if (tl == tr) {
		if (t[v].push != 0) {
			t[v].val += t[v].push;
			t[v].push = 0;
		}
		return;
	}
	if (t[v].push != 0) {
		t[2 * v].push += t[v].push;
		t[2 * v + 1].push += t[v].push;
		t[v].val += 1ll * t[v].push * (tr - tl + 1);
		t[v].push = 0;
	}
}

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v] = segtree(val[pos[tl]]);
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v].val = t[2 * v].val + t[2 * v + 1].val;
}

void upd(int v, int tl, int tr, int l, int r, ll x) {
	push(v, tl, tr);
	if (l > tr || tl > r) {
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
	t[v].val = t[2 * v].val + t[2 * v + 1].val;
}

ll get(int v, int tl, int tr, int l, int r) {
	push(v, tl, tr);
	if (l > tr || tl > r) {
		return 0;
	}
	if (l <= tl && tr <= r) {
		return t[v].val;
	}
	int tm = (tl + tr) >> 1;
	return get(2 * v, tl, tm, l, r) + get(2 * v + 1, tm + 1, tr, l, r);
}

inline void init() {
	memset(up, -1, sizeof(up));
	memset(p, 0, sizeof(p));
	for (int i = 0; i < MAXN; i++) {
		g[i].clear();
	}
	timer = 0;
}

inline void solve() {
	init();
	for (int i = 1; i < n; i++) {
		cin >> p[i];
		g[p[i]].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	p[0] = 0;
	up[0] = 0;
	dfs(0);
	build(0);
	build(1, 0, n - 1);
	cout << get(1, 0, n - 1, tin[n - 1], tin[n - 1]) << ' ';
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		ll sum = get(1, 0, n - 1, tin[a], tin[a] + sz[a] - 1) - get(1, 0, n - 1, tin[a], tin[a]);
		while (up[a] != 0) {
			sum += get(1, 0, n - 1, tin[up[a]], tin[a]);
			a = p[up[a]];
		}
		sum += get(1, 0, n - 1, 0, tin[a]);
		sum %= MOD;
		upd(1, 0, n - 1, tin[b], tin[b] + sz[b] - 1, sum);
		upd(1, 0, n - 1, tin[b], tin[b], -sum);
		while (up[b] != 0) {
			upd(1, 0, n - 1, tin[up[b]], tin[b], sum);
			b = p[up[b]];
		}
		upd(1, 0, n - 1, 0, tin[b], sum);
		cout << get(1, 0, n - 1, tin[n - 1], tin[n - 1]) << ' ';
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
	while (cin >> n >> m)
		solve();
	return 0;
}