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
	const int MAXN = 3e5;
#else
	const int MAXN = 3e5;
#endif

int n;

vector<int> g[MAXN];
int dp[MAXN];
vector<int> tree[MAXN];
map<int, int> all[MAXN];
int sz[MAXN];

inline void init() {

}

void add(int v, int to) {

}

vector<int> eul;

void dfs(int v, int p = -1) {
	eul.push_back(v);
	sz[v] = 1;
	int mx = -1;
	
	for (auto to : g[v]) {
		dfs(to, v);
		sz[v] += sz[to];
		// if (mx == -1 || tree[to].size() > tree[mx].size()) {
		// 	mx = to;
		// }
	}
/*	if (mx != -1) {
		tree[v].swap(tree[mx]);
		all[v].swap(all[mx]);
	}
	for (auto to : g[v]) {
		dp[v] += dp[to];
		if (to == mx) {
			continue;
		}
		for (auto it : tree[to]) {
			add(v, it);
		}
	}*/
	// tree[v].push_back(v);
}

int f[MAXN];

void add(int id) {
	for (int i = id + 1; i < MAXN; i += i & -i) {
		f[i]++;
	}
}

int get(int id) {
	int ans = 0;
	for (int i = id + 1; i > 0; i -= i & -i) {
		ans += f[i];
	}
	return ans;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int a;
			cin >> a;
			a--;
			g[i].push_back(a);
		}
	}
	dfs(0);
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		int l = i;
		int r = i + sz[eul[i]] - 1;
		memset(f, 0, sizeof(f));
		for (int j = r; j >= l; j--) {
			ans[eul[i]] += get(eul[j]);
			add(eul[j]); 
		}
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i] << ' ';
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("As.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}