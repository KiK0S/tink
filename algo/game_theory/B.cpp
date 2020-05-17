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

int n, r;
vector<int> g[MAXN];
int dp[MAXN];
map<pair<int, int>, int> edge;

inline void init() {

}

void dfs(int v, int p = -1) {
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		dfs(to, v);
		dp[v] ^= dp[to] + 1;
	}
}

void find_ans(int v, int need, int p = -1) {
	// cerr << v << ' ' << need << '\n';
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		if (((dp[to] + 1) ^ dp[v]) == need) {
			cout << edge[{to, v}] << '\n';
			exit(0);
		}
	}
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		int nd = (need ^ (dp[v] ^ (dp[to] + 1))) - 1;
		find_ans(to, nd, v);
	}
}

inline void solve() {
	init();
	r--;
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		edge[{a, b}] = i + 1;
		edge[{b, a}] = i + 1;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(r);
	if (dp[r] == 0) {
		cout << "2\n";
		return;
	}
	// for (int i = 0; i < n; i++) {
	// 	cerr << dp[i] << ' ';
	// }
	// cerr << '\n';
	cout << 1 << '\n';
	find_ans(r, 0);
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
	while (cin >> n >> r)
		solve();
	return 0;
}