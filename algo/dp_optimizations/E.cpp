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
	const int MAXN = 15;
	const int MAXK = 4;
#else
	const int MAXN = 1e5 + 10;
	const int MAXK = 21;
#endif


const ll INF = 1e10;

int n, k;
int val[MAXN];
ll dp[MAXN][MAXK];
int opt[MAXN][MAXK];
ll cnt[MAXN];
ll current_ans;
int pntl;
int pntr;

struct params {
	int tl, tr, l, r, layer, level;
	params() {}
	params(int a, int b, int c, int d, int e, int f) {
		tl = a, tr = b, l = c, r = d, layer = e, level = f;
	}
};

queue<params> q;


inline ll get(int l, int r) {
	while (pntr <= r) {
		current_ans += cnt[val[pntr]];
		cnt[val[pntr]]++;
		pntr++;
	}
	while (pntl < l) {
		current_ans -= cnt[val[pntl]] - 1;
		cnt[val[pntl]]--;
		pntl++;
	}
	return current_ans;
}

inline void calc(params p) {
	if (p.tl > p.tr) {
		return;
	}
	int tm = (p.tl + p.tr) >> 1;
	for (int i = p.l; i <= min(p.r, tm - 1); i++) {
		if (dp[tm][p.layer] > dp[i][p.layer - 1] + get(i + 1, tm)) {
			dp[tm][p.layer] = dp[i][p.layer - 1] + get(i + 1, tm);
			opt[tm][p.layer] = i;
		}
	}
	params L(p.tl, tm - 1, p.l, opt[tm][p.layer], p.layer, p.level + 1);	
	params R(tm + 1, p.tr, opt[tm][p.layer], p.r, p.layer, p.level + 1);	
	q.push(L);
	q.push(R);
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXK; j++) {
			dp[i][j] = INF;
		}
	}
}

inline void clear() {
	current_ans = 0;
	memset(cnt, 0, sizeof(ll) * (n + 1));
	pntr = 0;
	pntl = 0;
}

inline void solve() {
	init();
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
	}
	dp[0][0] = 0;
	for (int i = 1; i <= k; i++) {
		int last_level = -1;
		dp[0][i] = 0;
		q.emplace(1, n, 0, n, i, 0);
		while (q.size()) {
			params cur = q.front();
			q.pop();
			if (cur.level != last_level) {
				last_level = cur.level;
				clear();
			}
			calc(cur);
		}
	}
	cout << dp[n][k] << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}