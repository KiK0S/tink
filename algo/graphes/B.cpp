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
	const int MAXN = 3e5;
#endif
#define int ll
int n, m, s, t, S, T;
const int INF = 1e18;
vector<pair<int, int>> g[MAXN];
int dist[MAXN][5];
vector<int> G[MAXN];
int dp[MAXN];
vector<int> topsort;
int used[MAXN];

void dijkstra(int start, int q) {
	dist[start][q] = 0;
	set<pair<int, int>> st;
	for (int i = 0; i < n; i++) {
		st.insert({dist[i][q], i});
	}
	while (st.size()) {
		int v = (*st.begin()).second;
		st.erase(*st.begin());
		for (auto x : g[v]) {
			int to = x.first;
			int c = x.second;
			if (dist[to][q] > dist[v][q] + c) {
				st.erase({dist[to][q], to});
				dist[to][q] = dist[v][q] + c;
				st.insert({dist[to][q], to});
			}
		}
	}
}

inline void init() {
	s--, t--, S--, T--;
	for (int i = 0; i < MAXN; i++) {
		g[i].clear();
		G[i].clear();
		for (int j = 0; j < 4; j++) {
			dist[i][j] = INF;
		}
		dp[i] = INF;
		used[i] = 0;
	}
	topsort.clear();
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);		
	}
}


void dfs(int v) {
	used[v] = 1;
	for (auto to : G[v]) {
		if (!used[to]) {
			dfs(to);
		}
	}
	topsort.push_back(v);
}

inline void solve() {
	init();
	dijkstra(s, 0);
	dijkstra(S, 1);
	dijkstra(T, 2);
	dijkstra(t, 3);
	for (int i = 0; i < n; i++) {
		for (auto x : g[i]) {
			int to = x.first;
			int c = x.second;
			if (dist[t][0] == dist[i][0] + c + dist[to][3]) {
				G[i].push_back(to);
				// cerr << i << ' ' << to << '\n';
			}
		}
	}
	// for (int j = 0; j < 4; j++) {
	// 	for (int i = 0; i < n; i++) {
	// 		cerr << dist[i][j] << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	dfs(s);
	ll ans = dist[S][2];
	for (auto v : topsort) {
		dp[v] = dist[v][1];
		for (auto to : G[v]) {
			dp[v] = min(dp[v], dp[to]);
		}
		ans = min(ans, dist[v][2] + dp[v]);
	}
	for (int i = 0; i < MAXN; i++) {
		dp[i] = INF;
	}
	for (auto v : topsort) {
		dp[v] = dist[v][2];
		for (auto to : G[v]) {
			dp[v] = min(dp[v], dp[to]);
		}
		ans = min(ans, dist[v][1] + dp[v]);
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
	while (cin >> n >> m >> s >> t >> S >> T)
		solve();
	return 0;
}