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
	const int MAXN = 15;
#endif

int n, m;
int g[MAXN][MAXN];

int dp[1 << MAXN][MAXN][MAXN];

inline void init() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] = 0;
		}
	}
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				dp[i][j][k] = 0;
			}
		}
	}
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a][b] = g[b][a] = 1;
	}
	for (int i = 0; i < n; i++) {
		dp[1 << i][i][i] = 1;
	}
	int ans = 0;
	for (int start = 0; start < n; start++) {
		for (int mask = 1; mask < (1 << n); mask++) {
			for (int last = 0; last < n; last++) {
				if (!(mask & (1 << last))) {
					continue;
				}
				if (!dp[mask][last][start]) {
					continue;
				}
				if (g[last][start] && __builtin_popcount(mask) > 3 && __builtin_popcount(mask) % 2 == 0) {
					// cerr << mask << '\n';
					ans = 1;
				}
				for (int to = 0; to < n; to++) {
					if (mask & (1 << to)) {
						continue;
					}
					if (!g[last][to]) {
						continue;
					}
					dp[mask | (1 << to)][to][start] = 1;
				}
			}
		}
	}
	// cerr << '\n';
	if (ans) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("Bs.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}