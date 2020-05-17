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
	const int MAXN = 5e5 + 100;
#endif

const int MAXV = 2 * MAXN;

int n, q;

struct node {
	int l = -1;
	int r = -1;
	int p = -1;
	int x;
	int mx = 0;
	int sz = 1;
	node(){}
	node(int a) {x = a;}
};

node T[MAXV];
int pnt = 0;

int make_new(int a) {
	assert(pnt < MAXV);
	T[pnt].x = a;
	T[pnt].mx = a;
	return pnt++;
}

int is_root(int t) {
	return T[t].p == -1;
}

int is_left(int t) {
	return T[T[t].p].l == t;
}

struct segtree {
	int last_spl = 0;
	int root = -1;
};

int get_mx(int t) {
	return t == -1 ? 0 : T[t].mx;
}

int get_sz(int t) {
	return t == -1 ? 0 : T[t].sz;
}

void upd(int t) {
	if (t == -1) {
		return;
	}
	T[t].mx = max(T[t].x, max(get_mx(T[t].l), get_mx(T[t].r)));
	T[t].sz = 1 + get_sz(T[t].l) + get_sz(T[t].r);
}

void rotate(int t) {
	if (T[T[t].p].p != -1) {
		if (is_left(T[t].p)) {
			T[T[T[t].p].p].l = t;
		}
		else {
			T[T[T[t].p].p].r = t;
		}
	}
	if (is_left(t)) {
		T[T[t].p].l = T[t].r;
		if (T[t].r != -1) {
			T[T[t].r].p = T[t].p;
		}
		T[t].r = T[t].p;
		T[t].p = T[T[t].r].p;
		T[T[t].r].p = t;
		upd(T[t].r);
	}
	else {
		T[T[t].p].r = T[t].l;
		if (T[t].l != -1) {
			T[T[t].l].p = T[t].p;
		}
		T[t].l = T[t].p;
		T[t].p = T[T[t].l].p;
		T[T[t].l].p = t;
		upd(T[t].l);
	}
	upd(t);
}


void print(int t, int _t = 0) {
	if (t == -1) {
		return;
	}
	print(T[t].l, _t + 1);
	for (int i = 0; i < _t; i++) {
		cerr << '\t';
	}
	cerr << T[t].x << '\n';
	print(T[t].r, _t + 1);
}


bool zig(int t) {
	if (is_root(T[t].p)) {
		rotate(t);
		return 1;
	}
	return 0;
}

bool zig_zig(int t) {
	bool a = is_left(t);
	bool b = is_left(T[t].p);
	if (a ^ b) {
		return 0;
	}
	rotate(T[t].p);
	rotate(t);
	return 1;
}

bool zig_zag(int t) {
	rotate(t);
	rotate(t);
	return 1;
}

void splay(int t) {
	while (!is_root(t)) {
		if (zig(t)) {
			continue;
		}
		if (zig_zig(t)) {
			continue;
		}
		zig_zag(t);
	}
}

int get(int t, int x) {
	if (t == -1) {
		return -1;
	}
	if (get_mx(T[t].l) > x) {
		return get(T[t].l, x);
	}
	if (T[t].x > x) {
		return t;
	}
	return get(T[t].r, x);
}

int get_k(int t, int k) {
	if (t == -1) {
		return -1;
	}
	if (get_sz(T[t].l) >= k) {
		return get_k(T[t].l, k);
	}
	if (get_sz(T[t].l) + 1 == k) {
		return T[t].x;
	}
	return get_k(T[t].r, k - get_sz(T[t].l) - 1);
}

segtree st[4 * MAXN];
int val[MAXN];

void upd_seg(int v) {
	int tp = get_mx(st[2 * v].root);
	st[v].last_spl = tp;
	int t = get(st[2 * v + 1].root, tp);
	if (t != -1) {
		splay(t);
		st[2 * v + 1].root = T[t].l;
		T[t].l = st[2 * v].root;
		if (st[2 * v].root != -1) {
			T[st[2 * v].root].p = t;
		}
	}
	else {
		t = st[2 * v].root;
	}
	st[v].root = t;
	upd(st[v].root);
}

void push(int v) {
	int t = get(st[v].root, st[v].last_spl);
	if (t != -1) {
		splay(t);
		st[2 * v].root = T[t].l;
		if (st[2 * v].root != -1) {
			T[st[2 * v].root].p = -1;
		}
		T[t].l = st[2 * v + 1].root;
		st[2 * v + 1].root = t;
	}
	else {
		st[2 * v].root = st[v].root;
	}
	upd(st[2 * v].root);
	upd(st[2 * v + 1].root);
}

void build(int v, int tl, int tr) {
	if (tl == tr) {
		st[v].root = make_new(val[tl]);
		upd(st[v].root);
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	upd_seg(v);
}

void upd(int v, int tl, int tr, int pos, int x) {
	if (tl == tr) {
		st[v].root = make_new(x);
		upd(st[v].root);
		return;
	}
	push(v);
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		upd(2 * v, tl, tm, pos, x);
	}
	else {
		upd(2 * v + 1, tm + 1, tr, pos, x);
	}
	upd_seg(v);
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	build(1, 0, n - 1);
	for (int i = 0; i < q; i++) {
		int a;
		cin >> a;
		if (a == 1) {
			int pos, x;
			cin >> pos >> x;
			pos--;
			upd(1, 0, n - 1, pos, x);
		}
		else {
			int k;
			cin >> k;
			cout << get_k(st[1].root, k) << '\n';
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> q)
		solve();
	return 0;
}