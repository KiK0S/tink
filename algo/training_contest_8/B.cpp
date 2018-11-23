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
	const int MAXN = 3e5;
#endif

#define int ll

int n, m;

int a[MAXN];
int b[MAXN];

struct tree {
	tree *l = nullptr, *r = nullptr;
	int x, y;
	int sz;
	tree() {}
	tree(int a) {
		x = a;
		y = rand();
		sz = 0;		
	}
};

int getsz(tree *t) {
	return t == nullptr ? 0 : t->sz;
}

void upd(tree *t) {
	if (t == nullptr) {
		return;
	}
	t->sz = getsz(t->l) + getsz(t->r) + 1;
}


void merge(tree *&t, tree *l, tree *r) {
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
}

void split(tree *t, tree *&l, tree *&r, int x) {
	if (t == nullptr) {
		l = nullptr;
		r = nullptr;
		upd(l);
		upd(r);
		return;
	}
	if (t->x <= x) {
		split(t->r, t->r, r, x);
		l = t;
	}
	else {
		split(t->l, l, t->l, x);
		r = t;
	}
	upd(r);
	upd(l);
}

void spl(tree *t, tree *&l, tree *&r) {
	if (getsz(t->l) != 0) {
		spl(t->l, l, r);
		t->l = r;
		r = t;
	}
	else {
		l = new	tree();
		l->x = t->x;
		l->y = t->y;
		l->sz = 1;
		r = t->r;
	}
	upd(l);
	upd(r);
}

inline void init() {

}

inline void solve() {
	init();
	tree * A = nullptr, *B = nullptr;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		merge(A, A, new tree(a[i]));
	}
	for (int j = 0; j < m; j++) {
		cin >> b[j];
		merge(B, B, new tree(b[j]));
	}
	int cnt = 0;
	int ans = 0;
	while (getsz(A) != 0 && getsz(B) != 0) {
		tree *na = nullptr, *nb = nullptr, *ma = nullptr, *mb = nullptr;
		// cerr << getsz(A) << ' ' << getsz(B) << '\n';
		spl(A, na, ma);
		spl(B, nb, mb);
		// cerr << getsz(na) << ' ' << getsz(nb) << '\n';
		// cerr << getsz(ma) << ' ' << getsz(mb) << '\n';
		if (na->x > nb->x || na->x == nb->x && cnt % 2 == 0) {
			if (na->x == nb->x) {
				cnt++;
			}
			na->x += nb->x;
			tree *L = nullptr, *R = nullptr;
			split(ma, L, R, na->x);
			// cerr << "A win " << na->x << ' ' << getsz(L) + 1 << '\n';
			ans += getsz(L) + 1;
			merge(L, L, na);
			merge(A, L, R);
			B = mb;
		}
		else {
			if (na->x == nb->x) {
				cnt++;
			}
			nb->x += na->x;
			tree *L = nullptr, *R = nullptr;
			// cerr << mb->x << '\n';
			split(mb, L, R, nb->x);
			// cerr << "B win " << nb->x << ' ' << getsz(L) + 1 << '\n';
			ans += getsz(L) + 1;
			merge(L, L, nb);
			merge(B, L, R);
			A = ma;
		}
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}