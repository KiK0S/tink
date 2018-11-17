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
	const int MAXN = 10001;
#endif


int dp[1 << 20][20];
int d[MAXN];
vector<int> g[MAXN];
int n, m;

int get(int mask, int last, int md2 = 1) {
	// cerr << mask << ' ' << last << '\n';
	if (dp[mask][last] != -1) {
		return dp[mask][last];
	}
	bool fl = 0;
	for (auto to : g[last]) {
		if (mask & (1 << to)) {
			continue;
		}
		fl = 1;
		if (!get(mask | (1 << to), to, md2 ^ 1)) {
			return dp[mask][last] = 1;
		}
	}
	if (fl) {
		return dp[mask][last] = 0;
	}
	dp[mask][last] = 0;
	// cerr << md2 << ' ' << last << ' ' << dp[mask][last] << '\n';
	return dp[mask][last];
}

void dfs(int v, int p = -1, int md2 = 1) {
	// cerr << v << '\n';
	d[v] = -2;
	bool fl = 0;
	for (auto to : g[v]) {
		if (to == p || d[to] == -2) {
			continue;
		}
		fl = 1;
		// assert(d[to] == -1);
		dfs(to, v, md2 ^ 1);
		// cerr << to << ' ' << d[to] << '\n';
		if (d[to] == 0) {
			d[v] = 1;
			return;
		}
	}
	if (fl) {
		if (d[v] != 1) {
			d[v] = 0;
		}
		return;
	}
	d[v] = 0;
}

inline void init() {
	memset(dp, -1, sizeof(dp));
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		b += n;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	if (n <= 10) {
		for (int i = 0; i < n; i++) {
			if (!get(1 << i, i)) {
				cout << "Mirko\n";
			}
			else {
				cout << "Slavko\n";
			}
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			memset(d, -1, sizeof(d));
			dfs(i);
			// cerr << d[i] << ' ';
			if (!d[i]) {
				cout << "Mirko\n";
			}
			else {
				cout << "Slavko\n";
			}
		}
		// for (int i = 0; i < 2 * n; i++) {
		// 	cerr << d[i] << ' ';
		// }
		// cerr << '\n';
	}

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
	while (cin >> n >> m)
		solve();
	return 0;
}