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
	const int MAXK = 5;
#else
	const int MAXN = 5e4 + 100;
	const int MAXK = 105;
#endif

#define int ll

int n, k;
int pos[MAXN];
double dp[MAXN][MAXK];
int opt[MAXN][MAXK];
int sqr[MAXN];
int pref[MAXN];

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXK; j++) {
			dp[i][j] = 4e18;
		}
	}
	sqr[0] = pref[0] = 0;
}

double get(int _l, int _r) {
	assert(_l <= _r);
	ll sum_sqr = sqr[_r] - (_l == 0 ? 0ll : sqr[_l - 1]);
	ll sum = pref[_r] - (_l == 0 ? 0ll : pref[_l - 1]);
	// sum = 0;
	// for (int i = _l; i <= _r; i++) {
	// 	sum += pos[i];
	// }
	int cnt = _r - _l + 1;
	double crd = sum * 1.0 / cnt;
	// double ans = 0;
	// for (int i = _l; i <= _r; i++) {
	// 	ans += (crd - pos[i]) * (crd - pos[i]);
	// }
	// return ans;
	// sum * res + cnt * res * res -> max
	// 2 * cnt * res + sum = 0
	// res = -sum / 2 / cnt
	// cerr << sum_sqr << ' ' << sum << ' ' << -sum / 2.0 / cnt << '\n';
	// cerr << _l << ' ' << _r << " - " << sum_sqr - sum * sum / 2.0 / cnt + sum * sum / 4.0 / cnt << '\n';
	return sum_sqr - 2 * crd * sum + crd * crd * cnt;
}

void calc(int tl, int tr, int l, int r, int _k) {
	if (tl > tr) {
		return;
	}
	int tm = (tl + tr) >> 1;
	dp[tm][_k] = dp[tm - 1][_k - 1];
	opt[tm][_k] = tm - 1;
	for (int i = l; i <= min(r, tm - 1); i++) {
		if (dp[tm][_k] > dp[i][_k - 1] + get(i + 1, tm)) {
			dp[tm][_k] = dp[i][_k - 1] + get(i + 1, tm);
			opt[tm][_k] = i;
		}
	}
	if (tl == tr) {
		return;
	}
	calc(tl, tm - 1, l, opt[tm][_k], _k);
	calc(tm + 1, tr, opt[tm][_k], r, _k);
}

inline void solve() {
	init();
	for (int i = 1; i <= n; i++) {
		cin >> pos[i];
	}
	sort(pos + 1, pos + n + 1);
	for (int i = 1; i <= n; i++) {
		sqr[i] = pos[i] * pos[i] + sqr[i - 1];
		pref[i] = pref[i - 1] + pos[i];
	}
	dp[0][0] = 0;
	for (int i = 1; i <= k; i++) {
		calc(1, n, 0, n, i);
	}
	// for (int i = 1; i <= k; i++) {
	// 	for (int j = 1; j <= n; j++) {
	// 		dp[j][i] = min(dp[j][i], dp[j][i - 1]);
	// 		for (int l = 0; l < j; l++) {
	// 			dp[j][i] = min(dp[j][i], dp[l][i - 1] + get(l + 1, j));
	// 		}
	// 	}
	// }
	cout << fixed << setprecision(10) << dp[n][k] << '\n';
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
	while (cin >> n >> k)
		solve();
	return 0;
}