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
	const int MAXN = 40;
	const int MAXLOG = 6;
#else
	const int MAXN = 8e5 + 2;
	const int MAXLOG = 20;
#endif
#define int ll
int n;
vector<int> g[MAXN];
int tin[MAXN];
int tout[MAXN];
int timer = 0;
int binup[MAXN][MAXLOG];

void dfs(int v, int p = 0) {
	binup[v][0] = p;
	for (int i = 1; i < MAXLOG; i++) {
		binup[v][i] = binup[binup[v][i - 1]][i - 1];
	}
	tin[v] = timer++;
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		dfs(to, v);
	}
	tout[v] = timer++;
}

bool is_parent(int v, int u) {
	return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int lca(int v, int u) {
	if (is_parent(v, u)) {
		return v;
	}
	if (is_parent(u, v)) {
		return u;
	}
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_parent(binup[v][i], u)) {
			v = binup[v][i];
		}
	}
	return binup[v][0];
}

inline void init() {

}

struct event{
	int pos;
	int l, r;
	int add;
	event(){}
	event(int a, int b, int c, int d) {
		pos = a;
		l = b;
		r = c;
		add = d;
	}
};

struct segtree {
	int val = 0;
	int push = 0;
};

segtree t[4 * MAXN];

void push(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].val += t[v].push;
		t[v].push = 0;
		return;
	}
	t[v].val += t[v].push;
	t[2 * v].push += t[v].push;
	t[2 * v + 1].push += t[v].push;
	t[v].push = 0;
}

void upd(int v, int tl, int tr, int l, int r, int x) {
	push(v, tl, tr);
	if (tl > r || l > tr) {
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
	t[v].val = max(t[2 * v].val, t[2 * v + 1].val);
}

vector<event> scan;

void add(int l, int r, int b, int t, int c) {
	scan.emplace_back(l, b, t, c);
	scan.emplace_back(r + 1, b, t, -c);
}

int get() {
	sort(scan.begin(), scan.end(), [](event a, event b){
		return a.pos < b.pos;
	});
	int pnt = 0;
	int ret = 0;
	for (int i = 0; i < MAXN; i++) {
		while (pnt < scan.size() && scan[pnt].pos == i) {
			upd(1, 0, MAXN - 1, scan[pnt].l, scan[pnt].r, scan[pnt].add);
			pnt++;
		}
		ret = max(ret, t[1].val + t[1].push);
	}
	return ret;
}

inline void solve() {
	init();
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}	
	dfs(0);
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b, p;
		cin >> a >> b >> p;
		a--, b--;
		if (is_parent(a, b) || is_parent(b, a)) {
			if (is_parent(b, a)) {
				swap(a, b);
			}
			int c = b;
			for (int i = MAXLOG - 1; i >= 0; i--) {
				if (!is_parent(binup[c][i], a)) {
					c = binup[c][i];
				}
			}
			add(0, tin[c] - 1, tin[b], tout[b], p);
			add(tout[c] + 1, timer - 1, tin[b], tout[b], p);
			add(tin[b], tout[b], 0, tin[c] - 1, p);
			add(tin[b], tout[b], tout[c] + 1, timer - 1, p);
		}
		else {
			add(tin[a], tout[a], tin[b], tout[b], p);
			add(tin[b], tout[b], tin[a], tout[a], p);
		}
	}
	cout << get() << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("8A.in", "r", stdin);
		freopen("8A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}