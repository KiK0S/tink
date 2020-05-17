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

#define int ll

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 500;
#endif

int n, m, k;
int val[MAXN];
int dp[MAXN][MAXN];
const int INF = 1e18;

inline void init() {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			dp[i][j] = INF;
		}
	}
	dp[0][0] = 0;
}

int f(int id, int x) {
	if (x % k == k - 1) {
		return 0;
	}
	return val[id];
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	int ans = INF;
	// m = min(m, n);
	for (int i = 0; i <= m; i++) {
		init();
		for (int last = 0; last < n; last++) {
			for (int cnt = 0; cnt <= i; cnt++) {
				if (dp[last][cnt] == INF) {
					continue;
				}
				int id_left = last - cnt;
				int id_take = n - i + cnt;
				dp[last + 1][cnt] = min(dp[last + 1][cnt], dp[last][cnt] + f(last, id_left));
				if (cnt < i) {
					dp[last + 1][cnt + 1] = min(dp[last + 1][cnt + 1], dp[last][cnt] + f(last, id_take));
				}
			}
		}
		ans = min(ans, dp[n][i]);
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> k)
		solve();
	return 0;
}