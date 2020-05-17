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
	const int MAXN = 1e5;
#endif

int n, s = 1e9;

int a[MAXN];
char rot[MAXN];

int dy[] = {1, 0, -1, 0};
int dx[] = {0, 1, 0, -1};

inline void init() {
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> rot[i];
	}
}

void L(int &dir) {
	dir--;
	if (dir == -1) dir = 3;
}

void R(int &dir) {
	dir++;
	if (dir == 4) dir = 0;
}

void insert(vector<pair<int, int>> &all, pair<int, int> a, int d = 0) {
	all.push_back(a);
	for (int i = 1; i <= d; i++) {
		all.push_back({a.first + i, a.second});
		all.push_back({a.first - i, a.second});
		all.push_back({a.first, a.second + i});
		all.push_back({a.first, a.second - i});
	}
}

struct segtree {
	segtree *l = nullptr, *r = nullptr;
	int push = 0;
	int val = 0;
};

segtree *root = new segtree();

void push(segtree *t, int tl, int tr) {
	if (tl == tr) {
		t->val += t->push;
		t->push = 0;
		return;
	}
	if (t->l == nullptr) {
		t->l = new segtree();
	}
	if (t->r == nullptr) {
		t->r = new segtree();
	}
	t->val += t->push;
	t->l->push += t->push;
	t->r->push += t->push;
	t->push = 0;
}

void upd(segtree *t, int tl, int tr, int l, int r, int x) {
	push(t, tl, tr);
	if (tl > r || l > tr) {
		return;
	}
	if (l <= tl && tr <= r) {
		t->push += x;
		push(t, tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	upd(t->l, tl, tm, l, r, x);
	upd(t->r, tm + 1, tr, l, r, x);
	t->val = max(t->l->val, t->r->val);
}

pair<int, int> get(segtree *t, int tl, int tr) {
	push(t, tl, tr);
	if (tl == tr) {
		return {t->val, tl};
	}
	int tm = (tl + tr) >> 1;
	push(t->l, tl, tm);
	push(t->r, tm + 1, tr);
	if (t->l->val >= t->r->val) {
		return get(t->l, tl, tm);
	}
	return get(t->r, tm + 1, tr);
}

struct ev{
	int pos;
	int l, r;
	int x;
	ev(int a, int b, int c, int d) {
		pos = a, l = b, r = c, x = d;
	}
};

vector<ev> scan;

void update(pair<int, int> a, pair<int, int> b) {
	scan.emplace_back(a.first, a.second, b.second - 1, 1);
	scan.emplace_back(b.first, a.second, b.second - 1, -1);
}


pair<int, int> get() {
	return get(root, -s, s);
}

inline void solve() {
	root = new segtree();
	init();
	int x = 0;
	int y = 0;
	int dir = 0;
	for (int i = 0; i < n; i++) {
		vector<pair<int, int>> all;
		if (dir == 0) {
			insert(all, {s, y});
		}
		if (dir == 1) {
			insert(all, {x, -s});
		}
		if (dir == 2) {
			insert(all, {-s, y});
		}
		if (dir == 3) {
			insert(all, {x, s});
		}
		insert(all, {x, y});
		x += dx[dir] * a[i];
		y += dy[dir] * a[i];
		if (dir == 0) {
			insert(all, {s, y});
		}
		if (dir == 1) {
			insert(all, {x, -s});
		}
		if (dir == 2) {
			insert(all, {-s, y});
		}
		if (dir == 3) {
			insert(all, {x, s});
		}
		insert(all, {x, y});
		sort(all.begin(), all.end());
		update(all[0], all[3]);
		all.clear();
		insert(all, {x, y});
		if (rot[i] == 'L') {
			if (dir == 0) {
				insert(all, {s, y});
				insert(all, {x, s});
				insert(all, {s, s});
			}
			if (dir == 1) {
				insert(all, {s, y});
				insert(all, {x, -s});
				insert(all, {s, -s});
			}
			if (dir == 2) {
				insert(all, {-s, y});
				insert(all, {x, -s});
				insert(all, {-s, -s});
			}
			if (dir == 3) {
				insert(all, {-s, y});
				insert(all, {x, s});
				insert(all, {-s, s});
			}
			L(dir);
		}
		else {
			if (dir == 3) {
				insert(all, {s, y});
				insert(all, {x, s});
				insert(all, {s, s});
			}
			if (dir == 0) {
				insert(all, {s, y});
				insert(all, {x, -s});
				insert(all, {s, -s});
			}
			if (dir == 1) {
				insert(all, {-s, y});
				insert(all, {x, -s});
				insert(all, {-s, -s});
			}
			if (dir == 2) {
				insert(all, {-s, y});
				insert(all, {x, s});
				insert(all, {-s, s});
			}
			R(dir);
		}
		sort(all.begin(), all.end());
		update(all[0], all[3]);
		all.clear();
	}
	sort(scan.begin(), scan.end(), [](ev a, ev b){return a.pos < b.pos;});
	int pnt = 0;
	int ans = -1;
	pair<int, int> res;
	while (pnt < scan.size()) {
		int start = pnt;
		while (pnt < scan.size() && scan[start].pos == scan[pnt].pos) {
			upd(root, -s, s, scan[pnt].l, scan[pnt].r, scan[pnt].x);
			pnt++;
		}
		pair<int, int> bst = get(root, -s, s);
		if (bst.first > ans) {
			ans = bst.first;
			res.first = scan[start].pos;
			res.second = bst.second;
		}
	}
	cerr << ans << '\n';
	cout << res.first << ' ' << res.second << '\n';
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