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

int n;
vector<vector<pair<int, int>>> g;
int ans = 0;

void dfs(int u, int w, int p) {
	ans = max(ans, w);
	for (auto edge : g[u]) {
		if (edge.first != p) {
			dfs(edge.first, w + edge.second, u);
		}
	}
}

inline void init() {
	cin >> n;
	g.resize(n);
	for (int i = 0; i < n - 1; ++i) {
		int x, y, c;
		cin >> x >> y >> c;
		g[x].push_back({y, c});
		g[y].push_back({x, c});
	}
	dfs(0, 0, -1);
	cout << ans << '\n';
}

inline void solve() {
	init();
	
}

signed main() {
	#ifdef DEBUG
		freopen("M.in", "r", stdin);
		freopen("M.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	// while (cin >> n)
		solve();
	return 0;
}