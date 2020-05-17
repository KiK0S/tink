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
	int to, cap, flow;
	edge(){}
	edge(int a, int b, int c) {
		to = a, cap = b, flow = c;
	}
};

vector<edge> e;
vector<int> g[MAXN];
int dist[MAXN];
int used[MAXN];
int ptr[MAXN];
int timer = 1;
int SCALE = 1 << 30;

void bfs() {
	for (int i = 0; i < MAXN; i++) {
		dist[i] = INF;
	}
	dist[0] = 0;
	queue<int> q;
	q.push(0);
	while (q.size()) {
		int v = q.front();
		q.pop();
		for (auto id : g[v]) {
			int to = e[id].to;
			if (dist[to] == INF && e[id].cap - e[id].flow >= SCALE) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
}

int dfs(int v, int mx = INF) {
	if (used[v] == timer) {
		return 0;
	}
	if (v == MAXN - 1) {
		return mx;
	}
	used[v] = timer;
	while (ptr[v] < g[v].size()) {
		int id = g[v][ptr[v]];
		int to = e[id].to;
		if (dist[to] == dist[v] + 1 && e[id].cap - e[id].flow >= SCALE) {
			int x = 0;
			if (x = dfs(to, min(mx, e[id].cap - e[id].flow))) {
				e[id].flow += x;
				e[id ^ 1].flow -= x;
				return x;
			}
		}
		ptr[v]++;
	}
	return 0;
}

void make_edge(int from, int to, int cap) {
	e.emplace_back(to, cap, 0);
	e.emplace_back(from, 0, 0);
	g[from].push_back(e.size() - 2);
	g[to].push_back(e.size() - 1);
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		make_edge(a, b, c);
	}
	int ans = 0;
	timer = 1;
	while (SCALE > 0) {
		while (1) {
			bfs();
			if (dist[MAXN - 1] == INF) {
				break;
			}
			int x = 0;
			memset(ptr, 0, sizeof(ptr));
			timer++;
			while (x = dfs(0)) {
				ans += x;
				timer++;
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

// START = 0
// FINISH = MAXN - 1