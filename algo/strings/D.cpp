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
#include <numeric>
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 20;
#else
	const int MAXN = 6e5;
#endif

int n, m;

int val[MAXN];
int color[MAXN];
int cnt[MAXN];
int pos[MAXN];
int sa[MAXN];
int psa[MAXN];
int nc[MAXN];
int lcp[MAXN];

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

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		val[i]++;
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
		if (pos[i] == n - 1) {
			x = 0;
			lcp[pos[i]] = -1;
			continue;
		}
		while (max(i, sa[pos[i] + 1]) + x < n && val[i + x] == val[sa[pos[i] + 1] + x]) {
			x++;
		}
		lcp[pos[i]] = x;
		x = max(0, x - 1);
	}
	vector<pair<int, int>> ls;
	vector<pair<int, int>> rs;
	ls.push_back({-1e9, -1});
	rs.push_back({-1e9, n});
	vector<int> dpl(n);
	vector<int> dpr(n);
	ll ans = n - 1;
	for (int i = 0; i < n; i++) {
		int r = i;
		while (ls.size() && ls.back().first >= lcp[i]) {
			r = ls.back().second;
			ls.pop_back();
		}
		ls.push_back({lcp[i], r});
		dpl[i] = r;
	}
	for (int i = n - 1; i >= 0; i--) {
		int l = i;
		while (rs.size() && rs.back().first >= lcp[i]) {
			l = rs.back().second;
			rs.pop_back();
		}
		rs.push_back({lcp[i], l});
		dpr[i] = l;
	}
	int len = n - 1;
	int ps = 0;
	for (int i = 0; i < n; i++) {
		if (ans < 1ll * lcp[i] * (dpr[i] - dpl[i] + 2)) {
			ans = 1ll * lcp[i] * (dpr[i] - dpl[i] + 2);
			len = lcp[i];
			ps = sa[dpl[i]];
		}
	}
	cout << ans << '\n' << len << '\n';
	for (int i = ps; i < ps + len; i++) {
		cout << val[i] - 1 << ' ';
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
	while (cin >> n >> m)
		solve();
	return 0;
}