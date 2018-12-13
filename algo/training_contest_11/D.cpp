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
	const int MAXN = 111;
#else
	const int MAXN = 111;
#endif

int n;

int color[MAXN];
vector<pair<int, int>> dp[MAXN];
vector<int> g[MAXN];
int can[MAXN][MAXN];


void dfs(int v) {
	int mx = -1;
	for (auto to : g[v]) {
		dfs(to);
		if (mx == -1 || dp[to].size() > dp[mx].size()) {
			mx = to;
		}
	}
	if (mx != -1) {
		dp[v].swap(dp[mx]);
	}
	dp[v].push_back({color[v], color[v]});
	for (auto to : g[v]) {
		if (to == mx) {
			continue;
		}
		for (auto it : dp[to]) {
			dp[v].push_back(it);
		}
	}
	memset(can, 0, sizeof(can));
	can[color[v]][color[v]] = 1;
	for (int len = 2; len < MAXN; len++) {
		for (int l = 0; l + len - 1 < MAXN; l++) {
			int r = l + len - 1;
			for (auto it : dp[v]) {
				if (it.first != l) {
					continue;
				}
				if (it.second >= r) {
					continue;
				}
				if (can[it.second + 1][r]) {
					can[l][r] = 1;
				}
			}
			for (auto it : dp[v]) {
				if (it.second != r) {
					continue;
				}
				if (it.first <= l) {
					continue;
				}
				if (can[l][it.first- 1]) {
					can[l][r] = 1;
				}
			}
		}
	}
	dp[v].clear();
	// cerr << v << '\t';
	for (int l = color[v]; l >= 0; l--) {
		for (int r = color[v]; r < MAXN; r++) {
			if (can[l][r]) {
				// cerr << l << ' ' << r << '\t';
				dp[v].push_back({l, r});
			}
		}
	}
	// cerr << '\n';
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> color[i];
	}	
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
	}
	dfs(0);
	cout << dp[0].size() << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}