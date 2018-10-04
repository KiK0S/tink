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
	const int MAXN = 2e6;
#endif
#define int ll

int n, m;
int x, y;
int cnt1[MAXN];
int cnt2[MAXN];
int dp[MAXN];
int ans = 0;

inline void init() {
	memset(cnt1, 0, sizeof(cnt1));
	memset(cnt2, 0, sizeof(cnt2));
	memset(dp, 0, sizeof(dp));
}

inline void solve(int n, int m) {
	init();
	// cerr << n << ' ' << m << '\n';
	for (int i = 1; i < n; i++) {
		for (int j = 1; j * i < n; j++) {
			cnt1[i]++;
		}
		// cerr << cnt1[i] << ' ';
	}
	// cerr << '\n';
	for (int i = 1; i < m; i++) {
		for (int j = 1; j * i < m; j++) {
			cnt2[i]++;
		}
		// cerr << cnt2[i] << ' ';
	}
	// cerr << '\n';
	for (int i = min(n, m) - 1; i > 0; i--) {
		dp[i] = cnt1[i] * cnt2[i];
		for (int j = 2; i * j < min(n, m); j++) {
			dp[i] -= dp[i * j];
		}
		ans += dp[i] * i;
		// cerr << i << ' ' << dp[i] << '\t';
	}
	// cerr << '\n';
	// cerr << ans << '\n';
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
	while (cin >> m >> n >> x >> y) {
		solve(x, y);
		solve(x, m - y + 1);
		solve(n - x + 1, y);
		solve(n - x + 1, m - y + 1);
		ans += x * (x - 1) / 2;
		// cerr << ans << '\n';
		ans += (n - x) * (n - x + 1) / 2;
		// cerr << ans << '\n';
		ans += y * (y - 1) / 2;
		// cerr << ans << '\n';
		ans += (m - y) * (m - y + 1) / 2;
		// cerr << ans << '\n';
		cout << ans << '\n';
	}
	return 0;
}