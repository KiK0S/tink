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
#include <complex>
using namespace std;

typedef long long ll;
#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 2e4 + 1;
#endif

const int MOD = 1e9 + 7;

int n, m, k;

int g[MAXN][MAXN];

inline void init() {
	assert(n < MAXN && m < MAXN);
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			g[i][j] = (1ll * i * m + j + 1) % MOD;
		}
	}
	for (int i = 0; i < k; i++) {
		char c;
		int x, y;
		cin >> c >> x >> y;
		x--;
		if (c == 'R') {
			for (int j = 0; j < m; j++) {
				g[x][j] = (1ll * g[x][j] * y) % MOD;
			}
		}
		else {
			for (int j = 0; j < n; j++) {
				g[j][x] = (1ll * g[j][x] * y) % MOD;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ans += g[i][j];
			ans %= MOD;
		}
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("Bs.in", "r", stdin);
		freopen("Bs.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> k)
		solve();
	return 0;
}