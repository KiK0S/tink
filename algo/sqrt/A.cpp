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
#include <ctime>
#include <bitset>
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 3e5 + 10;
#endif

int n, m;

vector<int> g[MAXN];
int cnt[MAXN];
int deg[MAXN];
int vert[MAXN];

inline void init() {
	for (int i = 0; i < n; i++) {
		vert[i] = i;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}
	sort(vert, vert + n, [&](int a, int b) {
		return make_pair(deg[a], a) < make_pair(deg[b], b);
	});
	for (int i = 0; i < n; i++) {
		sort(g[i].rbegin(), g[i].rend(), [&](int a, int b) {
			return make_pair(deg[a], a) < make_pair(deg[b], b);
		});
		while (g[i].size() && make_pair(deg[g[i].back()], g[i].back()) < make_pair(deg[i], i)) {
			g[i].pop_back();
		}
		reverse(g[i].begin(), g[i].end());
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int cur = vert[i];
		for (auto v : g[cur]) {
			cnt[v]++;
		}
		for (auto v : g[cur]) {
			for (auto it : g[v]) {
				ans += cnt[it];
			}
		}
		for (auto v : g[cur]) {
			cnt[v]--;
		}
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