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
	const int MAXN = 20;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 300;
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
	int to, cap, flow, cost;
	edge() {

	}
	edge(int a, int b, int c, int d) {
		to = a, cap = b, flow = c, cost = d;
	}
};

vector<edge> e;
vector<int> g[MAXN];
int dist[MAXN];
int used[MAXN];
int pre[MAXN];

int x[MAXN];
int y[MAXN];
int cnt[MAXN];
int X[MAXN];
int Y[MAXN];
int CNT[MAXN];


void make_edge(int a, int b, int c, int d) {
	e.emplace_back(b, c, 0, d);
	e.emplace_back(a, 0, 0, -d);
	g[a].push_back(e.size() - 2);
	g[b].push_back(e.size() - 1);
}

inline void init() {

}

inline void solve() {
	init();
		
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> cnt[i];
	}
	for (int j = 0; j < m; j++) {
		cin >> X[j] >> Y[j] >> CNT[j];
	}
	for (int i = 0; i < n; i++) {
		make_edge(0, i + 1, cnt[i], 0);
	}
	for (int i = 0; i < m; i++) {
		make_edge(n + 1 + i, n + m + 1, CNT[i], 0);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			make_edge(i + 1, n + 1 + j, INF, abs(x[i] - X[j]) + abs(y[i] - Y[j]) + 1);
		}
	}
	int pre_n = n;
	n = n + m + 2;
	int cost = 0;
	while (1) {
		queue<int> q;
		vector<int> in(n, 0);
		q.push(0);
		in[0] = 1;
		for (int i = 0; i < n; i++) {
			dist[i] = INF;
			pre[i] = -1;
		}
		dist[0] = 0;
		while (q.size()) {
			int v = q.front();
			q.pop();
			in[v] = 0;
			for (auto id : g[v]) {
				int to = e[id].to;
				if (e[id].flow == e[id].cap) {
					continue;
				}
				if (dist[to] > dist[v] + e[id].cost) {
					dist[to] = dist[v] + e[id].cost;
					pre[to] = id ^ 1;
					if (!in[to]) {
						q.push(to);
						in[to] = 1;
					}
				}
			}
		}
		if (dist[n - 1] == INF) {
			break;
		}
		int flow = INF;
		for (int v = n - 1; v != 0; ) {
			int p = e[pre[v]].to;
			flow = min(flow, e[pre[v] ^ 1].cap - e[pre[v] ^ 1].flow);
			v = p;
		}
		for (int v = n - 1; v != 0; ) {
			int p = e[pre[v]].to;
			cost += flow * e[pre[v] ^ 1].cost;
			e[pre[v] ^ 1].flow += flow;
			e[pre[v]].flow -= flow;
			v = p;
		}
	}
	int other_cost = 0;
	n = pre_n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int c;
			cin >> c;
			other_cost += c * (abs(x[i] - X[j]) + abs(y[i] - Y[j]) + 1);
		}
	}
	if (other_cost == cost) {
		cout << "OPTIMAL\n";
		return;
	}
	cerr << cost << '\n';
	cout << "SUBOPTIMAL\n";
	map<pair<int, int>, int> g_ans;
	for (int i = 1; i <= n; i++) {
		for (auto id : g[i]) {
			int to = e[id].to;
			g_ans[make_pair(i - 1, to - 1 - n)] = e[id].flow;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << g_ans[make_pair(i, j)] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
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