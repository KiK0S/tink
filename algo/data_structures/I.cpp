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
	const int MAXN = 2e5;
#endif

int n, s, m ;

struct segtree {
	segtree *l = nullptr, *r = nullptr;
	int mn = -1e9;
};

segtree * roots[MAXN];

void build(segtree *&v, int tl, int tr) {
	v = new segtree();
	if (tl == tr) {
		return;
	}
	int tm = (tl + tr) >> 1;
	build(v->l, tl, tm);
	build(v->r, tm + 1, tr);
}

segtree * upd(segtree *v, int tl, int tr, int pos, int val) {
	segtree *nw = new segtree();
	nw->mn = v->mn;
	nw->l = v->l;
	nw->r = v->r;
	if (tl == tr) {
		nw->mn = val;
		return nw;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		nw->l = upd(v->l, tl, tm, pos, val);
	}
	else {
		nw->r = upd(v->r, tm + 1, tr, pos, val);
	}
	nw->mn = min(nw->l->mn, nw->r->mn);
	return nw;
}

int get(segtree *v, int tl, int tr, int a) {
	if (tl == tr) {
		return tl;
	}
	int tm = (tl + tr) >> 1;
	// cerr << tl << ' ' << tr << " - " << v->l->mn << ' ' << v->r->mn << '\n';
	if (v->l->mn <= a) {
		return get(v->l, tl, tm, a);
	}
	else {
		return get(v->r, tm + 1, tr, a);
	}
}

inline void init() {

}

struct Q {
	int l, r, c;
	Q() {}
	Q(int a, int b, int _c) {
		l = a, r = b, c = _c;
	}
};

inline void solve() {
	init();
	vector<Q> q;
	vector<int> coords;
	coords.push_back(0);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> c >> a >> b;
		coords.push_back(a);
		coords.push_back(b);
		q.emplace_back(a, b, c);
	}
	coords.push_back(1e9 + 1);
	sort(coords.begin(), coords.end());
	coords.resize(unique(coords.begin(), coords.end()) - coords.begin());
	// for (auto it : coords) {
	// 	cerr << it << ' ';
	// }
	// cerr << '\n';
	sort(q.begin(), q.end(), [](Q a, Q b){
		return a.l < b.l;
	});
	int pnt = 0;
	for (int i = 0; i < coords.size(); i++) {
		if (i == 0) {
			build(roots[i], 1, MAXN - 1);
		}
		else {
			roots[i] = roots[i - 1];
		}
		while (pnt < q.size() && q[pnt].l == coords[i]) {
			// cerr << "upd " << q[pnt].c << ' ' << q[pnt].r << '\n';
			roots[i] = upd(roots[i], 1, MAXN - 1, q[pnt].c, q[pnt].r);
			pnt++;
		}
		// cerr << '\n';
	}
	int Q;
	cin >> Q;
	int pre = 0;
	for (int i = 0; i < Q; i++) {
		int a, b;
		cin >> a >> b;
		a += pre;
		b += pre;
		// cerr << a << ' ' << b << '\n';
		b = lower_bound(coords.begin(), coords.end(), b) - coords.begin() - 1;
		// cerr << a << ' ' << b << '\n';
		pre = get(roots[b], 1, MAXN - 1, a);
		if (pre == s + 1) {
			pre = 0;
		}
		// cerr << pre << '\n';
		cout << pre << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("I.in", "r", stdin);
		freopen("I.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> s >> m)
		solve();
	return 0;
}