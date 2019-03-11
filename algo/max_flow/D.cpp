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
	const int MAXN = 100;
	const int MAXV = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 5e4;
	const int MAXV = 100;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif
#define int ll
mt19937 rng(time(0));

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
int MINFLOW = 1 << 30;

map<char, int> C = {
	{'.', 0},
	{'N', 3},
	{'H', 1},
	{'C', 4},
	{'O', 2}
};

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

char val[MAXV][MAXV];

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

inline void init() {

}

inline void solve() {
	init();
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> val[i][j];
			sum += C[val[i][j]];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i + j) & 1) {
				e.emplace_back(i * m + j + 1, C[val[i][j]], 0);
				e.emplace_back(0, 0, 0);
				g[i * m + j + 1].push_back(e.size() - 1);
				g[0].push_back(e.size() - 2);
			}
			else {
				e.emplace_back(i * m + j + 1, 0, 0);
				e.emplace_back(MAXN - 1, C[val[i][j]], 0);
				g[i * m + j + 1].push_back(e.size() - 1);
				g[MAXN - 1].push_back(e.size() - 2);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i + j) & 1) {
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k];
					int y = j + dy[k];
					if (x >= 0 && x < n && y >= 0 && y < m) {
						e.emplace_back(x * m + y + 1, 1, 0);
						e.emplace_back(i * m + j + 1, 0, 0);
						g[i * m + j + 1].push_back(e.size() - 2);
						g[x * m + y + 1].push_back(e.size() - 1);
					}
				}
			}
		}
	}
	int flow = 0;
	while (MINFLOW > 0) {
		while (1) {
			bfs();
			if (dist[MAXN - 1] == INF) {
				break;
			}
			int x = 0;
			memset(used, 0, sizeof(used));
			while (x = dfs(0)) {
				flow += x;
			}
		}
		MINFLOW >>= 1;
	}
	if (flow * 2 == sum && sum != 0) {
		cout << "Valid\n";
	}
	else {
		cout << "Invalid\n";
	}
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}