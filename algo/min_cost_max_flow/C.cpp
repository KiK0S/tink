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
	const int MAXN = 200;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif
#define int ll
mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, k;
string s, S;

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

int ord(char c) {
	if (c >= 'a' && c <= 'z') {
		return c - 'a';
	}
	return c - 'A' + 26;
}

char rev_ord(int x) {
	if (x < 26) {
		return x + 'a';
	}
	return x - 26 + 'A';
}

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
	map<pair<int, int>, int> mapa;
	for (int i = 0; i < s.size(); i++) {
		mapa[make_pair(ord(s[i]), ord(S[i]))]++;
	}
	for (int i = 1; i <= k; i++) {
		make_edge(0, i, 1, 0);
		make_edge(i + k, 2 * k + 1, 1, 0);
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			make_edge(i + 1, k + 1 + j, 1, -mapa[make_pair(i, j)]);
		}
	}
	n = 2 * k + 2;
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
	cout << -cost << '\n';
	for (int i = 1; i <= k; i++) {
		for (auto id : g[i]) {
			if (e[id].to != 0 && e[id].flow == 1) {
				cout << rev_ord(e[id].to - k - 1);
			}
		}
	}
	cout << '\n';
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
	while (cin >> n >> k >> s >> S)
		solve();
	return 0;
}