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
	const int MAXN = 3e5;
#else
	const int MAXN = 3e5;
#endif

int n;

vector<int> g[MAXN];
ll dp[MAXN];
int sz[MAXN];


struct segtree {
	ll sum = 0;
	segtree *l = nullptr;
	segtree *r = nullptr;
};

segtree * t[MAXN];

ll getsum(segtree * v) {
	return v == nullptr ? 0 : v->sum;
}

void add(segtree *v, int tl, int tr, int pos) {
	if (tl == tr) {
		v->sum++;
		return;
	}
	int tm = (tl + tr) / 2;
	if (pos <= tm) {
		if (v->l == nullptr) {
			v->l = new segtree();
		}
		add(v->l, tl, tm, pos);
	}
	else {
		if (v->r == nullptr) {
			v->r = new segtree();
		}
		add(v->r, tm + 1, tr, pos);
	}
	v->sum = getsum(v->l) + getsum(v->r);
}

ll get(segtree *v, int tl, int tr, int l, int r) {
	if (v == nullptr) {
		return 0;
	}
	if (tl > r || l > tr) {
		return 0;
	}
	if (l <= tl && tr <= r) {
		return getsum(v);
	}
	int tm = (tl + tr) >> 1;
	return get(v->l, tl, tm, l, r) + get(v->r, tm + 1, tr, l, r);
}

void rec(int v, int par, bool ok) {
	// cerr << v << ' ' << par << '\t' << ok << '\n';
	if (ok) {
		dp[par] += get(t[par], 0, n - 1, v, n - 1);
	}
	else {
		dp[par] += get(t[par], 0, n - 1, 0, v);
	}
	// cerr << dp[par] << '\n';
	for (auto to : g[v]) {
		rec(to, par, ok);
	}
}

void rec1(int v, int par) {
	add(t[par], 0, n - 1, v);
	for (auto to : g[v]) {
		rec1(to, par);
	}
}

void del(segtree *v) {
	if (v == nullptr) {
		return;
	}
	del(v->l);
	del(v->r);
	delete v;
}

void print(segtree *v, int tl = 0, int tr = n - 1) {
	if (v == nullptr) {
		return;
	}
	cerr << tl << ' ' << tr << '\t' << getsum(v) << '\n';
	int tm = (tl + tr) >> 1;
	print(v->l, tl, tm);
	print(v->r, tm + 1, tr);
}

void dfs(int v, int p = -1) {
	sz[v] = 1;
	int mx = -1;
	for (auto to : g[v]) {
		dfs(to, v);
		sz[v] += sz[to];
		if (mx == -1 || sz[to] > sz[mx]) {
			mx = to;
		}
	}
	if (mx != -1) {
		swap(t[v], t[mx]);
	}
	// cerr << v << ' ' << dp[v] << '\n';
	// print(t[v]);
	// cerr << '\n';
	int id = -1;
	for (int i = 0; i < g[v].size(); i++) {
		if (g[v][i] == mx) {
			id = i;
			break;
		}
	}
	for (auto to : g[v]) {
		del(t[to]);
		dp[v] += dp[to];
	}
	for (int i = id - 1; i >= 0; i--) {
		auto to = g[v][i];
		rec(to, v, 0);
		rec1(to, v);
	}
	// if (id < 0) {
	// 	return;
	// }
	for (int i = id + 1; i < g[v].size(); i++) {
		auto to = g[v][i];
		rec(to, v, 1);
		rec1(to, v);
	}
	dp[v] += get(t[v], 0, n - 1, 0, v);
	add(t[v], 0, n - 1, v);
}


inline void init() {
	memset(dp, 0, sizeof(dp));
	memset(sz, 0, sizeof(sz));
	for (int i = 0; i < MAXN; i++) {
		t[i] = new segtree();
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int a;
			cin >> a;
			a--;
			g[i].push_back(a);
		}
	}
	dfs(0);
	for (int i = 0; i < n; i++) {
		cout << dp[i] << ' ';
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}