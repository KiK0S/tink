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
	const int MAXN = 2500;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 2500;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, k;

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

int tpow[10][2];

inline void init() {
	tpow[0][0] = 1;
	tpow[0][1] = 2;
	for (int i = 1; i < 10; i++) {
		tpow[i][0] = tpow[i - 1][0] * 3;
		tpow[i][1] = tpow[i][0] * 2;
	}
}

vector<int> cnt[MAXN];

inline void solve() {
	init();
	vector<vector<int>> kek(n, vector<int>(k));
	vector<vector<int>> coords(k, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cin >> kek[i][j];
			// kek[i][j] *= 2;
			coords[j][i] = kek[i][j];
		}
	}
	for (int j = 0; j < k; j++) {
		sort(coords[j].begin(), coords[j].end());
	}
	for (int i = 0; i < n; i++) {
		int mask = 0;
		for (int j = 0; j < k; j++) {
			int mid = (coords[j][n / 2 - 1] + coords[j][n / 2]) / 2;
			if (kek[i][j] < mid) {
				mask += tpow[j][0];
			}
			if (kek[i][j] > mid) {
				mask += tpow[j][1];
			}
		}
		cnt[mask].push_back(i);
	}
	for (int i = 0; i < tpow[k][0]; i++) {
		if (i % 3 == 1) {
			make_edge(0, i, cnt[i].size());
		}
		if (i % 3 == 2) {
			make_edge(i, MAXN - 1, cnt[i].size());
		}
	}
	for (int maska = 0; maska < tpow[k][0]; maska++) {
		if (maska % 3 != 1) {
			continue;
		}
		for (int maskb = 0; maskb < tpow[k][0]; maskb++) {
			if (maskb % 3 != 2) {
				continue;
			}
			int tmp_a = maska;
			int tmp_b = maskb;
			bool ok = 1;
			for (int i = 0; i < k; i++) {
				int ma = tmp_a % 3;
				int mb = tmp_b % 3;
				if (ma == mb && ma != 0) {
					ok = 0;
					break;
				}
				tmp_b /= 3;
				tmp_a /= 3;
			}
			if (ok) {
				make_edge(maska, maskb, INF);
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
			memset(used, 0, sizeof(used));
			int x = 0;
			while (x = dfs(0)) {
				flow += x;
			}
		}
		MINFLOW >>= 1;
	}
	if (flow * 2 < n) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	for (int mask = 0; mask < tpow[k][0]; mask++) {
		if (mask % 3 != 1) {
			continue;
		}
		for (auto id : g[mask]) {
			int to = e[id].to;
			while (e[id].flow > 0) {
				e[id].flow--;
				cout << cnt[mask].back() + 1 << ' ' << cnt[to].back() + 1 << '\n';
				cnt[mask].pop_back();
				cnt[to].pop_back();
			}
		}
	}
}


signed main() {
	#ifdef DEBUG
		freopen("I.in", "r", stdin);
		freopen("I.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}