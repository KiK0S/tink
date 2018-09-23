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
	const int MAXCOORD = 100;
#else
	const int MAXN = 1e5 + 10;
	const int MAXCOORD = 1e5 + 10;
#endif

const ll INF = 1e9;

int n;
int a[MAXN];
int b[MAXN];
vector<int> g[MAXN];
int tin[MAXN];
vector<int> eul;
int sz[MAXN];
ll dp[MAXN];
int timer = 0;


struct line {
	ll k, m;
	line() {
		k = 0, m = INF * INF;
	}
	line(ll a, ll b) {
		k = a, m = b;
	}
	ll get(int x) {
		return k * x + m;
	}
};

struct li_chao {
	line cur;
	li_chao *l;
	li_chao *r;

	li_chao() {
		l = nullptr;
		r = nullptr;
	}

	void extend(li_chao *&ptr) {
		if (ptr == nullptr) {
			ptr = new li_chao();
		}
	}

	ll get(int tl, int tr, int x) {
		if (tl == tr) {
			return cur.get(x);
		}
		int tm = (tl + tr) >> 1;
		if (x <= tm) {
			if (l == nullptr) {
				return cur.get(x);
			}
			return min(cur.get(x), l->get(tl, tm, x));
		}
		else {
			if (r == nullptr) {
				return cur.get(x);
			}
			return min(cur.get(x), r->get(tm + 1, tr, x));
		}
	}

	void add(int tl, int tr, line x) {
		if (x.k == 0 && x.m == INF * INF) {
			return;
		} 
		int tm = (tl + tr) >> 1;
		bool mid = x.get(tm) < cur.get(tm);
		bool lf = x.get(tl) < cur.get(tl);
		if (mid) {
			swap(cur, x);
			mid ^= 1;
			lf ^= 1;
		}
		if (tl == tr) {
			return;
		}
		if (lf) {
			extend(l);
			l->add(tl, tm, x);
		}
		else {
			extend(r);
			r->add(tm + 1, tr, x);
		}
	}
};

struct segtree {
	li_chao *cur;
	segtree() {
		cur = new li_chao();
	}
};

segtree t[4 * MAXN];

void upd(int v, int tl, int tr, int pos, line l) {
	t[v].cur->add(-MAXCOORD, MAXCOORD, l);
	if (tl == tr) {
		return;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		upd(2 * v, tl, tm, pos, l);
	}
	else {
		upd(2 * v + 1, tm + 1, tr, pos, l);
	}
}

ll get(int v, int tl, int tr, int l, int r, int x) {
	if (l > tr || tl > r || l > r) {
		return INF * INF;
	}
	if (l <= tl && tr <= r) {
		return t[v].cur->get(-MAXCOORD, MAXCOORD, x);
	}
	int tm = (tl + tr) >> 1;
	return min(get(2 * v, tl, tm, l, r, x), get(2 * v + 1, tm + 1, tr, l, r, x));
}

void dfs(int v, int p = -1) {
	tin[v] = timer++;
	sz[v] = 1;
	eul.push_back(v);
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		dfs(to, v);
		sz[v] += sz[to];
	}
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		g[i].clear();
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int v, u;
		cin >> v >> u;
		v--, u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	dfs(0);
	for (int i = n - 1; i >= 0; i--) {
		if (sz[eul[i]] == 1) {
			dp[eul[i]] = 0;
		}
		else {
			dp[eul[i]] = get(1, 0, n - 1, i + 1, i + sz[eul[i]] - 1, a[eul[i]]);
		}
		upd(1, 0, n - 1, i, line(b[eul[i]], dp[eul[i]]));
	}
	for (int i = 0; i < n; i++) {
		cout << dp[i] << ' ';
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
	while (cin >> n)
		solve();
	return 0;
}