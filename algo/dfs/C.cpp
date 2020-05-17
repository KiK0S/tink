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
	const int MAXN = 10;
#else
	const int MAXN = 1e5 + 100;
#endif

int n, m, f;
const int MAXLOG = 20;
vector<int> g[MAXN];
int tin[MAXN];
int fup[MAXN];
int used[MAXN];
int clr[MAXN];;
int timer = 0;
set<pair<int, int>> bridges;

void dfs(int v, int p = -1) {
	tin[v] = fup[v] = timer++;
	used[v] = 1;
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		if (used[to]) {
			fup[v] = min(fup[v], tin[to]);
		}
		else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > tin[v]) {
				bridges.insert({v, to});
				bridges.insert({to, v});
			}
		}
	}
}

int pnt = 1;

void paint(int v, int color) {
	used[v] = 1;
	clr[v] = color;
	for (auto to : g[v]) {
		if (used[to]) {
			continue;
		}
		if (bridges.count({v, to})) {
			paint(to, pnt++);
		}
		else {
			paint(to, color);
		}
	}
}

int binup[MAXN][MAXLOG];
int tin_lca[MAXN];
int tout_lca[MAXN];
int h[MAXN];
set<int> tree[MAXN];

void calc(int v, int p) {
	binup[v][0] = p;
	h[v] = h[p] + 1;
	for (int i = 1; i < MAXLOG; i++) {
		binup[v][i] = binup[binup[v][i - 1]][i - 1];
	}
	tin_lca[v] = timer++;
	for (auto to : tree[v]) {
		if (to == p) {
			continue;
		}
		calc(to, v);
	}
	tout_lca[v] = timer++;
}

int is_p(int v, int u) {
	return tin_lca[v] <= tin_lca[u] && tout_lca[u] <= tout_lca[v];
}

int lca(int v, int u) {
	if (is_p(v, u)) {
		return v;
	}
	if (is_p(u, v)) {
		return u;
	}
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_p(binup[v][i], u)) {
			v = binup[v][i];
		}
	}
	return binup[v][0];
}


inline void init() {
	timer = 1;
	f--;
	// assert(n < 1000);
}


inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(f);
	memset(used, 0, sizeof(used));
	paint(f, pnt++);
	for (auto it : bridges) {
		tree[clr[it.first]].insert(clr[it.second]);
		tree[clr[it.second]].insert(clr[it.first]);
		// cerr << it.first << ' ' << it.second << '\n';
	}
	// for (int i = 0; i < n; i++) {
	// 	cerr << clr[i] << ' ';
	// }
	// cerr << '\n';
	timer = 1;
	calc(clr[f], clr[f]);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		a = clr[a];
		b = clr[b];
		cout << h[lca(a, b)] - 1 << '\n';	
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
	cin >> n >> m >> f;
	solve();
	return 0;
}