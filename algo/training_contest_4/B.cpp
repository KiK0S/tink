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
	const int MAXN = 10;
#else
	const int MAXN = 302;
#endif

int n, m;
char g[MAXN][MAXN];
pair<int, bitset<MAXN>> dp[MAXN][MAXN];
pair<int, bitset<MAXN>> ndp[MAXN][MAXN];
// int pre[MAXN][MAXN][MAXN];
int sy = -1, sx = -1;

inline void init() {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			cin >> g[i][j];
			if (g[i][j] == 'M') {
				sy = j;
				sx = i;
			}
		}
	}
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j].first = -1;
			ndp[i][j].first = -1;
		}
	}
}

bool check (int _a, int _b, bitset<MAXN> &a, bitset<MAXN> &b) {
	// cerr << _a << ' ' << _b << '\n';
	// cerr << a << ' ' << b << '\n';
	if (_b == -1) {
		return 0;
	}
	if (_a <= 0) {
		return 1;
	}
	if (_a != _b) {
		return _a < _b;
	}
	// cerr << a << ' ' << b << '\n';
	int pos = (a ^ b)._Find_first();
	return a[pos] < b[pos];
}

void relax(int tx, int ty, int x, int y, int k) {
	if (ty < 0) {
		return;
	}
	if (ty == m) {
		return;
	}
	if (g[x][y] == '*') {		
		return;
	}
	if (dp[y][k].first == -1) {
		return;
	}
	if (g[x][y] == '.' || g[x][y] == 'M') {
		if (check(ndp[ty][k].first, dp[y][k].first, ndp[ty][k].second, dp[y][k].second)) {
			ndp[ty][k] = dp[y][k];
			// pre[tx][ty][k] = y;
		}
	}
	if (g[x][y] == '(') {
		dp[y][k].second[dp[y][k].first] = 1;
		dp[y][k].first++;
		if (check(ndp[ty][k + 1].first, dp[y][k].first, ndp[ty][k + 1].second, dp[y][k].second)) {
			ndp[ty][k + 1] = dp[y][k];
			// pre[tx][ty][k + 1] = y;
		}
		dp[y][k].first--;
		dp[y][k].second[dp[y][k].first] = 0;
	}
	if (g[x][y] == ')' && k > 0) {
		dp[y][k].first++;
		if (check(ndp[ty][k - 1].first, dp[y][k].first, ndp[ty][k - 1].second, dp[y][k].second)) {
			ndp[ty][k - 1] = dp[y][k];
			// pre[tx][ty][k + 1] = y;
		}
		dp[y][k].first--;
	}
}

inline void solve() {
	init();
	dp[sy][0] = make_pair(0, bitset<MAXN>());
	int _ans = 0;
	bitset<MAXN> ans;
	for (int x = 0; x < n; x++) {
	// 	for (int i = 0; i <= n; i++) {
	// 	for (int k = 0; k < m; k++) {
	// 		cerr << dp[k][i].first << ' ';
	// 	}
	// 	cerr << '\n';
	// }
		for (int k = 0; k + 1 < n; k++) {
			for (int y = 0; y < m; y++) {
				if (k == 0) {
					if (check(_ans, dp[y][k].first, ans, dp[y][k].second)) {
						ans = dp[y][k].second;
						_ans = dp[y][k].first;
					}
				}
				relax(x + 1, y, x, y, k);
				relax(x + 1, y + 1, x, y, k);
				relax(x + 1, y - 1, x, y, k);
			}
		}
		for (int j = 0; j < m; j++) {
			for (int k = 0; k + 1 < n; k++) {
				swap(dp[j][k], ndp[j][k]);
				ndp[j][k] = make_pair(-1, bitset<MAXN>());
			}
		}
	}	
	// for (int i = 0; i <= n; i++) {
	// 	for (int k = 0; k < m; k++) {
	// 		cerr << dp[k][i].first << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	// int fx = n, fy = 0;
	for (int i = 0; i < m; i++) {
		if (check(_ans, dp[i][0].first, ans, dp[i][0].second)) {
			ans = dp[i][0].second;
			_ans = dp[i][0].first;
			// cerr << _ans << ' ' << ans << '\n';
			// fx = n;
			// fy = i;
		}
	}
	if (_ans == 0) {
		cout << "-1\n";
		return;
	}
	cout << _ans << '\n';
	for (int i = 0; i < _ans; i++) {
		if (ans[i]) {
			cout << '(';
		}
		else {
			cout << ')';
		}
	}
	// cout << ans << '\n';
	// int bal = 0;
	// string res;
	// if (dp[fx][fy][0] < 0) {
	// 	cout << "-1\n";
	// 	return;
	// }
	// cout << dp[fx][fy][0] << '\n';
	// while (fx != sx || fy != sy) {
	// 	// cerr << fx << ' ' << fy << ' ' << bal << '\n';
	// 	fy = pre[fx][fy][bal];
	// 	fx--;
	// 	if (g[fx][fy] == '(') {
	// 		bal--;
	// 	}
	// 	if (g[fx][fy] == ')') {
	// 		bal++;
	// 	}
	// 	if (g[fx][fy] == '(' || g[fx][fy] == ')') {
	// 		res.push_back(g[fx][fy]);
	// 	}
	// }
	// reverse(res.begin(), res.end());
	// cout << res << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}