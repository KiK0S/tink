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
	const int MAXN = 200;
#else
	const int MAXN = 2 * 80 * 80;
#endif

#define int ll

int n, m;

struct E {
	int from;
	int to;
	int cap;
	int flow;
	E() {}
	E(int a, int b, int c, int d) {
		from = a;
		to = b;
		cap = c;
		flow = d;
	}
};

pair<int, int> d[] = {
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}
};
vector<E> e;
int used[MAXN];
vector<int> g[MAXN];
vector<int> inp[MAXN];
int dist[MAXN];
int s, f;
int X = 1ll << 60;
int pnt;

void bfs() {
	for (int i = 0; i < MAXN; i++) {
		dist[i] = 1e9;
	}
	dist[f] = 1e9;
	dist[s] = 0;
	queue<int> q;
	q.push(0);
	while (q.size()) {
		int v = q.front();
		q.pop();
		for (auto id : g[v]) {
			int to = e[id].to;
			if (e[id].cap >= e[id].flow + X && dist[to] > dist[v] + 1) {
				dist[to] = dist[v] + 1;
				q.push(to);
			}
		}
	}
}

int dfs(int v, int d = 1e15) {
	if (used[v] || d <= 0) {
		return 0;
	}
	if (v == f) {
		return d;
	}
	used[v] = 1;
	for (auto id : g[v]) {
		int to = e[id].to;
		int x;
		if (dist[to] != dist[v] + 1 || e[id].cap < e[id].flow + X) {
			continue;
		}
		if (x = dfs(to, min(d, e[id].cap - e[id].flow))) {
			e[id].flow += x;
			used[v] = 0;
			e[id ^ 1].flow -= x;
			return x;
		}
	}
	return 0;
}

void make_edge(int a, int b, int c) {
	e.emplace_back(a, b, c, 0);
	e.emplace_back(b, a, 0, 0);
	g[a].push_back(e.size() - 2);
	g[b].push_back(e.size() - 1);
	inp[b].push_back(e.size() - 2);
	inp[a].push_back(e.size() - 1);
}

int id[80][80];
int a[80][80];
int ans[80][80][4];

char field[300][300];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	s = 0;
	f = MAXN - 1;
	pnt = 1;
	int sum_a = 0;
	int sum_b = 0;
	int cnt_a = 0;
	int cnt_b = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i + j) & 1) {
				cnt_a++;
				sum_a += a[i][j];
				id[i][j] = pnt;
				if (a[i][j] == 2) {
					make_edge(s, pnt++, 1);
					make_edge(s, pnt++, 1);
				}
				else {
					make_edge(s, pnt++, a[i][j]);
				}
			}
			else {
				cnt_b++;
				sum_b += a[i][j];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i + j) & 1) {

			}
			else {
				id[i][j] = pnt;
				if (a[i][j] == 2) {
					make_edge(pnt++, f, 1);
					make_edge(pnt++, f, 1);
				}
				else {
					make_edge(pnt++, f, a[i][j]);
				}
			}
		}
	}
	if (sum_a != sum_b) {
		cout << "Impossible!\n";
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i + j) & 1) {
				for (int k = 0; k < 4; k++) {
					auto it = d[k];
					int x = i + it.first;
					int y = j + it.second;
					if (x >= 0 && x < n && y >= 0 && y < m) {
						int st = id[i][j];
						if (a[i][j] == 2) {
							st += k & 1;
						}
						if (a[x][y] == 2) {
							make_edge(st, id[x][y] + (k & 1), 1);
						}
						else {
							make_edge(st, id[x][y], 1);
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < MAXN; i++) {
		random_shuffle(g[i].begin(), g[i].end());
	}
	int flow = 0;
	int x;
	while (X) {
		while (1) {
			bfs();
			if (dist[f] == 1e9) {
				break;
			}
			while (x = dfs(s)) {
				flow += x;
			}
			memset(used, 0, sizeof(used));
		}
		X >>= 1;
	}
	if (flow != sum_a) {
		cout << "Impossible!\n";
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i + j) & 1) {
				int v = id[i][j];
				for (auto q : g[v]) {
					if (e[q].flow == 1) {
						for (int k = 0; k < 4; k++) {
							auto it = d[k];
							int x = i + it.first;
							int y = j + it.second;
							if (x >= 0 && x < n && y >= 0 && y < m && (id[x][y] == e[q].to || a[x][y] == 2 && id[x][y] + 1 == e[q].to)) {
								ans[i][j][k] = 1;
								ans[x][y][k ^ 2] = 1;
							}
						}	
					}
				}
				if (a[i][j] == 2) {
					v++;
					for (auto q : g[v]) {
						if (e[q].flow == 1) {
							for (int k = 0; k < 4; k++) {
								auto it = d[k];
								int x = i + it.first;
								int y = j + it.second;
								if (x >= 0 && x < n && y >= 0 && y < m && (id[x][y] == e[q].to || a[x][y] == 2 && id[x][y] + 1 == e[q].to)) {
									ans[i][j][k] = 1;
									ans[x][y][k ^ 2] = 1;
								}
							}	
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 300; j++) {
			field[i][j] = '.';
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] != 0) {
				field[3 * i + 1][3 * j + 1] = 'O';
			}
			if (ans[i][j][0]) {
				field[3 * i + 2][3 * j + 1] = 'X';
			}
			if (ans[i][j][1]) {
				field[3 * i + 1][3 * j + 2] = 'X';
			}
			if (ans[i][j][2]) {
				field[3 * i][3 * j + 1] = 'X';
			}
			if (ans[i][j][3]) {
				field[3 * i + 1][3 * j] = 'X';
			}
		}
	}
	for (int i = 0; i < 3 * n; i++) {
		for (int j = 0; j < 3 * m; j++) {
			cout << field[i][j];
		}
		cout << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	srand(time(0));
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}