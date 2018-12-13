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

int n, s = 100;

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


struct _res{
	int ans = 0;
};

struct segtree_in {
	segtree_in *l = nullptr, *r = nullptr;
	_res v = {0};
	int push = 0;
};

struct segtree_out {
	segtree_out *l = nullptr, *r = nullptr;
	segtree_in *v;
	vector<pair<int, int>> q;
	_res ans;
	segtree_out() {
		v = new segtree_in();
	}
};

bool operator < (_res a, _res b) {
	return a.ans < b.ans;
}

bool operator > (_res a, _res b) {
	return a.ans > b.ans;
}

bool operator == (_res a, _res b) {
	return a.ans == b.ans;
}

void push(segtree_in *t, int tl, int tr) {
	if (t == nullptr) {
		return;
	}
	t->v.ans += t->push;
	if (tl == tr) {
		t->push = 0;
		return;
	}
	if (t->l == nullptr) {
		t->l = new segtree_in();
	}
	t->l->push += t->push;
	if (t->r == nullptr) {
		t->r = new segtree_in();
	}
	t->r->push += t->push;	
	t->push = 0;
}

_res get_ans(segtree_in *t) {
	if (t == nullptr) {
		return _res();
	}
	return t->v;
}

void update_in(segtree_in *t, int tl, int tr, int l, int r) {
	push(t, tl, tr);
	if (tl > r || l > tr) {
		return;
	}
	if (l <= tl && tr <= r) {
		t->push++;
		push(t, tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	if (t->l == nullptr) {
		t->l = new segtree_in();
	}
	if (t->r == nullptr) {
		t->r = new segtree_in();
	}
	update_in(t->l, tl, tm, l, r);
	update_in(t->r, tm + 1, tr, l, r);
	t->v = max(t->l->v, t->r->v);
}

void push_out(segtree_out *t, int tl, int tr) {
	if (t == nullptr) {
		return;
	}
	for (auto p : t->q) {
		update_in(t->v, -s, s, p.first, p.second);
	}
	t->ans = max(t->ans, get_ans(t->v));
	if (tl == tr) {
		t->q.clear();
		return;
	}
	if (t->l == nullptr) {
		t->l = new segtree_out();
	}
	if (t->r == nullptr) {
		t->r = new segtree_out();
	}
	for (auto p : t->q) {
		t->l->q.push_back(p);
		t->r->q.push_back(p);
	}
	t->q.clear();
}

void update_out(segtree_out *t, int tl, int tr, int l, int r, int a, int b) {
	push_out(t, tl, tr);
	if (tl > r || l > tr) {
		return;
	}
	if (l <= tl && tr <= r) {
		t->q.push_back({a, b});
		push_out(t, tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	if (t->l == nullptr) {
		t->l = new segtree_out();
	}
	if (t->r == nullptr) {
		t->r = new segtree_out();
	}
	update_out(t->l, tl, tm, l, r, a, b);
	update_out(t->r, tm + 1, tr, l, r, a, b);
	t->ans = max(t->l->ans, t->r->ans);
}

segtree_out *root;

int g[500][500];

void update(pair<int, int> a, pair<int, int> b) {
	for (int i = a.first + 200; i <= b.first + 200 - 1; i++) {
		for (int j = a.second + 200; j <= b.second + 200 - 1; j++) {
			g[i][j]++;
		}
	}
	// update_out(root, -s, s, a.first, b.first - 1, a.second, b.second - 1);
}

int get_in(segtree_in *t, int tl, int tr) {
	push(t, tl, tr);
	if (tl == tr) {
		return tl;
	}
	int tm = (tl + tr) >> 1;
	push(t->l, tl, tm);
	push(t->r, tm + 1, tr);
	if (get_ans(t->l) == get_ans(t)) {
		return get_in(t->l, tl, tm);
	}
	return get_in(t->r, tm + 1, tr);
}

pair<int, int> get_out(segtree_out *t, int tl, int tr) {
	push_out(t, tl, tr);
	if (tl == tr) {
		int x = tl;
		int y = get_in(t->v, -s, s);
		return {x, y};
	}
	int tm = (tl + tr) >> 1;
	push_out(t->l, tl, tm);
	push_out(t->r, tm + 1, tr);
	if (t->l->ans == t->ans) {
		return get_out(t->l, tl, tm);
	}
	return get_out(t->r, tm + 1, tr);
}

pair<int, int> get() {
	int res = -1;
	pair<int, int> h = {-1, -1};
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
			if (g[i][j] > res) {
				res = g[i][j];
				h = {i - 200, j - 200};
			}
		}
	}
	return h;
	// return get_out(root, -s, s);
}

inline void solve() {
	root = new segtree_out();
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
	pair<int, int> res = get();
	cout << res.first << ' ' << res.second << '\n';
}

void test() {
	root = new segtree_out();
	for (int i = 0; i < n; i++) {
		int l, r, a, b;
		cin >> l >> a >> r >> b;
		update({l, a}, {r, b});
	}
	pair<int, int> res = get();
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
		test();
	return 0;
}