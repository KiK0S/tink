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
	const int MAXN = 60;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 5010;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m, k, l;
int a1, b1, a2, b2;

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
int MINFLOW = 1 << 1;

int input(int x, int y) {
	return 1 + y + m * x;
}

int output(int x, int y) {
	return 1 + n * m + y + m * x;
}

void bfs() {
	for (int i = 0; i < MAXN; i++) {
		dist[i] = INF;
	}
	dist[output(a1, b1)] = 0;
	queue<int> q;
	q.push(output(a1, b1));
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
	if (v == input(a2, b2) || mx == 0) {
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

int G[51][51];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		G[a][b] = 1;
	}
	for (int i = 0; i < l; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		G[a][b] = 2;
	}
	cin >> a1 >> b1 >> a2 >> b2;
	a1--, b1--, a2--, b2--;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int dir = 0; dir < 4; dir++) {
				int x = i + dx[dir];
				int y = j + dy[dir];
				if (x < 0 || y < 0 || x >= n || y >= m) {
					continue;
				}
				make_edge(output(i, j), input(x, y), INF);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (G[i][j] == 2) {
				make_edge(input(i, j), output(i, j), 1);	
			}
			else if (G[i][j] == 1) {
				make_edge(input(i, j), output(i, j), 0);
			}
			else {
				make_edge(input(i, j), output(i, j), INF);
			}
		}
	}
	int ans = 0;
	while (MINFLOW > 0) {
		while (1) {
			bfs();
			if (dist[input(a2, b2)] == INF) {
				break;
			}
			memset(used, 0, sizeof(used));
			int x = 0;
			while (x = dfs(output(a1, b1))) {
				if (x == INF) {
					cout << "-1\n";
					return;
				}
				ans += x;
			}
		}
		MINFLOW >>= 1;
	}
	MINFLOW = 1;
	cout << ans << '\n';
	int cnt = 0;
	bfs();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dist[output(i, j)] == INF && dist[input(i, j)] != INF && G[i][j] == 2) {
				cout << i + 1 << ' ' << j + 1 << '\n';
				cnt++;
			}
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> k >> l)
		solve();
	return 0;
}