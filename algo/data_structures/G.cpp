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
	const int MAXN = 20;
#else
	const int MAXN = 6e5;
#endif

struct segtree {
	segtree *l = nullptr, *r = nullptr;
	int val;
};

struct Queue {
	segtree *v = nullptr;
	int l = 0;
	int r = 0;
};

void build(segtree *&v, int tl, int tr) {
	v = new segtree();
	if (tl == tr) {
		return;
	}
	int tm = (tl + tr) >> 1;
	build(v->l, tl, tm);
	build(v->r, tm + 1, tr);
}

int get(segtree *v, int tl, int tr, int pos) {
	if (tl == tr) {
		return v->val;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		return get(v->l, tl, tm, pos);
	}
	else {
		return get(v->r, tm + 1, tr, pos);
	}
}

segtree *upd(segtree *v, int tl, int tr, int pos, int x) {
	segtree *nw = new segtree();
	nw->l = v->l;
	nw->r = v->r;
	if (tl == tr) {
		nw->val = x;
		return nw;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		nw->l = upd(nw->l, tl, tm, pos, x);
	}
	else {	
		nw->r = upd(nw->r, tm + 1, tr, pos, x);
	}
	return nw;
}

Queue *q[MAXN];
int sz = 1;

void push(int version, int x) {
	q[sz]->v = upd(q[version]->v, 0, MAXN - 1, q[version]->r, x);
	q[sz]->l = q[version]->l;
	q[sz]->r = q[version]->r + 1;
	sz++;
}

int pop(int version) {
	q[sz]->v = q[version]->v;
	q[sz]->l = q[version]->l + 1;
	q[sz]->r = q[version]->r;
	sz++;
	return get(q[sz - 1]->v, 0, MAXN - 1, q[sz - 1]->l - 1);
}

int n;

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		q[i] = new Queue();
	}
	build(q[0]->v, 0, MAXN - 1);
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		if (t == 1) {
			int a, b;
			cin >> a >> b;
			push(a, b);
		}
		else {
			int a;
			cin >> a;
			cout << pop(a) << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}