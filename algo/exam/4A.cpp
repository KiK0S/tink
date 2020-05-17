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
	const int MAXN = 50;
#else
	const int MAXN = 2e5;
#endif

int n;

struct segtree {
	segtree *l = nullptr, *r = nullptr;
	int val = 0;
};

void build(segtree *&v, int tl, int tr) {
	if (v == nullptr) {
		v = new segtree();
	}
	if (tl == tr) {
		return;
	}
	int tm = (tl + tr) >> 1;
	build(v->l, tl, tm);
	build(v->r, tm + 1, tr);
}

segtree *upd(segtree *v, int tl, int tr, int pos) {
	if (tl == tr) {
		segtree *nw = new segtree();
		nw->val = v->val + 1;
		return nw;
	}
	int tm = (tl + tr) >> 1;
	segtree *nw = new segtree();
	nw->l = v->l;
	nw->r = v->r;
	if (pos <= tm) {
		nw->l = upd(v->l, tl, tm, pos);
	}
	else {
		nw->r = upd(v->r, tm + 1, tr, pos);
	}
	nw->val = nw->l->val + nw->r->val;
	return nw;
}

int get(segtree *v, int tl, int tr, int l, int r) {
	if (l > tr || tl > r) {
		return 0;
	}
	if (l <= tl && tr <= r) {
		return v->val;
	}
	int tm = (tl + tr) >> 1;
	return get(v->l, tl, tm, l, r) + get(v->r, tm + 1, tr, l, r);
}

segtree *roots[MAXN];

inline void init() {

}

inline void solve() {
	init();
	int pnt = 0;
	build(roots[0], 0, MAXN - 1);
	for (int i = 0; i < n; i++) {
		int t, pos;
		cin >> t >> pos;
		while (pnt < t) {
			roots[pnt + 1] = roots[pnt];
			pnt++;
		}
		roots[t] = upd(roots[t], 0, MAXN - 1, pos);
	}
	while (pnt + 1 < MAXN) {
		roots[pnt + 1] = roots[pnt];
		pnt++;
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int q, p, r, k;
		cin >> q >> p >> r >> k;
		int L = max(0, p - r);
		int R = min(MAXN - 1, p + r);
		int l = q - 1;
		r = MAXN;
		int sub = get(roots[q - 1], 0, MAXN - 1, L, R);
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (get(roots[mid], 0, MAXN - 1, L, R) >= k + sub) {
				r = mid;
			}			
			else {
				l = mid;
			}
		}
		if (r == MAXN) {
			cout << "-1\n";
		}
		else {
			cout << r << '\n';
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("4A.in", "r", stdin);
		freopen("4A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}