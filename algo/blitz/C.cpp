#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

#define int ll

int n, m, s, f;

vector<pair<int, int>> g[MAXN];
int dist[MAXN];
int pre[MAXN];

void solve() {
	s--, f--;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}
	set<pair<int, int>> S;
	for (int i = 0; i < n; i++) {
		dist[i] = 1e18;
		pre[i] = -1;
	}
	dist[s] = 0;
	for (int i = 0; i < n; i++) {
		S.insert(make_pair(dist[i], i));
	}
	while (!S.empty()) {
		int cost = (*S.begin()).first;
		int v = (*S.begin()).second;
		S.erase(*S.begin());
		for (auto to : g[v]) {
			if (dist[to.first] > cost + to.second) {
				S.erase({dist[to.first], to.first});
				dist[to.first] = cost + to.second;
				pre[to.first] = v;
				S.insert({dist[to.first], to.first});
			}
		}
	}
	if (dist[f] > 1e17) {
		cout << "-1\n";
		return;
	}
	cout << dist[f] << '\n';
	vector<int> res;
	while (f != -1) {
		res.push_back(f + 1);
		f = pre[f];
	}
	reverse(res.begin(), res.end());
	for (auto v : res) {
		cout << v << ' ';
	}
	cout << '\n';
	return;
}

signed main() {
	#ifdef DEBUG 
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
		freopen("distance.in", "r", stdin);
		freopen("distance.out", "w", stdout);	
	#endif
	while (cin >> n >> m >> s >> f) {
		solve();
	}
	return 0;
}