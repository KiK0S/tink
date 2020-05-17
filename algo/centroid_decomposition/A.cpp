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
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 3e5;
#endif

int n;
vector<int> g[MAXN];
int pre[MAXN];
int used[MAXN];


int dfs(int v, int sz, int p, int &c) {
	if (used[v]) {
		return 0;
	}
	int cnt = 1;
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		cnt += dfs(to, sz, v, c);
	}
	if (c == -1 && (cnt * 2 >= sz || p == -1)) {
		c = v;
	}
	return cnt;
}

int find_centroid(int x, int sz) {
	int c = -1;
	dfs(x, sz, -1, c);
	used[c] = 1;
	for (auto to : g[c]) {
		if (used[to]) {
			continue;
		}
		pre[find_centroid(to, sz / 2)] = c;
	}
	return c;
}


inline void init() {
	memset(used, 0, sizeof(used));
	memset(pre, -1, sizeof(pre));
}

inline void solve() {
	init();
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	find_centroid(0, n);
	for (int i = 0; i < n; i++) {
		cout << pre[i] + 1 << ' ';
	}
	cout << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}