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
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m, A, B, C;


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
int MINFLOW = 1 << 30;

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
			if (dist[to] == INF && e[id].cap - e[id].flow >= MINFLOW) {
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
	if (v == MAXN - 1 || mx == 0) {
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

void make_edge(int from, int to, int cap) {
	e.emplace_back(to, cap, 0);
	e.emplace_back(from, 0, 0);
	g[from].push_back(e.size() - 2);
	g[to].push_back(e.size() - 1);
}

char G[100][100];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};


int get(int x, int y) {
	return 1 + y + x * m;
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> G[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (G[i][j] == 'B') {
				make_edge(0, get(i, j), 0);
				make_edge(get(i, j), MAXN - 1, 2 * A);
			}
			else {
				make_edge(0, get(i, j), 2 * B);
				make_edge(get(i, j), MAXN - 1, 0);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int dir = 0; dir < 4; dir++) {
				int x = i + dx[dir];
				int y = j + dy[dir];
				if (x < 0 || y < 0 || x >= n || y >= m) {
					continue;
				}
				make_edge(get(i, j), get(x, y), 2 * C);
			}
		}
	}
	int ans = 0;
	while (MINFLOW > 0) {
		while (1) {
			bfs();
			if (dist[MAXN - 1] == INF) {
				break;
			}
			int x = 0;
			memset(used, 0, sizeof(used));
			while (x = dfs(0)) {
				ans += x;
			}
		}
		MINFLOW >>= 1;
	}
	cout << ans / 2 << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("H.in", "r", stdin);
		freopen("H.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> A >> B >> C)
		solve();
	return 0;
}