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
	const int MAXN = 100;
#else
	const int MAXN = 1e6 + 10;
#endif

int n, m;
vector<pair<int, int>> g[MAXN];
int used[MAXN];
int path[MAXN];
pair<int, int> edge[MAXN];
int pnt = 0;
int ans = 0;
int out[MAXN];
int cycle[MAXN];

int dfs(int v, int p = -1, int c = 1) {
	used[v] = c;
	// cerr << "path\n";
	// for (auto it : path) {
	// 	cerr << it.first << ' ' << it.second << '\t';
	// }
	// cerr << '\n';
	for (auto I : g[v]) {
		int to = I.first;
		if (to == p) {
			continue;
		}
		path[pnt++] = I.second;
		if (used[to]) {
			// cerr << v << ' ' << to << '\n';
			if (abs(used[to] - used[v]) == 1) {
				ans = 1;
				return 1;
				// cerr << "A\n";
			}
			else if (!out[to]) {
				for (int i = pnt - 1; i >= 0; i--) {
					auto it = edge[path[i]];
					// cerr << it.first << ' ' << it.second << '\t';
					if (cycle[path[i]] || cycle[path[i] ^ 1]) {
						ans = 1;
						// cerr << "B\n";
						return 1;
					}
					cycle[path[i]] = 1;
					if (it.first == to) {
						break;
					}
				}
				// cerr << '\n';
			}
			pnt--;
			continue;
		}
		if (dfs(to, v, 3 - c)) return 1;
		pnt--;	
	}
	out[v] = 1;
	return 0;
}

inline void init() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		g[i].clear();
	}
	ans = 0;
	pnt = 0;
	for (int i = 0; i < 2 * m; i++) {
		edge[i] = make_pair(0, 0);
		cycle[i] = 0;
	}
	memset(used, 0, sizeof(int) * n);
	memset(out, 0, sizeof(int) * n);
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		edge[2 * i] = make_pair(a, b);
		edge[2 * i + 1] = make_pair(b, a);
		g[a].push_back({b, 2 * i});
		g[b].push_back({a, 2 * i + 1});
	}
	for (int i = 0; i < n; i++) {
		if (!out[i]) {
			// cerr << "call\n";
			if (dfs(i)) {
				cout << "YES\n";
				return;
			}
		}
	}
	cout << "NO\n";
	// if (ans) {
	// 	cout << "YES\n";
	// }
	// else {
	// 	cout << "NO\n";
	// }
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
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}