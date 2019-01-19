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
	const int MAXN = 20;
#else
	const int MAXN = 4e5;
#endif

int n, m, L, R;
vector<int> g[MAXN];
vector<int> gr[MAXN];
int x[MAXN];
int y[MAXN];
int start[MAXN];
int fin[MAXN];
int used[MAXN];
vector<int> topsort;
int color[MAXN];
vector<int> G[MAXN];
int l[MAXN];
vector<int> coord;
int r[MAXN];

void get_topsort(int v) {
	used[v] = 1;
	for (auto to : g[v]) {
		if (!used[to]) {
			get_topsort(to);
		}
	}
	topsort.push_back(v);
}

void paint(int v, int c) {
	color[v] = c;
	if (fin[v] == 1) {
		coord.push_back(y[v]);
		r[color[v]] = max(r[color[v]], y[v]);
		l[color[v]] = min(l[color[v]], y[v]);
	}
	for (auto to : gr[v]) {
		if (color[to] == -1) {
			paint(to, c);
		}
	}
}

void tp(int v) {
	used[v] = 1;
	for (auto to : G[v]) {
		if (used[to]) {
			continue;
		}
		tp(to);
	}
	topsort.push_back(v);
}


inline void init() {
	topsort.clear();
	coord.clear();
	memset(color, -1, sizeof(color));
	for (int i = 0; i < MAXN; i++) {
		l[i] = 1e9 + 100;
		r[i] = -1;
	}
}

int get(int a, int b) {
	if (a > b) {
		return 0;
	}
	return upper_bound(coord.begin(), coord.end(), b) - lower_bound(coord.begin(), coord.end(), a);
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
		if (x[i] == 0) {
			start[i] = 1;
		}
		if (x[i] == L) {
			fin[i] = 1;
		}
	}
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g[a].push_back(b);
		gr[b].push_back(a);
		if (c == 2) {
			g[b].push_back(a);
			gr[a].push_back(b);
		}
	}
	for (int i = 0; i < n; i++) {
		if (used[i] || !start[i]) {
			continue;
		}
		get_topsort(i);
	}
	reverse(topsort.begin(), topsort.end());
	int clr = 0;
	for (auto v : topsort) {
		if (color[v] == -1) {
			paint(v, clr++);
		}
	}
	sort(coord.begin(), coord.end());
	for (int i = 0; i < n; i++) {
		for (auto to : g[i]) {
			if (color[i] != -1 && color[to] != -1 && color[i] != color[to]) {
				G[color[i]].push_back(color[to]);
			}
		}
	}
	for (int i = 0; i < clr; i++) {
		sort(G[i].begin(), G[i].end());
		G[i].resize(unique(G[i].begin(), G[i].end()) - G[i].begin());
	}
	topsort.clear();
	memset(used, 0, sizeof(used));
	for (int i = 0; i < clr; i++) {
		if (!used[i]) {
			tp(i);
		}
	}
	for (auto v : topsort) {
		for (auto to : G[v]) {
			l[v] = min(l[v], l[to]);
			r[v] = max(r[v], r[to]);
		}
	}
	vector<pair<int, int>> ans;
	for (int i = 0; i < n; i++) {
		if (!start[i]) {
			continue;
		}
		int v = color[i];
		// cerr << i << '\t' << l[v] << ' ' << r[v] << '\n';
		ans.emplace_back(-y[i], get(l[v], r[v]));
	}
	sort(ans.begin(), ans.end());
	for (auto it : ans) {
		cout << it.second << '\n';
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
	while (cin >> n >> m >> L >> R)
		solve();
	return 0;
}