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
#else
	const int MAXN = 20;
#endif

#define int ll

int n;
int val[1 << MAXN];
int dp[1 << MAXN][MAXN];
int ans[1 << MAXN];

inline void init() {
	memset(ans, 0, sizeof(ans));
	memset(dp, 0, sizeof(dp));
}

inline void solve() {
	init();
	for (int i = 0; i < (1 << n); i++) {
		cin >> val[i];
	}
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
			if (mask & (1 << i)) {
				dp[mask][i] = (i == 0 ? ans[mask] : dp[mask][i - 1]) + (i == 0 ? ans[mask ^ (1 << i)] : dp[mask ^ (1 << i)][i - 1]);
			}
			else {
				dp[mask][i] = (i == 0 ? ans[mask] : dp[mask][i - 1]);
			}
		}
		ans[mask] = val[mask] - dp[mask][n - 1];
		for (int i = 0; i < n; i++) {
			dp[mask][i] += ans[mask];
		}
		// for (int i = 0; i < n; i++) {
		// 	if (mask & (1 << i)) {
		// 		dp[mask][i] = (i == 0 ? ans[mask] : dp[mask][i - 1]) + (i == 0 ? ans[mask ^ (1 << i)] : dp[mask ^ (1 << i)][i - 1]);
		// 	}
		// 	else {
		// 		dp[mask][i] = (i == 0 ? ans[mask] : dp[mask][i - 1]);
		// 	}
		// }
	}
	for (int i = 0; i < (1 << n); i++) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}