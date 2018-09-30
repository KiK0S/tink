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
	const int MAXLOG = 5;
#else
	const int MAXN = 4e5;
	const int MAXLOG = 22;
#endif

int n;
int pre[MAXN][MAXLOG];
int h[MAXN][MAXLOG];
int used[MAXN];
int level[MAXN];
int change[MAXN];
struct triplet {
	int a, b, c;
	triplet() {}
	triplet(int _a, int _b, int _c) {
		a = _a, b = _b, c = _c;
	}
};

vector<pair<int, int>> g[MAXN];
vector<triplet> s[MAXN];

int dfs(int v, int p, int sz, int &c) {
	if (used[v]) {
		return 0;
	}
	int cnt = 1;
	for (auto to : g[v]) {
		if (to.first == p) {
			continue;
		}
		cnt += dfs(to.first, v, sz, c);
	}
	if (c == -1 && (cnt * 2 >= sz || p == -1)) {
		c = v;
	}
	return cnt;
}

void calc_dist(int v, int p, int lg, int add) {
	h[v][lg] = (p == -1 ? 0 : h[p][lg]) + add;
	for (auto to : g[v]) {
		if (used[to.first] || to.first == p) {
			continue;
		}
		calc_dist(to.first, v, lg, to.second);
	}
}

int find_centroid(int v, int sz, int lg, int p = -1) {
	int c = -1;
	dfs(v, -1, sz, c);
	for (int i = 0; i < lg; i++) {
		pre[c][i] = pre[p][i];
	}
	used[c] = 1;
	level[c] = lg;
	pre[c][lg] = c;
	calc_dist(c, -1, lg, 0);
	for (auto to : g[c]) {
		if (used[to.first]) {
			continue;
		}
		int nxt = find_centroid(to.first, sz / 2, lg + 1, c);
	}
	return c;
}

inline void init() {
	memset(pre, -1, sizeof(pre));
	memset(used, 0, sizeof(used));
	for (int i = 0; i < MAXN; i++) {
		g[i].clear();
		s[i].clear();
		s[i].emplace_back(1e9 + 10, 0, -1);
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}
	find_centroid(0, n, 0);
	// for (int i = 0; i < n; i++) {
	// 	cerr << level[i] << ' ';
	// }
	// cerr << '\n';
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		type--;
		if (!type) {
			int start, b, c;
			cin >> start >> b >> c;
			start--;
			int v = start;
			int cur = level[start];
			while (cur >= 0) {
				int dst = b - h[start][cur];
				// cerr << dst << '\n';
				while (s[v].back().a <= dst) {
					s[v].pop_back();
				}
				s[v].emplace_back(dst, c, i);
				if (cur == 0) {
					break;
				}
				cur--;
				v = pre[start][cur];
			}
		}
		else {
			int start;
			cin >> start;
			start--;
			bool ok = 0;
			pair<int, int> ans = {-1, 0};
			for (int cur = 0; cur <= level[start]; cur++) {
				int v = pre[start][cur];
				int l = 0;
				int r = s[v].size();
				// cerr << h[start][cur] << '\n';
				while (l + 1 < r) {
					int mid = (l + r) >> 1;
					if (s[v][mid].a < h[start][cur]) {
						r = mid;
					}
					else {
						l = mid;
					}
				}
				// cerr << v << '\t';
				// for (auto it : s[v]) {
				// 	cerr << it.first << ' ' << it.second << '\t';
				// }
				// cerr << '\n';
				ans = max(ans, make_pair(s[v][l].c, s[v][l].b));
			}
			cout << ans.second << '\n';
		}
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