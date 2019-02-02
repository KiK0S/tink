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
	const int MAXN = 7;
	const int MAXK = 10;
#else
	const int MAXN = 1e2 + 10;
	const int MAXK = 1e3 + 10;
#endif

#define int ll

int n, m, q;
int g[MAXN][MAXN];
int buy[MAXN][MAXK];
int sell[MAXN][MAXK];
int G[MAXN][MAXN];
int p[MAXN][MAXN];

int INF = 1e9 + 10;

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j= 0; j < MAXN; j++) {
			g[i][j] = INF;
		}
		g[i][i] = 0;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < q; j++) {
			cin >> buy[i][j] >> sell[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g[a][b] = c;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int cost = 0;
			for (int k = 0; k < q; k++) {
				if (buy[i][k] != -1 && sell[j][k] != -1) {
					cost = max(cost, sell[j][k] - buy[i][k]);
				}
			}
			G[i][j] = cost;
		}
	}
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		cerr << g[i][j] << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	// cerr << '\n';
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		cerr << G[i][j] << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	// cerr << '\n';
	int l = 0;
	int r = 1e9 + 10;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		// cerr << mid << '\n';
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				p[i][j] = mid * g[i][j] - G[i][j];
				// cerr << p[i][j] << ' ';
			}
			p[i][i] = INF;
			// cerr << '\n';
		}
		// cerr << '\n';
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					p[i][j] = min(p[i][j], p[i][k] + p[k][j]);
				}
			}
		}
		bool ok = 0;
		// for (int i = 0; i < n; i++) {
		// 	for (int j = 0; j < n; j++) {
		// 		cerr << p[i][j] << ' ';
		// 	}
		// 	cerr << '\n';
		// }
		// cerr << '\n';
		for (int i = 0; i < n; i++) {
			if (p[i][i] <= 0) {
				ok = 1;
				break;
			}
		}
		if (ok) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	cout << l << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> q)
		solve();
	return 0;
}