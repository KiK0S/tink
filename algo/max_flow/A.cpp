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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 1000;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));
#define int ll
const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m;

struct edge {
	int to, cap, flow = 0;
	edge() {}
	edge(int a, int b) {
		to = a;
		cap = b;
	}
};

vector<edge> e;
vector<int> g[MAXN];
int SCALE = 1 << 30;
int dist[MAXN];
int used[MAXN];

void bfs() {
	for (int i = 0; i < n; i++) {
		dist[i] = INF;
	}
	dist[0] = 0;
	queue<int> q;
	q.push(0);
	while(q.size()) {
		int v = q.front();
		q.pop();
		for (auto id : g[v]) {
			int to = e[id].to;
			if (e[id].cap - e[id].flow >= SCALE && dist[to] == INF) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
}

int dfs(int v, int mx = INF) {
	if (used[v]) {
		return 0;
	}
	if (mx == 0 || v == n - 1) {
		return mx;
	}
	for (auto id : g[v]) {
		int to = e[id].to;
		if (dist[to] == dist[v] + 1) {
			int x = 0;
			if (x = dfs(to, min(mx, e[id].cap - e[id].flow))) {
				e[id].flow += x;
				e[id ^ 1].flow -= x;
				return x;
			}
		}
	}
	used[v] = 1;
	return 0;
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		e.emplace_back(b, c);
		e.emplace_back(a, 0);
		g[a].push_back(e.size() - 2);
		g[b].push_back(e.size() - 1);
	}
	int ans = 0;
	while (SCALE > 0) {
		while (1) {
			bfs();
			memset(used, 0, sizeof(used));
			if (dist[n - 1] == INF) {
				break;
			}
			int x = 0;
			while (x = dfs(0)) {
				ans += x;
			}
		}
		SCALE >>= 1;
	}	
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
	while (cin >> n >> m)
		solve();
	return 0;
}