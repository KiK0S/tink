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
	const int MAXLOG = 4;
#else
	const int MAXN = 1e5;
	const int MAXLOG = 20;
#endif

#define int ll

const int INF = 1e15;
int n;
int pnt = 0;
int val[MAXN];
int sparse_gcd[MAXN][MAXLOG];
int len[MAXN];
int pref[MAXN];

struct query {
	int a;
	int l, r;
	query() {}
	query(int _a, int _l, int _r) {
		a = _a;
		l = _l;
		r = _r;
	}
};

vector<query> q;

struct segtree {
	int val;
	int push;
	segtree() {}
	segtree(int x) {
		val = x;
		push = 0;
	}
};

segtree t[4 * MAXN];

inline void init() {
	pnt = 0;
	len[1] = 0;
	for (int i = 2; i < MAXN; i++) {
		len[i] = len[i >> 1] + 1;
	}
	q.clear();
}

void build() {
	for (int i = 0; i < n; i++) {
		sparse_gcd[i][0] = abs(val[i]);
	}
	for (int i = 1; i < MAXLOG; i++) {
		for (int j = 0; j + (1 << (i - 1)) < n; j++) {
			sparse_gcd[j][i] = __gcd(sparse_gcd[j][i - 1], sparse_gcd[j + (1 << (i - 1))][i - 1]);
		}
	}
}

int get_gcd(int l, int r) {
	int lg = len[r - l + 1];
	return __gcd(sparse_gcd[l][lg], sparse_gcd[r - (1 << (lg)) + 1][lg]);
}


void push(int v, int tl, int tr) {
	if (t[v].push != 0) {
		if (tl == tr) {
			t[v].val += t[v].push;
		}
		else {
			t[2 * v].push += t[v].push;
			t[2 * v + 1].push += t[v].push;
			t[v].val += t[v].push; 
		}
		t[v].push = 0;
	}
}

void build(int v, int tl, int tr) {
	t[v].push = 0;
	if (tl == tr) {
		t[v].val = pref[pnt];
		pnt++;
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v].val = max(t[2 * v].val, t[2 * v + 1].val);
}

void upd(int v, int tl, int tr, int l, int r, int x) {
	push(v, tl, tr);
	if (tl > r || l > tr) {
		return;
	}
	if (l <= tl && tr <= r) {
		t[v].push += x;
		push(v, tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	upd(2 * v, tl, tm, l, r, x);
	upd(2 * v + 1, tm + 1, tr, l, r, x);
	t[v].val = max(t[2 * v].val, t[2 * v + 1].val);
}

int get(int v, int tl, int tr, int l, int r) {
	push(v, tl, tr);
	if (tl > r || l > tr) {
		return -INF;
	}
	if (l <= tl && tr <= r) {
		return t[v].val;
	}
	int tm = (tl + tr) >> 1;
	return max(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	pref[0] = val[0];
	for (int i = 1; i < n; i++) {
		pref[i] = pref[i - 1] + val[i];
	}
	build(1, 0, n - 1);
	build();
	int ans = -1e15;
	for (int i = 0; i < n; i++) {
		int lastr = i;
		while (lastr < n) {
			int cur_gcd = get_gcd(i, lastr);
			int l = lastr;
			int r = n;
			while (l + 1 < r) {
				int mid = (l + r) >> 1;
				if (get_gcd(i, mid) == cur_gcd) {
					l = mid;
				}
				else {
					r = mid;
				}
			}
			q.emplace_back(i, lastr, l);
			lastr = l + 1;
		} 
	}
	reverse(q.begin(), q.end());
	vector<query> st;
	st.emplace_back(1e9, n, n);
	pnt = 0;
	for (int i = n - 1; i >= 0; i--) {
		while (st.back().a <= val[i]) {
			upd(1, 0, n - 1, st.back().l, st.back().r, st.back().a);
			st.pop_back();
		}
		st.emplace_back(val[i], i, st.back().l - 1);
		// for (auto it : st) {
		// 	cerr << it.a << ' ' << it.l << ' ' << it.r << '\t';
		// }
		// cerr << '\n';
		upd(1, 0, n - 1, st.back().l, st.back().r, -val[i]);
		while (pnt < q.size() && q[pnt].a == i) {
			int got = get(1, 0, n - 1, q[pnt].l, q[pnt].r);
			if (i) {
				got -= pref[i - 1];
			}
			ans = max(ans, got * get_gcd(q[pnt].a, q[pnt].l));
			// cerr << got * get_gcd(q[pnt].a, q[pnt].l) << ' ';
			pnt++;
		}
		// cerr << '\n';
		// for (int j = 0; j < n; j++) {
		// 	cerr << get(1, 0, n - 1, j, j) << ' ';
		// }
		// cerr << '\n';
	}
	cout << ans << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}