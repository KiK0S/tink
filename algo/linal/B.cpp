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
	const int MAXN = 2019;
#endif
#define double long double
int n, k;
double p;
double dp[MAXN][MAXN];

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = 0;
		}
	}
}

inline void solve() {
	init();
	dp[0][0] = 1;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			dp[i + 1][j] += dp[i][j] * (1 - p);
			dp[i + 1][j + 1] += dp[i][j] * p;
		}
		dp[i + 1][n] += dp[i][n];
	}
	double ans = 0;
	for (int i = 0; i <= n; i++) {
		ans += i * dp[k][i];
	}
	cout << fixed << setprecision(10) << ans << '\n';
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
	while (cin >> n >> p >> k)
		solve();
	return 0;
}