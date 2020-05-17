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
#else
	const int MAXN = 1e5;
#endif

int n, m;

struct treap {
	treap *l, *r;
	int sz, y;
	int x;
	treap(int val) {
		x = val;
		y = ((1ll * rand() << 15) | rand()) & (INT32_MAX - 1);
		sz = 1;
		l = nullptr;
		r = nullptr;
	}
};

int getsz(treap *t) {
	if (t == nullptr) return 0;
	return t->sz;
}

void upd(treap *t) {
	if (t == nullptr) {
		return;
	}
	t->sz = 1;
	t->sz += getsz(t->l) + getsz(t->r);
}

void merge(treap *&t, treap *l, treap *r) {
	if (l == nullptr) {
		t = r;
		upd(t);
		return;
	}
	if (r == nullptr) {
		t = l;
		upd(t);
		return;
	}
	if (l->y > r->y) {
		merge(l->r, l->r, r);
		t = l;
	}
	else {
		merge(r->l, l, r->l);
		t = r;
	}
	upd(t);
	return;
}

void split(treap *t, treap *&l, treap *&r, int x) {
	if (t == nullptr) {
		l = nullptr;
		r = nullptr;
		return;
	}
	int sz_left = getsz(t->l) + 1;
	if (x <= sz_left) {
		split(t->l, l, t->l, x);
		r = t;
	}
	else {
		split(t->r, t->r, r, x - sz_left);
		l = t;
	}
	upd(l);
	upd(r);
}

void dfs(treap *t) {
	if (t == nullptr) 
		return;
	dfs(t->l);
	cout << t->x << ' ';
	dfs(t->r);
}

inline void init() {

}

inline void solve() {
	init();
	treap *root = nullptr;
	for (int i = 0; i < n; i++) {
		merge(root, root, new treap(i + 1));
	}	
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		treap *L = nullptr, *M = nullptr, *R = nullptr;
		split(root, L, R, r + 1);
		split(L, L, M, l);
		merge(L, M, L);
		merge(root, L, R);
	}
	dfs(root);
}

signed main() {
	#ifdef DEBUG
		freopen("N.in", "r", stdin);
		freopen("N.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}