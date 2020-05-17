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
	const int MAXN = 1e6 + 100;
#endif
// #define int ll
int n, m;

struct segtree {
	int val = 0;
	int push = -1;
};

int parent[(300001)];
segtree t[4 * MAXN];
set<int> colors[(300001)];
vector<int> g[(300001)];

inline void push(int v, int tl, int tr) {
	if (t[v].push == -1) {
		return;
	}
	if (tl == tr) {
		t[v].val = t[v].push;
	}
	else {
		t[2 * v].push = t[v].push;
		t[2 * v + 1].push = t[v].push;
	}
	t[v].push = -1;
}

inline void upd(int v, int tl, int tr, int l, int r, int x) {
	push(v, tl, tr);
	if (tl > r || l > tr) {
		return;
	}
	if (l <= tl && tr <= r) {
		t[v].push = x;
		push(v, tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	upd(2 * v, tl, tm, l, r, x);
	upd(2 * v + 1, tm + 1, tr, l, r, x);
}

inline int get(int v, int tl, int tr, int pos) {
	push(v, tl, tr);
	if (tl == tr) {
		return t[v].val;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		return get(2 * v, tl, tm, pos);
	}
	else {
		return get(2 * v + 1, tm + 1, tr, pos);
	}
}

inline void init() {
}

struct side {
	int x;
	int a, b;
	int type;
	side() {}
	side(int _a, int _b, int _c, int _d) {
		x = _a, a = _b, b = _c, type = _d;
	}
};

struct point {
	int x;
	int y, c;
	point() {}
	point(int a, int b, int _c) {
		x = a, y = b, c = _c;
	}
};

vector<int> coord;

inline int get(int a) {
	return lower_bound(coord.begin(), coord.end(), a) - coord.begin();
}

int ans[MAXN];

inline void dfs(int v) {
	if (g[v].size() == 0) {
		ans[v] = colors[v].size();
		return;
	}
	int mx = -1;
	int sz = colors[v].size();
	for (auto to : g[v]) {
		dfs(to);
		if (sz <= colors[to].size()) {
			sz = colors[to].size();
			mx = to;
		}
	}
	if (v == 0) {
		return;
	}
	for (auto to : g[v]) {
		if (mx == to) {
			colors[v].swap(colors[to]);
			break;
		}
	}
	for (auto to : g[v]) {
		for (auto it : colors[to]) {
			colors[v].insert(it);
		}
		colors[to].clear();
	}
	ans[v] = colors[v].size();
}
vector<side> s;
vector<point> p;
vector<int> ox;

inline void solve() {
	init();
	coord.resize(2 * n + m);
	s.resize(2 * n);
	p.resize(m);
	ox.resize(2 * n + m);
	for (int i = 0; i < n; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		s[2 * i] = side(a, b, d, i + 1);
		s[2 * i + 1] = side(c + 1, b, d, -i - 1);
		coord[2 * i] = (b);
		coord[2 * i + 1] = (d);
		ox[2 * i] = (a);
		ox[2 * i + 1] = (c + 1);
	}
	for (int i = 0; i < m; i++) {
		int x, y, c;
		cin >> x >> y >> c;
		p[i] = point(x, y, c);
		coord[2 * n + i] = (y);
		ox[2 * n + i] = (x);
	}
	sort(coord.begin(), coord.end());
	coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
	sort(ox.begin(), ox.end());
	ox.resize(unique(ox.begin(), ox.end()) - ox.begin());	
	sort(s.begin(), s.end(), [](side &a, side &b){
		if (a.type < 0 && b.type < 0) {
			return a.x < b.x || a.x == b.x && a.a > b.a;
		}
		if (a.type > 0 && b.type > 0) {
			return a.x < b.x || a.x == b.x && a.a < b.a;
		}
		return a.x < b.x || a.x == b.x && a.type < b.type;
	});
	sort(p.begin(), p.end(), [](point &a, point &b){
		return a.x < b.x;
	});
	int pnt1 = 0, pnt2 = 0;
	for (auto x : ox) {
		while (pnt1 < s.size() && s[pnt1].x == x) {
			s[pnt1].a = get(s[pnt1].a);
			s[pnt1].b = get(s[pnt1].b);
			if (s[pnt1].type >= 0) {
				parent[s[pnt1].type] = get(1, 0, MAXN - 1, s[pnt1].a);
				g[parent[s[pnt1].type]].push_back(s[pnt1].type);
				upd(1, 0, MAXN - 1, s[pnt1].a, s[pnt1].b, s[pnt1].type);
			}
			else {
				upd(1, 0, MAXN - 1, s[pnt1].a, s[pnt1].b, parent[-s[pnt1].type]);
			}
			pnt1++;
		}
		while (pnt2 < p.size() && p[pnt2].x == x) {
			int par = get(1, 0, MAXN - 1, get(p[pnt2].y));
			colors[par].insert(p[pnt2].c);
			pnt2++;
		}
	}
	dfs(0);
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("J.in", "r", stdin);
		freopen("J.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}