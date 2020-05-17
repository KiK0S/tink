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
	const int MAXN = 30;
#else
	const int MAXN = 2e5 + 10;
#endif

int u;
int n, m;
int d[510][260][260];
int fact[MAXN];
int inv[MAXN];
int MOD = 1e9 + 7;

int bp(int a, int n) {
	if (n == 0) {
		return 1;
	}
	if (n & 1) {
		return (1ll * a * bp(a, n - 1)) % MOD;
	}
	return bp((1ll * a * a) % MOD, n >> 1);
}

inline void init() {
	memset(d, 0, sizeof(d));
	fact[0] = 1;
	inv[0] = bp(fact[0], MOD - 2);
	for (int i = 1; i < MAXN; i++) {
		fact[i] = (1ll * fact[i - 1] * i) % MOD;
		inv[i] = bp(fact[i], MOD - 2);
	}
}


int binom(int n, int k) {
	// cerr << n << ' ' << k << '\n';
	return (1ll * fact[n] * ((1ll * inv[k] * inv[n - k]) % MOD)) % MOD;
}

inline void solve2() {
	d[0][0][0] = 1;
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k <= n; k++) {
				// cerr << dp[i][j][k] << ' ';
				d[i + 1][j][k] += d[i][j][k];
				d[i + 1][j][k] %= MOD;
				d[i + 1][j][k + 1] += d[i][j][k];
				d[i + 1][j][k + 1] %= MOD;
				if (j < k) {
					d[i + 1][j + 1][k] += d[i][j][k];
					d[i + 1][j + 1][k] %= MOD;
					d[i + 1][j + 1][k + 1] += d[i][j][k];
					d[i + 1][j + 1][k + 1] %= MOD;	
				}
			}
		}
	}
	cout << d[m][n][n] << '\n';
}

inline void solve() {
	init();
	if (u == 0) {
		solve2();
		return;
	}
	cout << (((1ll * binom(2 * n, n) * binom(m, 2 * n)) % MOD) * bp(n + 1, MOD - 2)) % MOD << '\n';
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
	while (cin >> m >> n >> u)
		solve();
	return 0;
}