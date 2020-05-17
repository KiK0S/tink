#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1010;
#endif

#define int ll

int n;
map<pair<int, int>, int> g[MAXN];
vector<int> ans;

void dfs(int v) {
	while (!g[v].empty()) {
		int to = (*g[v].begin()).first.first;
		int cost = (*g[v].begin()).first.second;
		g[to][make_pair(v, cost)]--;
		if (g[to][make_pair(v, cost)] == 0) {
			g[to].erase(make_pair(v, cost));
		}
		g[v][make_pair(to, cost)]--;
		if (g[v][make_pair(to, cost)] == 0) {
			g[v].erase(make_pair(to, cost));
		}
		dfs(to);
		ans.push_back(to);
	}
}

void solve() {
	int st = 0;
	for (int i = 0; i < n; i++) {
		int m;
		cin >> m;
		if (m % 2 == 1) {
			st = i;
		}
		for (int j = 0; j < m; j++) {
			int a, b;
			cin >> a >> b;
			a--;
			g[i][make_pair(a, b)]++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (auto to : g[i]) {
			int v = to.first.first;
			if (g[v][make_pair(i, to.first.second)] != g[i][make_pair(v, to.first.second)]) {
				cout << "-1\n";
				return;
			}
		}
	}
	dfs(st);
	ans.push_back(st);
	reverse(ans.begin(), ans.end());
	cout << ans.size() - 1 << '\n';
	for (auto it : ans) {
		cout << it + 1 << ' ';
	}
}

signed main() {
	#ifdef DEBUG 
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
		freopen("post.in", "r", stdin);
		freopen("post.out", "w", stdout);	
	#endif
	while (cin >> n) {
		solve();
	}
	return 0;
}