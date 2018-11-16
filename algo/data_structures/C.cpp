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
	const int MAXN = 1e5;
#endif


int n, q;
int INF = 1e9;

struct segtree {
	segtree *l = nullptr, *r = nullptr;
	vector<int> val;
};

void upd(segtree *&v, int tl, int tr, int pos, int x) {
	if (v == nullptr) {
		v = new segtree();
	}
	if (tl == tr) {
		v->val.push_back(x);
		return;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		upd(v->l, tl, tm, pos, x);
	}
	else {
		upd(v->r, tm + 1, tr, pos, x);
	}
}

int getsz(segtree *v) {
	if (v == nullptr) return 0;
	return v->val.size();
}

void build(segtree *v, int tl, int tr) {
	if (v == nullptr) {
		return;
	}
	if (tl == tr) {
		sort(v->val.begin(), v->val.end());
		return;
	}
	int tm = (tl + tr) >> 1;
	build(v->l, tl, tm);
	build(v->r, tm + 1, tr);
	v->val.resize(getsz(v->r) + getsz(v->l));
	if (v->r != nullptr && v->l != nullptr) {
		merge(v->r->val.begin(), v->r->val.end(), v->l->val.begin(), v->l->val.end(), v->val.begin());
	}
	else {
		if (v->l != nullptr) {
			copy(v->l->val.begin(), v->l->val.end(), v->val.begin());
		}
		else {
			copy(v->r->val.begin(), v->r->val.end(), v->val.begin());	
		}
	}
}

int get(segtree *v, int tl, int tr, int l, int r, int a, int b) {
	// cerr << tl << ' ' << tr << '\n';
	if (v == nullptr || l > tr || tl > r) {
		return 0;
	}
	if (v->val.size() == 0) {
		return 0;
	}
	if (l <= tl && tr <= r) {
		// cerr << "lw\n";
		return upper_bound(v->val.begin(), v->val.end(), b) - upper_bound(v->val.begin(), v->val.end(), a - 1);
	}
	int tm = (tl + tr) >> 1;
	return get(v->l, tl, tm, l, r, a, b) + get(v->r, tm + 1, tr, l, r, a, b);
}

inline void init() {

}

inline void solve() {
	init();
	segtree *root = nullptr;
	// cerr << "a\n";
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		upd(root, -INF, INF, x, y);
	}
	// cerr << "b\n";
	build(root, -INF, INF);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		cout << get(root, -INF, INF, a, c, b, d) << '\n';
		// cerr << "c\n";
	}
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