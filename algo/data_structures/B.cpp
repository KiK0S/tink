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
	const int MAXN = 501;
#endif

int n, m;

int g[MAXN][MAXN];

struct segtree_inside {
	int val;
};

struct segtree_outside {
	vector<segtree_inside> t;
	vector<int> a;
};

segtree_outside t[4 * MAXN];

void build_inside(int v, int tl, int tr, segtree_outside &root) {
	if (tl == tr) {
		root.t[v].val = root.a[tl];
		return; 
	}
	int tm = (tl + tr) >> 1;
	build_inside(2 * v, tl, tm, root);
	build_inside(2 * v + 1, tm + 1, tr, root);
	root.t[v].val = min(root.t[2 * v].val, root.t[2 * v + 1].val);
}

void build_outside(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].a.resize(n);
		t[v].t.resize(4 * n);
		for (int i = 0; i < n; i++) {
			t[v].a[i] = g[i][tl];
		}
		build_inside(1, 0, n - 1, t[v]);
		return;
	}
	int tm = (tl + tr) >> 1;
	build_outside(2 * v, tl, tm);
	build_outside(2 * v + 1, tm + 1, tr);
	t[v].a.resize(n);
	t[v].t.resize(4 * n);
	for (int i = 0; i < n; i++) {
		t[v].a[i] = min(t[2 * v].a[i], t[2 * v + 1].a[i]);
	}
	build_inside(1, 0, n - 1, t[v]);
}

int get_inside(int v, int tl, int tr, int l, int r, segtree_outside &root) {
	if (tl > r || l > tr) {
		return INT32_MAX;
	}
	if (l <= tl && tr <= r) {
		return root.t[v].val;
	}
	int tm = (tl + tr) >> 1;
	return min(get_inside(2 * v, tl, tm, l, r, root), get_inside(2 * v + 1, tm + 1, tr, l, r, root));
}

int get_outside(int v, int tl, int tr, int l, int r, int a, int b) {
	if (tl > r || l > tr) {
		return INT32_MAX;
	}
	if (l <= tl && tr <= r) {
		return get_inside(1, 0, n - 1, a, b, t[v]);
	}
	int tm = (tl + tr) >> 1;
	return min(get_outside(2 * v, tl, tm, l, r, a, b), get_outside(2 * v + 1, tm + 1, tr, l, r, a, b));
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> g[i][j];
		}
	}
	build_outside(1, 0, m - 1);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--, b--, c--, d--;
		cout << get_outside(1, 0, m - 1, b, d, a, c) << ' ';
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
	while (cin >> n >> m)
		solve();
	return 0;
}