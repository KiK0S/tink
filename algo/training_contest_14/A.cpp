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
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, k;
string s;

struct segtree {
	int val = 0, push = 0;
};

segtree t[4 * MAXN];

void push(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].val += t[v].push;
		t[v].push = 0;
		return;
	}
	t[2 * v].push += t[v].push;
	t[2 * v + 1].push += t[v].push;
	t[v].val += t[v].push;
	t[v].push = 0;
}

void upd(int v, int tl, int tr, int l, int r, int x) {
	push(v, tl, tr);
	if (l > tr || tl > r) {
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
	t[v].val = min(t[2 * v].val, t[2 * v + 1].val);
}

int get(int v, int tl, int tr, int l, int r) {
	push(v, tl, tr);
	if (l > tr || tl > r) {
		return 1e9;
	}
	if (l <= tl && tr <= r) {
		return t[v].val;
	}
	int tm = (tl + tr) >> 1;
	return min(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
}

inline void init() {
	for (int i = 0; i < 4 * MAXN; i++) {
		t[i].val = t[i].push = 0;
	}
}

inline void solve() {
	init();
	int l = 0;
	int r = k - 1;
	int cnt_open = 0;
	int cnt_close = 0;
	for (int i = l; i <= r; i++) {
		if (s[i] == '(') {
			cnt_open++;
			upd(1, 0, MAXN - 1, i, MAXN - 1, 1);
		}
		else {
			cnt_close++;
			upd(1, 0, MAXN - 1, i, MAXN - 1, -1);
		}
	}
	int ans = 0;
	while (r < n) {
		cerr << l << ' ' << r << ' ' << cnt_close << ' ' << cnt_open << '\n';
		if (get(1, 0, MAXN - 1, l, r) == 0 && cnt_close == cnt_open) {
			ans++;
		}
		if (s[l] == '(') {
			cnt_open--;
			upd(1, 0, MAXN - 1, l, MAXN - 1, -1);
		}
		else {
			cnt_close--;
			upd(1, 0, MAXN - 1, l, MAXN - 1, 1);
		}
		l++;
		r++;
		if (r == n) {
			break;
		}
		if (s[r] == '(') {
			cnt_open++;
			upd(1, 0, MAXN - 1, r, MAXN - 1, 1);
		}
		else {
			cnt_close++;
			upd(1, 0, MAXN - 1, r, MAXN - 1, -1);
		}
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k >> s)
		solve();
	return 0;
}