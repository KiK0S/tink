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
	const int MAXN = 10;
#else
	const int MAXN = 2e5;
#endif
#define int ll
int n, m;
vector<pair<int, int>> g[MAXN][2];
ll dist[MAXN][2];
int dsu[MAXN][2];
int cnt[2];
const ll INF = 1e17;

int get(int x, int t) {
	if (dsu[x][t] == x) {
		return x;
	}
	return dsu[x][t] = get(dsu[x][t], t);
}

int unite(int a, int b, int t) {
	a = get(a, t);
	b = get(b, t);
	if (a == b) {
		return 0;
	}
	cnt[t]--;
	if (rand() & 1) {
		dsu[b][t] = a;
	}
	else {
		dsu[a][t] = b;
	}
	return 1;
}



inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < 2; j++) {
			dsu[i][j] = i;
			g[i][j].clear();
			dist[i][j] = INF;
		}
	}
}

inline void solve1() {
	init();
	ll ans = 0;
	for (int q = 0; q < 2; q++) {
		cin >> n >> m;
		for (int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			a--, b--;
			g[a][q].emplace_back(b, c);
			g[b][q].emplace_back(a, c);
		}
		set<pair<ll, int>> st;
		dist[0][q] = 0;
		for (int i = 0; i < n; i++) {
			st.insert({dist[i][q], i});
		}
		while (st.size()) {
			int v = (*st.begin()).second;
			st.erase(*st.begin());
			for (auto x : g[v][q]) {
				int to = x.first;
				int c = x.second;
				if (dist[to][q] > dist[v][q] + c) {
					st.erase({dist[to][q], to});
					dist[to][q] = dist[v][q] + c;
					st.insert({dist[to][q], to});
				}
			}
		}
		ans += dist[n - 1][q];
	}
	cout << ans << '\n';
}

inline void solve2() {
	init();
	int ans = 0;
	vector<pair<int, pair<int, int>>> edges;
	for (int q = 0; q < 2; q++) {
		cin >> n >> m;
		for (int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			a--, b--;
			edges.emplace_back(q ? c : -c, make_pair(a, b));
		}
		cnt[q] = n;
	}
	sort(edges.begin(), edges.end(), [](auto a, auto b){
		return abs(a.first) < abs(b.first);
	});
	int res = 0;
	for (auto e : edges) {
		int a = e.second.first;
		int b = e.second.second;
		int c = e.first;
		if (c < 0) {
			if (unite(a, b, 0)) {
				ans += -c * cnt[1];
			}
		}
		else {
			if (unite(a, b, 1)) {
				ans += c * cnt[0];
			}
		}
	}
	cout << ans << '\n';
}


signed main() {
	#ifdef DEBUG
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int type;
	cin >> type;
	if (type == 1) {
		solve1();
	}
	else {
		solve2();
	}
	return 0;
}