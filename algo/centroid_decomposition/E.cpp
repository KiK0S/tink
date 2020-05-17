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
	const int MAXN = 3e5 + 10;
#endif

int n;
vector<int> g[MAXN];
vector<pair<int, int>> q[MAXN];
vector<int> l[MAXN];
int ans[MAXN];

void dfs(int v, int p = -1) {
	int mx = 0;
	int id = -1;
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		dfs(to, v);
		if (l[to].size() > mx) {
			mx = l[to].size();
			id = to;
		}
	}
	if (id != -1) {
		l[v].swap(l[id]);
	}
	l[v].push_back(1);
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		int pnt = l[v].size() - 2;
		for (int i = l[to].size() - 1; i >= 0; i--) {
			l[v][pnt--] += l[to][i];
		}
	}
	for (int i = 0; i < q[v].size(); i++) {
		if (q[v][i].second < l[v].size()) {
			ans[q[v][i].first] = l[v][l[v].size() - q[v][i].second - 1];
		}
	}
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
		g[i].push_back(p);
	}
	int query;
	cin >> query;
	for (int i = 0; i < query; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		q[a].emplace_back(i, b);
	}
	dfs(0);
	for (int i = 0; i < query; i++) {
		cout << ans[i] << '\n';
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}