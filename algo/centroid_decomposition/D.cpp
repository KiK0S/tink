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
	const int MAXN = 1e5;
#endif

int n;

int ans[MAXN];
vector<int> g[MAXN];
int pre[MAXN];
int used[MAXN];
vector<int> all;
vector<int> cur;

void add(vector<int> &v, int pos) {
	while (v.size() <= pos) {
		v.push_back(0);
	}
	v[pos]++;
}

void calc_multiply() {
	for (int i = 0; i < all.size(); i++) {
		for (int j = 0; j < cur.size(); j++) {
			ans[i + j] += all[i] * cur[j];
		}
	}
}

int dfs(int v, int p, int sz, int &c) {
	int cnt = 1;
	for (auto to : g[v]) {
		if (used[to] || to == p) {
			continue;
		}
		cnt += dfs(to, v, sz, c);
	}
	if (c == -1 && (cnt * 2 >= sz || p == -1)) {
		c = v;
	}
	return cnt;
}

void calc_h(int v, int p, int H, vector<int> &cur) {
	add(cur, H);
	for (auto to : g[v]) {
		if (to == p || used[to]) {
			continue;
		}
		calc_h(to, v, H + 1, cur);
	}
}

int find_centroid(int v, int sz) {
	int c = -1;
	dfs(v, -1, sz, c);
	used[c] = 1;
	all.clear();
	add(all, 0);
	for (auto to : g[c]) {
		if (!used[to]) {
			cur.clear();
			calc_h(to, c, 1, cur);
			calc_multiply();
			for (int i = 0; i < cur.size(); i++) {
				if (i == all.size()) {
					all.push_back(0);
				}
				all[i] += cur[i];
			}
		}
	}
	for (auto to : g[c]) {
		if (used[to]) {
			continue;
		}
		find_centroid(to, sz / 2);
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
	for (int i = 1; i < n; i++) {
		cout << ans[i] << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}