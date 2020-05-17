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
#define int ll

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXS = 15;
#else
	const int MAXN = 305;
	const int MAXS = 2000;
#endif


int n, m, s;
int g[MAXN][MAXN];
int dp[MAXN][MAXS];
int backpack[MAXS];
int pref[MAXS];
ll ans;

inline void init() {
	ans = 0ll;
	s = min(s, MAXS - 1);
	memset(dp, 0, sizeof(dp));
}


inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			if (c == '.') {
				g[i][j] = 1;
			}
			else {
				g[i][j] = 2;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		memset(backpack, 0, sizeof(backpack));
		for (int j = 0; j < m; j++) {
			{	// update dp[j]
				int sum = 0;
				for (int k = i - 1; k >= 0; k--) {
					sum += g[k][j];
					dp[j][sum]--;
				}
				sum = 0;
				for (int k = i; k < n; k++) {
					sum += g[k][j];
					dp[j][sum]++;
				}				
			}
			{	// update backpack
				int sum = 0;
				for (int k = j - 1; k >= 0; k--) {
					sum += g[i][k];
					backpack[sum]--;
				}
				sum = 0;
				for (int k = j; k < m; k++) {
					sum += g[i][k];
					backpack[sum]++;
				}
			}
			// for (int k = 0; k < MAXS; k++) {
			// 	cerr << dp[j][k] << ' ';
			// }
			// cerr << '\n';
			// for (int k = 0; k < MAXS; k++) {
			// 	cerr << backpack[k] << ' ';
			// }
			// cerr << '\n';
			{
				memset(pref, 0, sizeof(pref));
				for (int k = 0; k < MAXS; k++) {
					pref[k] = (k == 0 ? 0ll : pref[k - 1]) + backpack[k];
				}
				for (int k = 1; k < MAXS; k++) {
					int lft = s - k;
					if (lft + g[i][j] < 0 || lft + g[i][j] >= MAXS) {
						continue;
					}
					ans += dp[j][k] * pref[lft + g[i][j]];
				}
			}
			// cerr << '\n';
		}
	}
	cout << ans << '\n';
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
	while (cin >> n >> m >> s)
		solve();
	return 0;
}