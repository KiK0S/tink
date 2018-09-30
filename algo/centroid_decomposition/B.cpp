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
	const int MAXLOG = 5;
#else
	const int MAXN = 2e5;
	const int MAXLOG = 25;
#endif


int n;
int pre[MAXN];
vector<int> g[MAXN];
int used[MAXN];
vector<pair<int, int>> dist[MAXN];
int color[MAXN];
int h[MAXN][MAXLOG];
int lgr[MAXN];

inline int dfs(int v, int sz, int p, int &c) {
	if (used[v]) {
		return 0;
	}
	int cnt = 1;
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		cnt += dfs(to, sz, v, c);
	}
	if (c == -1 && (cnt * 2 >= sz || p == -1)) {
		c = v;
	}
	return cnt;
}

inline void calc_h(int v, int p, int lg) {
	h[v][lg] = (p == -1 ? 0 : h[p][lg] + 1);
	for (auto to : g[v]) {
		if (used[to] || to == p) {
			continue;
		}
		calc_h(to, v, lg);
	}
}

inline int find_centroid(int x, int sz, int lg) {
	int c = -1;
	dfs(x, sz, -1, c);
	used[c] = 1;
	lgr[c] = lg;
	calc_h(c, -1, lg);
	for (auto to : g[c]) {
		if (used[to]) {
			continue;
		}
		pre[find_centroid(to, sz / 2, lg + 1)] = c;
	}
	return c;
}

inline void init() {
	memset(used, 0, sizeof(used));
	memset(pre, -1, sizeof(pre));
	for (int i = 0; i < MAXN; i++) {
		dist[i].emplace_back(MAXN, 1e9);
	}
}

inline void solve() {
	init();
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		g[i].push_back(p);
		g[p].push_back(i);
	}
	find_centroid(0, n, 0);
	for (int i = 0; i < n; i++) {
		cin >> color[i];
		int v = i;
		int cur = lgr[v];
		assert(cur < MAXLOG);
		while (v != -1) {
			dist[v].emplace_back(color[i], h[i][cur]);
			cur--;
			v = pre[v];
		}	
		assert(cur == -1);
		// cerr << '\n';
	}
	for (int i = 0; i < n; i++) {
		sort(dist[i].begin(), dist[i].end());
		// for (auto it : dist[i]) {
		// 	cerr << it.first << ' ' << it.second << '\t';
		// }
		// cerr << '\n';
	}
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int v, b;
		cin >> v >> b;
		int start = v;
		int ans = 1e9;
		int cur = lgr[v];
		assert(cur < MAXLOG);
		while (v != -1) {
			pair<int, int> q = *lower_bound(dist[v].begin(), dist[v].end(), make_pair(b, -MAXN));
			if (q.first == b) {
				ans = min(ans, h[start][cur] + q.second);
			}
			cur--;
			v = pre[v];
		}
		assert(cur == -1);
		if (ans > n) {
			cout << "-1 ";
		}
		else {
			cout << ans << ' ';
		}
	}
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
	while (cin >> n)
		solve();
	return 0;
}