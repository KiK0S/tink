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
	const int MAXN = 10;
#else
	const int MAXN = 2001;
#endif

int n, k;
int dp[MAXN][MAXN];
int last[MAXN][MAXN];

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = 1e9;
			last[i][j] = i;
		}
	}
}

inline void solve() {
	init();
	for (int i = 0; i <= k; i++) {
		dp[0][i] = 0;
	}
	for (int j = 1; j <= k; j++) {
		int pnt = 1;
		for (int i = 1; i <= n; i++) {
			while (pnt < i && dp[i - pnt][j - 1] > dp[pnt - 1][j - 1] + 1) {
				pnt++;
			}
			dp[i][j] = min(dp[i][j - 1], max(dp[i - pnt][j - 1], dp[pnt - 1][j - 1] + 1));
		}
	}
	// for (int i = 0; i <= n; i++) {
	// 	for (int j = 0; j <= k; j++) {
	// 		cerr << dp[i][j] << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	if (dp[n][k] >= 1e9) {
		cout << "-1\n";
	}
	else {
		cout << dp[n][k];
	}
}

signed main() {
	#ifdef DEBUG
		freopen("H.in", "r", stdin);
		freopen("H.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}