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
	const int MAXN = 3e3;
#else
	const int MAXN = 2e3 + 10;
#endif
#define int ll
int n, s, t;
int m[2];

vector<pair<int, int>> g[MAXN][2];
int dist[MAXN][2];
int used[MAXN][2];

ll D[MAXN];

const int INF = 1e15;


inline void init() {
	s--, t--;
	for (int k = 0; k < 2; k++) {
		cin >> m[k];
		for (int i = 0; i < m[k]; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			a--, b--;
			g[a][k].emplace_back(b, c);
			g[b][k].emplace_back(a, c);
		}
		for (int i = 0; i < n; i++) {
			dist[i][k] = INF;
		}
		dist[t][k] = 0;
		for (int j = 0; j < n; j++) {
			int cand = -1;
			for (int i = 0; i < n; i++) {
				if (!used[i][k]) {
					if (cand == -1 || dist[i][k] < dist[cand][k]) {
						cand = i;
					}
				}
			}
			if (cand == -1) {
				break;
			}
			used[cand][k] = 1;
			for (auto x : g[cand][k]) {
				int to = x.first;
				if (dist[to][k] > dist[cand][k] + x.second) {
					dist[to][k] = dist[cand][k] + x.second;
				}
			}
		}
	}
}

int can[MAXN];

void dfs(int v, int tp) {
	can[2 * v + tp] = 1;
	for (auto x : g[v][tp]) {
		if (dist[x.first][tp] < dist[v][tp]) {
			if (can[x.first * 2 + (tp ^ 1)] == 1) {
				cout << "-1\n";
				exit(0);
			}
			if (!can[x.first * 2 + (tp ^ 1)]) {
				dfs(x.first, tp ^ 1);
			}
		}
	}
	can[2 * v + tp] = 2;
}

inline void solve() {
	init();
	dfs(s, 0);
	vector<pair<pair<int, int>, int>> edges;
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < 2; k++) {
			for (auto x : g[i][k]) {
				int to = x.first;
				if (dist[to][k] < dist[i][k]) {
					edges.emplace_back(make_pair(2 * to + (k ^ 1), 2 * i + k), x.second);
				}
			}
		}
	}
	for (int i = 0; i < MAXN; i++) {
		D[i] = -INF;
	}
	D[2 * t] = 0;
	D[2 * t + 1] = 0;
	for (int i = 0; i < MAXN; i++) {
		for (auto e : edges) {
			int v = e.first.first;
			int to = e.first.second;
			int c = e.second;
			if (D[to] < D[v] + c) {
				// if (MAXN - i < 100 && can[to]) {
				// 	cout << "-1\n";
				// 	return;
				// }
				D[to] = D[v] + c;
			}
		}
		// if (D[2 * s] >= INF) {
		// 	cout << "-1\n";
		// 	return;
		// }
	}
	int ans = D[2 * s];
	// if (ans < 0) {
	// 	cout << "-1\n";
	// 	return;
	// }
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> s >> t)
		solve();
	return 0;
}