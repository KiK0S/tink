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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 1e3 + 10;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m;
int g[MAXN][MAXN];
vector<int> zero[MAXN];
int ans[MAXN][MAXN];

struct segtree {
	int ans;
	int pref;
	int suf;
};

segtree t[4 * MAXN];

void upd(int v, int tl, int tm, int tr) {
	t[v].ans = max(t[2 * v].ans, t[2 * v + 1].ans);
	t[v].ans = max(t[v].ans, t[2 * v].suf + t[2 * v + 1].pref);
	if (t[2 * v].pref == tm - tl + 1) {
		t[v].pref = tm - tl + 1 + t[2 * v + 1].pref;
	}
	else {
		t[v].pref = t[2 * v].pref;
	}
	if (t[2 * v + 1].suf == tr - tm) {
		t[v].suf = tr - tm + t[2 * v].suf;
	}
	else {
		t[v].suf = t[2 * v + 1].suf;
	}
}

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].ans = t[v].suf = t[v].pref = 1;
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	upd(v, tl, tm, tr);
}

void upd(int v, int tl, int tr, int pos, int x) {
	if (tl == tr) {
		t[v].ans = t[v].suf = t[v].pref = x;
		return;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		upd(2 * v, tl, tm, pos, x);
	}
	else {
		upd(2 * v + 1, tm + 1, tr, pos, x);
	}
	upd(v, tl, tm, tr);
}


inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> g[i][j];
			g[i][j] = 1 - g[i][j];
			if (g[i][j] == 0) {
				zero[j].push_back(i);
			}
		}
	}
	for (int l = 0; l < n; l++) {
		build(1, 0, m - 1);
		vector<pair<int, int>> ev;
		for (int i = 0; i < m; i++) {
			int x = lower_bound(zero[i].begin(), zero[i].end(), l) - zero[i].begin();
			if (x != zero[i].size()) {
				ev.emplace_back(zero[i][x], i);
			}
		}
		sort(ev.begin(), ev.end());
		int pnt = 0;
		for (int r = l; r < n; r++) {
			int cur_ans = 0;
			while (pnt < ev.size() && ev[pnt].first == r) {
				upd(1, 0, m - 1, ev[pnt].second, 0);
				pnt++;
			}
			cur_ans = max(cur_ans, t[1].ans * (r - l + 1));
			ans[l][r] = cur_ans;
		}
	}
	for (int l = n - 1; l >= 0; l--) {
		for (int r = l; r < n; r++) {
			if (r > l) {
				ans[l][r] = max(ans[l][r], ans[l][r - 1]);
				ans[l][r] = max(ans[l][r], ans[l + 1][r]);
			}
		}
	}
	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--, r--;
		cout << ans[l][r] << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}