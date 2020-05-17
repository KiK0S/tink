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
	const int MAXN = 101;
#endif

int dp[MAXN][MAXN];
int n, m, k, f;
int MOD = 998244353;
int cnt_ok = 0;
int cnt_bad = 0;
	
vector<vector<int>> operator *(vector<vector<int>> a, vector<vector<int>> b) {
	int n = a.size();
	int m = b[0].size();
	int k = b.size();
	assert(k == a[0].size());
	vector<vector<int>> c(n, vector<int> (m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int t = 0; t < k; t++) {
				c[i][j] += (1ll * a[i][t] * b[t][j]) % MOD;
				c[i][j] %= MOD;
			}
		}
	}
	return c;
}

vector<vector<int>> bp(vector<vector<int>> a, int n) {
	if (n == 0) {
		vector<vector<int>> E(a.size(), vector<int>(a.size()));
		for (int i = 0; i < a.size(); i++) {
			E[i][i] = 1;
		}
		return E;
	}
	if (n & 1) {
		return a * bp(a, n - 1);
	}
	return bp(a * a, n >> 1);
}

inline void init() {
	for (int mask = 0; mask < (1 << m); mask++) {
		if (__builtin_popcount(mask) < f) {
			cnt_bad++;
		}
		else {
			cnt_ok++;
		}
	}
	memset(dp, 0, sizeof(dp));
}

inline void solve() {
	init();
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = i - 1; j >= max(i - k, 0); j--) {
			dp[i][j] += (1ll * dp[i - 1][j] * cnt_bad) % MOD;
			dp[i][j] %= MOD;
		}
		for (int j = i - 1; j >= max(i - k, 0); j--) {
			dp[i][i] += (1ll * dp[i - 1][j] * cnt_ok) % MOD;
			dp[i][i] %= MOD;
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			cerr << dp[i][j] << ' ';
		}
		cerr << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("Cs.in", "r", stdin);
		freopen("Cs.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> k >> f)
		solve();
	return 0;
}