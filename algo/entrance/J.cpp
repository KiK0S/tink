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
	const int MAXN = 1e5;
#endif

#define int ll

int n, s, t;

vector<pair<int, int>> g[MAXN][2];
int dist[MAXN][2];
int used[MAXN][2];
int dp[MAXN][2];
set<pair<pair<int, int>, int>> u;
bool can[MAXN][2];

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < 2; j++) {
			g[i][j].clear();
			dp[i][j] = -1e9;
			dist[i][j] = 1e9;
		}
	}
	s--, t--;
}

void dfs(int v, int type) {
	if (can[v][type]) {
		return;
	}
	can[v][type] = 1;
	for (auto to : g[v][type]) {
		if (dist[to.first][type] < dist[v][type]) {
			dfs(to.first, type ^ 1);
		}
	}
}

inline void solve() {
	init();
	dp[t][0] = dp[t][1] = 0;
	for (int j = 0; j < 2; j++) {
		int m;
		cin >> m;
		for (int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			a--, b--;
			g[a][j].push_back({b, c});
			g[b][j].push_back({a, c});
		}
		dist[t][j] = 0;
		for (int i = 0; i < n; i++) {
			int cur = -1;
			for (int k = 0; k < n; k++) {
				if (used[k][j]) {
					continue;
				}
				if (cur == -1 || dist[k][j] < dist[cur][j]) {
					cur = k;
				}
			}
			if (cur == -1) {
				break;
			}
			used[cur][j] = 1;
			for (auto to : g[cur][j]) {
				dist[to.first][j] = min(dist[to.first][j], dist[cur][j] + to.second);
			}
		}
	}
	dfs(s, 0);
	memset(used, 0, sizeof(used));
	queue<pair<int, int>> q;
	q.push({t, 0});
	q.push({t, 1});
	while (!q.empty()) {

		int v = q.front().first;
		int type = q.front().second;
		if (clock() * 1.0 / CLOCKS_PER_SEC > 2) {
			if (can[v][type]) {
				cout << "-1\n";
				return;
			}
		}
		if (clock() * 1.0 / CLOCKS_PER_SEC > 3) {
			break;
		}
		q.pop();
		type ^= 1;
		for (auto to : g[v][type]) {
			if (dist[to.first][type] > dist[v][type]) {
				if (dp[to.first][type] < dp[v][type ^ 1] + to.second) {
					// if (u.count({{to.first, v}, type}) && u[to.first]) {
					// 	continue;
					// }
					// u.insert({{to.first, v}, type});
					dp[to.first][type] = dp[v][type ^ 1] + to.second;
					q.push({to.first, type});
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			if (dp[i][j] < 0 && can[i][j]) {
				cout << "-1\n";
				return;
			}
		}
	}
	if (dp[s][0] >= 1e10) {
		cout << "-1\n";
		return;
	}
	cout << dp[s][0] << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("J.in", "r", stdin);
		freopen("J.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> s >> t)
		solve();
	return 0;
}