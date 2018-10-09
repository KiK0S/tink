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
	const int MAXW = 10;
	const int MAXLOG = 5;
#else
	const int MAXN = 3e5 + 100;
	const int MAXW = 1 << 10;
	const int MAXLOG = 21;
#endif

int pre[MAXN][MAXLOG];
int parent[MAXN];
int up[MAXN];
vector<int> g[MAXN];
bitset<MAXW> neutral;
int pos[MAXN];
int tin[MAXN];
int tout[MAXN];
int sz[MAXN];
int val[MAXN];
int vert[5];
bitset<MAXW> precalc[MAXN];
bitset<MAXW> got[5];
bitset<MAXW> cur;
int n, m, q, timer = 0;

struct segtree {
	bitset<MAXW> val;
};

segtree t[4 * MAXN];

void dfs(int v, int p) {
	sz[v] = 1;
	if (p == -1) {
		pre[v][0] = 0;
	}
	else {
		pre[v][0] = p;
	}
	for (int i = 1; i < MAXLOG; i++) {
		pre[v][i] = pre[pre[v][i - 1]][i - 1];
	}
	if (g[v].size() == 0) {
		return;
	}
	int id = 0;
	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		dfs(to, v);
		sz[v] += sz[to];
		if (sz[to] > sz[g[v][id]]) {
			id = i;
		}
	}
	swap(g[v][id], g[v][0]);
}

void build(int v, int p) {
	if (up[v] == -1) {
		up[v] = up[p];
	}
	pos[timer] = v;
	tin[v] = timer++;
	bool f = 0;
	for (auto to : g[v]) {
		if (f) {
			up[to] = to;
		}
		build(to, v);
		f = 1;
	}
	tout[v] = tin[v] + sz[v] - 1;
}

bool is_parent(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int v, int u) {
	if (is_parent(v, u)) {
		return v;
	}
	if (is_parent(u, v)) {
		return u;
	}
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_parent(pre[v][i], u)) {
			v = pre[v][i];
		}
	}
	return pre[v][0];
}

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].val[val[pos[tl]]] = 1;
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v].val = t[2 * v].val | t[2 * v + 1].val;
}

bitset<MAXW> get(int v, int tl, int tr, int l, int r) {
	if (l > tr || tl > r) {
		return neutral;
	}
	if (l <= tl && tr <= r) {
		return t[v].val;
	}
	int tm = (tl + tr) >> 1;
	return get(2 * v, tl, tm, l, r) | get(2 * v + 1, tm + 1, tr, l, r);
}

inline void init() {
	memset(up, -1, sizeof(up));
}

inline void solve() {
	init();
	for (int i = 1; i < n; i++) {
		cin >> parent[i];
		parent[i]--;
		g[parent[i]].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		val[i]--;
	}
	up[0] = 0;
	dfs(0, -1);
	build(0, -1);
	build(1, 0, n - 1);
	for (int i = 0; i < n; i++) {
		if (up[pos[i]] == pos[i]) {
			precalc[pos[i]] = neutral;
		}
		else {
			precalc[pos[i]] = precalc[pos[i - 1]];
		}
		precalc[pos[i]][val[pos[i]]] = 1;
	}
	int last = 0;
	for (int i = 0; i < q; i++) {
		int c;
		cin >> c;
		for (int j = 0; j < c; j++) {
			cin >> vert[j];
			vert[j] += last - 1;
			vert[j] %= n;
			got[j].reset();
		}
		int root = vert[0];
		for (int j = 1; j < c; j++) {
			root = lca(root, vert[j]);
		}
		for (int j = 0; j < c; j++) {
			while (up[vert[j]] != up[root]) {
				got[j] |= precalc[vert[j]];
				vert[j] = parent[up[vert[j]]];
			}
			got[j] |= get(1, 0, n - 1, tin[root], tin[vert[j]]);
		}
		int ans = 1e9;
		for (int mask = 1; mask < (1 << c); mask++) {
			cur.reset();
			for (int j = 0; j < c; j++) {
				if (mask & (1 << j)) {
					cur |= got[j];
				}
			}
			ans = min(ans, (int)cur.count() / __builtin_popcount(mask));
		}
		cout << ans * c << '\n';
		last = ans * c;
	}
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
	while (cin >> n >> m >> q)
		solve();
	return 0;
}