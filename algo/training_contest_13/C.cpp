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
	const int MAXN = 1e5;
#endif

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
}

inline void solve() {
	init();
	if (k > 100) {
		vector<vector<int>> dp(n + 1, vector<int>(k));
		dp[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j < k; j++) {
				dp[i][j] = (dp[i - 1][j - 1] * 1ll * cnt_bad) % MOD;
			}
			for (int j = 0; j < k; j++) {
				dp[i][0] += (dp[i - 1][j] * 1ll * cnt_ok) % MOD;
				if (dp[i][0] >= MOD) {
					dp[i][0] -= MOD;
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < k; i++) {
			ans += dp[n][i];
			if (ans >= MOD) {
				ans -= MOD;
			}
		}
		cout << ans << '\n';
		return;
	}

	vector<vector<int>> matr(k, vector<int>(k));
	// cerr << cnt_ok << '\n';
	for (int i = 1; i < k; i++) {
		matr[i][i - 1] = cnt_bad;
	}
	for (int i = 0; i < k; i++) {
		matr[0][i] = cnt_ok;
	}
	// for (int i = 0; i < k; i++) {
	// 	for (int j = 0; j < k; j++) {
	// 		cerr << matr[i][j] << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	vector<vector<int>> start(k, vector<int>(1));
	start[0][0] = 1;
	matr = bp(matr, n);
	// for (int i = 0; i < k; i++) {
		// for (int j = 0; j < k; j++) {
		// 	cerr << matr[i][j] << ' ';
		// }
		// cerr << '\n';
	// }
	matr = matr * start;
	// for (int i = 0; i < matr.size(); i++) {
	// 	for (auto it : matr[i]) {
	// 		cerr << it << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	int ans = 0;
	for (int i = 0; i < k; i++) {
		ans += matr[i][0];
		ans %= MOD;
	}
	cout << ans;
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> m >> n >> k >> f)
		solve();
	return 0;
}