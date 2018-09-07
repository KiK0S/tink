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
	const int MAXN = 1e4 + 1;
#else
	const int MAXN = 1e4 + 1;
#endif

int n, k, a, b;
int dp[MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 1; i <= a; i++) {
		dp[i] = dp[i - 1];
		if (i >= b) {
			dp[i] = max(dp[i], dp[i - b] + 1);
		}
		if (i >= b * (k - 1)) {
			dp[i] = max(dp[i], dp[i - b * (k - 1)] + k);
		}
		if (i >= n * b) {
			dp[i] = max(dp[i], dp[i - n * b] + n + 1);
		}
	}
	cout << dp[a] << '\n';
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
	while (cin >> n >> k >> a >> b)
		solve();
	return 0;
}