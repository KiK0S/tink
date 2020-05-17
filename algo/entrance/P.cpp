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
	const int MAXN = 2e5;
#else
	const int MAXN = 3e5;
#endif

int n;


namespace answer {
	int ans[MAXN + 10];
	
	void upd(int pos, int val){
		pos = n - pos;
		ans[pos] = max(ans[pos], val);
	}

	void calc() {
		for (int i = n - 1; i >= 0; i--) {
			ans[i] = max(ans[i], ans[i + 1]);
		}
	}

	void print() {
		calc();
		for (int i = 1; i <= n; i++) {
			cout << ans[i] << ' ';
		}
		cout << '\n';	
	}
};

struct segtree {

	pair<int, int> coords[MAXN];

	void build(int val[]) {
		for (int i = 0; i < n; i++) {
			coords[i] = {val[i], i};
		}
		sort(coords, coords + n);
		for (int i = 0; i < 4 * MAXN; i++) {
			t[i].sum = 0;
			t[i].mn = 0;
		}
	}

	void solve(int a[], int b[]) {
		build(a);
		vector<int> start(n);
		for (int i = 0; i < n; i++) {
			start[i] = lower_bound(coords, coords + n, make_pair(a[i], i)) - coords;
		}
		for (int i = 0; i < n; i++) {
			int l, r;
			int cur = get(1, 0, MAXN - 1, start[i]) + start[i];
			answer::upd(cur, a[i]);
			if (a[i] > b[i]) {
				l = lower_bound(coords, coords + n, make_pair(b[i], MAXN)) - coords;
				r = lower_bound(coords, coords + n, make_pair(a[i], -1)) - coords - 1;
				if (l > r) {
					continue;
				}
				add(1, 0, MAXN - 1, l, r, 1);
			}
			else {
				l = lower_bound(coords, coords + n, make_pair(a[i], i)) - coords;
				r = upper_bound(coords, coords + n, make_pair(b[i], MAXN)) - coords - 1;	
				if (l > r) {
					continue;
				}
				add(1, 0, MAXN - 1, l, r, -1);
			}
		}
 	}

	struct node {
		int sum = 0;
		int mn = 0;
		int push = 0;

	};

	node t[4 * MAXN];

	void push(int v, int tl, int tr) {
		if (t[v].push == 0 || tl == tr) {
			t[v].push = 0;
			return;
		}
		t[2 * v].mn = min(t[2 * v].mn, t[2 * v].sum + t[v].mn);
		t[2 * v + 1].mn = min(t[2 * v + 1].mn, t[2 * v + 1].sum + t[v].mn);
		t[2 * v].sum += t[v].sum;
		t[2 * v + 1].sum += t[v].sum;
		t[2 * v].push = 1;
		t[2 * v + 1].push = 1;
		t[v].sum = 0;
		t[v].mn = 0;
		t[v].push = 0;
	}

	void add(int v, int tl, int tr, int l, int r, int x) {
		push(v, tl, tr);
		if (tl > r || l > tr) {
			return;
		}
		if (l <= tl && tr <= r) {
			t[v].sum += x;
			t[v].mn = min(t[v].mn, t[v].sum);
			t[v].push = 1;
			push(v, tl, tr);
			return;
		}
		int tm = (tl + tr) >> 1;
		add(2 * v, tl, tm, l, r, x);
		add(2 * v + 1, tm + 1, tr, l, r, x);
	}

	int get(int v, int tl, int tr, int pos) {
		push(v, tl, tr);
		if (tl == tr) {
			return t[v].mn;
		}
		int tm = (tl + tr) >> 1;
		if (pos <= tm) {
			return get(2 * v, tl, tm, pos);
		}
		else {
			return get(2 * v + 1, tm + 1, tr, pos);
		}
	}
};

int a[MAXN];
int b[MAXN];

segtree f, s;
inline void init() {
	for (int i = 0; i <= MAXN; i++) {
		answer::ans[i] = 0;
	}
}

inline void read() {
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}	
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
}

inline void _solve() {
	init();
	f.solve(b, a);
	reverse(a, a + n);
	reverse(b, b + n);
	s.solve(a, b);
	answer::print();
}

signed main() {
	#ifdef DEBUG
		freopen("P.in", "r", stdin);
		freopen("P.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n) {
		read();
		_solve();
	}	
	return 0;
}