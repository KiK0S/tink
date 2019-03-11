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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 1e3 + 10;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m;
int g[MAXN][MAXN];
int ans[MAXN][MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> g[i][j];
			g[i][j] = 1 - g[i][j];
		}
	}
	for (int l = 0; l < n; l++) {
		for (int r = l; r < n; r++) {
			for (int t = 0; t < m; t++) {
				bool ok = 1;
				for (int b = t; b < m; b++) {
					for (int k = l; k <= r; k++) {
						if (g[k][b] == 0) {
							ok = 0;
							break;
						}
					}
					if (ok) {
						ans[l][r] = max(ans[l][r], (r - l + 1) * (b - t + 1));
					}
				}
			}
		}
	}
	for (int l = n - 1; l >= 0; l--) {
		for (int r = l; r < n; r++) {
			if (r > l) {
				ans[l][r] = max(ans[l][r], ans[l][r - 1]);
				ans[l][r] = max(ans[l][r], ans[l + 1][r]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << ans[i][j] << ' ';
		}
		cout << '\n';
	}
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
	while (cin >> n >> m)
		solve();
	return 0;
}