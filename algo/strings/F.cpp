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
	const int MAXN = 100;
#else
	const int MAXN = 6e5;
#endif


int n;
string s;
int val[MAXN];
int lcp[MAXN];
int sa[MAXN];
int pos[MAXN];
int psa[MAXN];
int nc[MAXN];
int cnt[MAXN];
int color[MAXN];

void countsort(int len) {
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++) {
		cnt[color[(i + len) % n] + 1]++;
	}
	partial_sum(cnt, cnt + MAXN, cnt);
	for (int i = 0; i < n; i++) {
		pos[i] = cnt[color[(i + len) % n]]++;
		psa[pos[i]] = i;
	}
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++) {
		cnt[color[i] + 1]++;
	}
	partial_sum(cnt, cnt + MAXN, cnt);
	for (int i = 0; i < n; i++) {
		pos[psa[i]] = cnt[color[psa[i]]]++;
		sa[pos[psa[i]]] = psa[i];
	}
	int clr = 0;
	for (int i = 0; i < n; i++) {
		if (i == 0 || make_pair(color[sa[i]], color[(sa[i] + len) % n]) != make_pair(color[sa[i - 1]], color[(sa[i - 1] + len) % n])) {
			clr++;
		}
		nc[sa[i]] = clr;
	}
	for (int i = 0; i < n; i++) {
		color[i] = nc[i];
	}
}

struct segtree {
	ll val = -1e18;
	ll add = 0;
};

segtree t[4 * MAXN];

void build(int v, int tl, int tr) {
	t[v].add = 0;
	if (tl == tr) {
		t[v].val = -sa[tl];
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v].val = max(t[2 * v].val, t[2 * v + 1].val);
}

void push(int v, int tl, int tr) {
	t[v].val += t[v].add;
	if (tl != tr) {
		t[2 * v].add += t[v].add;
		t[2 * v + 1].add += t[v].add;
	}
	t[v].add = 0;
}

void upd(int v, int tl, int tr, int l, int r, ll x) {
	push(v, tl, tr);
	if (tl > r || l > tr) {
		return;
	}
	if (l <= tl && tr <= r) {
		t[v].add += x;
		push(v, tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	upd(2 * v, tl, tm, l, r, x);
	upd(2 * v + 1, tm + 1, tr, l, r, x);
	t[v].val = max(t[2 * v].val, t[2 * v + 1].val);
}
	
ll get(int v, int tl, int tr, int l, int r) {
	push(v,  tl, tr);
	if (l > tr || tl > r) {
		return -1e18;
	}
	if (l <= tl && tr <= r) {
		return t[v].val;
	}
	int tm = (tl + tr) >> 1;
	return max(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
}

inline void init() {
	n = s.size();
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		val[i] = (int) s[i];
		color[i] = val[i];
	}
	n++;
	val[n - 1] = 1;
	color[n - 1] = 1;
	for (int len = 1; len <= n; len <<= 1) {
		countsort(len);
	}
	int x = 0;
	for (int i = 0; i < n; i++) {
		int ps = pos[i];
		if (ps != n - 1) {
			while (max(i, sa[ps + 1]) + x < n && val[i + x] == val[sa[ps + 1] + x]) {
				x++;
			}
			lcp[ps] = x;
		}
		x = max(0, x - 1);
	}
	// for (int i = 0; i < n; i++) {
	// 	cerr << lcp[i] << ' ';
	// }
	// cerr << '\n';
	// for (int i = 0; i < n; i++) {
	// 	cerr << sa[i] << ' ';
	// }
	// cerr << '\n';
	ll ans = 0;
	{
		build(1, 0, n - 1);
		vector<pair<int, int>> st;
		st.push_back({-1e9, -1});
		for (int i = 1; i < n; i++) {
			ans = max(ans, get(1, 0, n - 1, 0, i - 1) + sa[i]);
			int lst = i - 1;
			while (lcp[i] <= st.back().first) {
				upd(1, 0, n - 1, st.back().second, lst, -1ll * st.back().first * (st.back().first + 1));
				lst = st.back().second - 1;
				st.pop_back();
			}
			upd(1, 0, n - 1, lst + 1, i, 1ll * lcp[i] * (lcp[i] + 1));
			st.push_back({lcp[i], lst + 1});
		}
	}
	{
		build(1, 0, n - 1);
		vector<pair<int, int>> st;
		st.push_back({-1e9, n});
		for (int i = n - 1; i >= 0; i--) {
			if (i != n - 1) {
				ans = max(ans, get(1, 0, n - 1, i + 1, n - 1) + sa[i]);
			}
			int lst = i + 1;
			int lc = (i == 0 ? 0 : lcp[i - 1]);
			while (lc <= st.back().first) {
				upd(1, 0, n - 1, lst, st.back().second, -1ll * st.back().first * (st.back().first + 1));
				lst = st.back().second + 1;
				st.pop_back();
			}
			upd(1, 0, n - 1, i, lst - 1, 1ll * lc * (lc + 1));
			st.push_back({lc, lst - 1});
		}
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> s)
		solve();
	return 0;
}