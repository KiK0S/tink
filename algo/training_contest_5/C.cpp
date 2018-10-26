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
	const int MAXN = 5e3 + 10;
#endif

int n;
int tin[MAXN];
int tout[MAXN];
int timer = 0;
vector<int> g[MAXN];
int val[MAXN];
int pr[MAXN];
int cnt[2 * MAXN];

bool is_pr(int a, int b) {
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

void dfs(int v, int p = -1) {
	pr[v] = p;
	tin[v] = timer++;
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		dfs(to, v);
	}
	tout[v] = timer++;
}

vector<int> coord;
int m, q;

int getid(int vl) {
	return lower_bound(coord.begin(), coord.end(), vl) - coord.begin();
}
int id1[MAXN];
int id[MAXN];
inline void init() {
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	cin >> m >> q;
	coord.assign(2 * n, 2e9);
	for (int i = 0; i < n; i++) {
		coord[2 * i] = val[i];
		coord[2 * i + 1] = (q - val[i]);
	}
	sort(coord.begin(), coord.end());
	for (int i = 0; i < n; i++) {
		id[i] = getid(val[i]);
		id1[i] = getid(q - val[i]);
	}
}


inline void solve() {
	init();
	dfs(0);
	for (int i = 0; i < m; i++) {
		memset(cnt, 0, sizeof(cnt));
		int ans = 0;
		int a, b;
		cin >> a >> b;
		a--, b--;
		// cerr << a << ' ' << b << '\n';
		while (!is_pr(a, b)) {
			ans += cnt[id1[a]];
			cnt[id[a]]++;
			a = pr[a];
		// cerr << a << ' ' << b << '\n';
		}
		while (!is_pr(b, a)) {
			ans += cnt[id1[b]];
			cnt[id[b]]++;
			b = pr[b];
		// cerr << a << ' ' << b << '\n';
		}
		ans += cnt[id1[a]];
		cout << ans << '\n';
	}
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
	while (cin >> n)
		solve();
	return 0;
}