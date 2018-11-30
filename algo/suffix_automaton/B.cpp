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
	const int MAXN = 100;
#else
	const int MAXN = 5e5;
#endif

struct node {
	int to[27];
	int p = -1;
	int len = 0;
	int link = -1;
	int ans = 0;
	int last_used = -1;
	node() {
		memset(to, -1, sizeof(to));
	}
};

int n;
node g[MAXN];
int pnt = 0;
int timer = 0;

int add(int a, int ch) {
	int b = pnt++;
	g[b].len = g[a].len + 1;
	g[b].p = a;
	g[b].link = 0;
	while (a != -1) {
		if (g[a].to[ch] == -1) {
			g[a].to[ch] = b;
			a = g[a].link;
			continue;
		}
		int c = g[a].to[ch];
		if (g[c].p == a) {
			g[b].link = c;
			break;
		}
		int d = pnt++;
		for (int i = 0; i < 27; i++) {
			g[d].to[i] = g[c].to[i];
		}
		g[d].ans = g[c].ans;
		g[d].link = g[c].link;
		g[c].link = d;
		g[d].len = g[a].len + 1;
		g[d].p = a;
		g[b].link = d;
		while (a != -1 && g[a].to[ch] == c) {
			g[a].to[ch] = d;
			a = g[a].link;
		}
		break;
	}
	return g[g[b].p].to[ch];
}

void subauto(int v) {
	if (v < 0 || g[v].last_used == timer) {
		return;
	}
	g[v].last_used = timer;
	g[v].ans++;
	subauto(g[v].link);
	subauto(g[v].p);
}

int ans[MAXN];
int vertex[MAXN];

void dfs(int v) {
	if (v == -1 || g[v].last_used == timer) {
		return;
	}
	g[v].last_used = timer;
	ans[g[v].ans] = max(ans[g[v].ans], g[v].len);
	for(int i = 0; i < 27; i++) {
		dfs(g[v].to[i]);
	}
}

inline void init() {
	pnt = 1;
}

inline void solve() {
	init();
	int v = 0;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (auto c : s) {
			v = add(v, c - 'a');
		}
		subauto(v);
		vertex[i] = v;
		// timer++;
		// for (int i = 0; i < pnt; i++) {
		// 	cerr << "vertex " << i << '\n';
		// 	cerr << g[i].to[0] << ' ' << g[i].to[1] << '\n';
		// 	cerr << "link " << g[i].link << '\n';
		// 	cerr << "len " << g[i].len << '\n';
		// 	cerr << "ans " << g[i].ans << '\n';
		// 	cerr << '\n';
		// }
		timer++;
		v = 0;
	}
	// for (int i = 0; i < n; i++) {
	// 	subauto(vertex[i]);
	// 	timer++;
	// }
	timer++;
	dfs(0);
	int cur = -1;
	for (int i = n; i >= 2; i--) {
		cur = max(cur, ans[i]);
		ans[i] = cur;
	}
	for (int i = 2; i <= n; i++) {
		cout << ans[i] << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}