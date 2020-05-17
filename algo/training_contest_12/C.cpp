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
	const int MAXN = 5e5 + 10;
#endif
#define int ll

int n, m;
set<pair<int, int>> good;
vector<int> g[MAXN];
set<int> t[MAXN];
int val[MAXN];
int tin[MAXN];
int fup[MAXN];
int used[MAXN];
int color[MAXN];
int color_cost[MAXN];
int color_cnt[MAXN];
int timer = 0;
int dp[MAXN];
int ans = 0;

void br(int v, int p = -1) {
	fup[v] = tin[v] = timer++;
	used[v] = 1;
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		if (used[to]) {
			fup[v] = min(fup[v], tin[to]);
		}
		else {
			br(to, v);
			fup[v] = min(fup[v], fup[to]);
		}
	}
}

int next_color = 1;

void paint(int v, int c) {
	color[v] = c;
	color_cost[c] += val[v];
	color_cnt[c]++;
	for (auto to : g[v]) {
		if (color[to] != -1) {
			continue;
		}
		if (fup[to] > tin[v]) {
			paint(to, next_color++);
			t[color[v]].insert(color[to]);
			t[color[to]].insert(color[v]);
		}
		else {
			paint(to, c);
		}
	}
}

void get(int v) {
	used[v] = 1;
	dp[v] = color_cost[v];
	vector<int> also;
	also.push_back(0ll);
	for (auto to : t[v]) {
		if (!used[to]) {
			get(to);
			also.push_back(dp[to]);
		}
	}
	sort(also.rbegin(), also.rend());
	dp[v] += also[0];
	ans = max(ans, dp[v]);
	if (also.size() > 1) {
		ans = max(ans, dp[v] + also[1]);
	}
}

inline void init() {
	assert(n < 2e5);
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	br(0);
	memset(color, -1, sizeof(color));
	paint(0, 0);
	for (int i = 0; i < next_color; i++) {
		int cur = i;
		if (color_cnt[cur] == 1) {
			continue;
		}
		while (t[cur].size() == 1) {
			color_cnt[*t[cur].begin()] += color_cnt[cur];
			color_cost[*t[cur].begin()] += color_cost[cur];
			color_cost[cur] = 0;
			color_cnt[cur] = 0;		
			t[*t[cur].begin()].erase(cur);
			cur = *t[cur].begin();
		}
	}
	memset(used, 0, sizeof(used));
	for (int i = 0; i < next_color; i++) {
		if (!used[i]) {
			get(i);
		}
	}
	cout << ans << '\n';
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
	cin >> n >> m;
	solve();
	return 0;
}