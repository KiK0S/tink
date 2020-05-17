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
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m;
int s, t;

struct edge {
	int to, cap, flow;
};

vector<edge> e;
vector<int> g[MAXN];
int used[MAXN];
vector<int> ans; 

int dfs(int v, int mx = INF) {
	if (mx == 0 || v == t) {
		return mx;
	}
	if (used[v]) {
		return 0;
	}
	used[v] = 1;
	for (auto id : g[v]) {
		int to = e[id].to;
		int x = 0;
		if (x = dfs(to, min(mx, e[id].cap - e[id].flow))) {
			e[id].flow += x;
			e[id ^ 1].flow -= x;
			return x;
		}
	}
	return 0;
}

void find_ans(int v) {
	ans.push_back(v);
	if (v == t) {
		for (auto it : ans) {
			cout << it + 1 << ' ';
		}
		cout << '\n';
		return;
	}
	for (auto id : g[v]) {
		int to = e[id].to;
		if (e[id].flow == 1) {
			e[id].flow = 0;
			find_ans(to);
			return;
		}
	}
}

inline void init() {
	s--, t--;
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		e.push_back({b, 1, 0});
		e.push_back({a, 0, 0});
		g[a].push_back(e.size() - 2);
		g[b].push_back(e.size() - 1);
	}
	int res = 0;
	res += dfs(s);
	memset(used, 0, sizeof(used));
	res += dfs(s);
	if (res < 2) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	find_ans(s);
	ans.clear();
	find_ans(s);
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
	while (cin >> n >> m >> s >> t)
		solve();
	return 0;
}