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
	const int MAXN = 2;
#else
	const int MAXN = 20;
#endif

int n, k;
int dp1[1 << MAXN];
int pre1[1 << MAXN];
int dp2[1 << MAXN];
int pre2[1 << MAXN];
int can1[1 << MAXN];
int can12[1 << MAXN];
int can21[1 << MAXN];
int can2[1 << MAXN];
int g11[1 << MAXN];
int g12[1 << MAXN];
int g21[1 << MAXN];
int g22[1 << MAXN];

inline void init() {
	memset(dp2, 0, sizeof(dp2));
}

inline void solve() {
	init();
	int cnt = (1 << MAXN);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int c;
			cin >> c;
			if (i < MAXN) {
				if (j < MAXN) {
					g11[1 << i] |= c << j;
				}
				else {
					g12[1 << i] |= c << (j - MAXN);
				}
			}
			else {
				if (j < MAXN) {
					g21[1 << (i - MAXN)] |= c << j;
				}
				else {
					g22[1 << (i - MAXN)] |= c << (j - MAXN);
				}
			}
		}		
	}
	can1[0] = (1 << MAXN) - 1;
	can12[0] = (1 << MAXN) - 1;
	for (int mask = 1; mask < (1 << min(MAXN, n)); mask++) {
		can1[mask] = can1[mask & (mask - 1)] & g11[mask & -mask];
		can12[mask] = can12[mask & (mask - 1)] & g12[mask & -mask];
	}
	can2[0] = (1 << MAXN) - 1;
	can21[0] = (1 << MAXN) - 1;
	dp1[0] = 0;
	dp2[0] = 0;
	for (int mask = 1; mask < (1 << max(0, n - MAXN)); mask++) {
		can2[mask] = can2[mask & (mask - 1)] & g22[mask & -mask];
		can21[mask] = can21[mask & (mask - 1)] & g21[mask & -mask];
	}
	// for (int i = 0; i < (1 << MAXN); i++) {
	// 	cerr << can1[i];
	// }
	// cerr << '\n';
	// for (int i = 0; i < (1 << MAXN); i++) {
	// 	cerr << can2[i];
	// }
	// cerr << '\n';
	for (int mask = 0; mask < (1 << min(MAXN, n)); mask++) {
		for (int i = 0; i < min(n, MAXN); i++) {
			if (dp1[mask | (1 << i)] < dp1[mask]) {
				pre1[mask | (1 << i)] = mask;
				dp1[mask | (1 << i)] = dp1[mask];
			}
			if (!(mask & (1 << i)) && (can1[mask] & (1 << i))) {
				if (dp1[mask | (1 << i)] < dp1[mask] + 1) {
					pre1[mask | (1 << i)] = mask;
					dp1[mask | (1 << i)] = dp1[mask] + 1;
				}
			}
		}
	}
	for (int mask = 0; mask < (1 << max(0, n - MAXN)); mask++) {
		for (int i = 0; i < max(0, n - MAXN); i++) {
			if (dp2[mask | (1 << i)] < dp2[mask]) {
				pre2[mask | (1 << i)] = mask;
				dp2[mask | (1 << i)] = dp2[mask];
			}
			if (!(mask & (1 << i)) && (can2[mask] & (1 << i))) {
				if (dp2[mask | (1 << i)] < dp2[mask] + 1) {
					pre2[mask | (1 << i)] = mask;
					dp2[mask | (1 << i)] = dp2[mask] + 1;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < (1 << min(MAXN, n)); i++) {
		ans = max(ans, dp1[i] + dp2[can12[i]]);
	}
	double one = 1.0 * k / ans;
	cout << fixed << setprecision(10) << ans * (ans - 1) / 2 * one * one << '\n';
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