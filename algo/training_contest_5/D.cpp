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

int n;
string s;

struct treap {
	int x, y, sz = 1, rev = 0;
	treap *l = nullptr, *r = nullptr;
	treap() {}
	treap(int _x) {
		x = _x;
		y = rand();
	}
};

int getsz(treap *v) {
	return v == nullptr ? 0 : v->sz;
}

void upd(treap *&v) {
	if (v == nullptr) {
		return;
	}
	v->sz = getsz(v->l) + getsz(v->r) + 1;
	if (v->rev) {
		swap(v->l, v->r);
		if (v->l != nullptr) {
			v->l->rev ^= 1;
		}
		if (v->r != nullptr) {
			v->r->rev ^= 1;
		}
		v->rev = 0;
	}
}

void merge(treap *&v, treap *l, treap *r) {
	upd(l);
	upd(r);
	if (l == nullptr) {
		v = r;
		upd(v);
		return;
	}
	if (r == nullptr) {
		v = l;
		upd(v);
		return;
	}
	if (l->y > r->y) {
		merge(l->r, l->r, r);
		v = l;
	}
	else {
		merge(r->l, l, r->l);
		v = r;
	}
	upd(v);
}

void split(treap *v, treap *&l, treap *&r, int x) {
	upd(v);
	if (v == nullptr) {
		l = v;
		r = v;
		upd(l);
		upd(r);
		return;
	}
	int szl = getsz(v->l) + 1;
	if (x <= szl) {
		split(v->l, l, v->l, x);
		r = v;
	}
	else {
		split(v->r, v->r, r, x - szl);
		l = v;
	}
	upd(l);
	upd(r);
}

treap *A = nullptr, *B = nullptr;

inline void init() {
}

int pnt = 1;

void add(treap *&v) {
	merge(v, v, new treap(pnt));
	pnt++;
	pnt %= 10;
}

void del(treap *&v) {
	treap *L = nullptr, *R = nullptr;
	split(v, L, R, 2);
	// cerr << L->x;
	cout << L->x;
	v = R;
}

void rev(treap *&v) {
	if (v == nullptr) return;
	v->rev ^= 1;
}

inline void solve() {
	init();
	for (auto c : s) {
		if (c == 'a') {
			add(A);
		}
		if (c == 'b') {
			add(B);
		} 
		if (c == 'A') {
			del(A);
		}
		if (c == 'B') {
			del(B);
		}
		if (c == '>') {
			rev(A);
			merge(B, B, A);
			A = nullptr;
		}
		if (c == ']') {
			rev(B);
			merge(A, A, B);
			B = nullptr;
		}
		if (c == '<') {
			treap *L = nullptr, *R = nullptr;
			// cerr << getsz(B) << ' ' << (getsz(B) + 1) / 2 + 1 << '\n';
			split(B, L, R, (getsz(B) + 1) / 2 + 1);
			rev(R);
			A = R;
			B = L;
		}
		if (c == '[') {
			treap *L = nullptr, *R = nullptr;
			// cerr << getsz(A) << ' ' << (getsz(A) + 1) / 2 + 1<< '\n';
			split(A, L, R, (getsz(A) + 1) / 2 + 1);
			rev(R);
			B = R;
			A = L;
		}	
	}
	cout << '\n';
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
	while (cin >> n >> s)
		solve();
	return 0;
}