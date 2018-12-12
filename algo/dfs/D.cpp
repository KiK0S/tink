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
	const int MAXN = 10;
#else
	const int MAXN = 2e5;
#endif

int n, m, h;

int start[MAXN];
vector<int> g[MAXN];
vector<int> gr[MAXN];
set<int> bg[MAXN];
int used[MAXN];
vector<int> eul;
int cnt[MAXN];
int ans = 1e9;

void dfs(int v) {
	used[v] = 1;
	for (auto to : g[v]) {
		if (used[to]) {
			continue;
		}
		dfs(to);
	}
	eul.push_back(v);
}

void dfs_1(int v, int clr) {
	used[v] = clr;
	for (auto to : gr[v]) {
		if (used[to]) {
			continue;	
		}
		dfs_1(to, clr);
	}
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		cnt[i] = 1e9;
		g[i].clear();
		gr[i].clear();
	}
	memset(used, 0, sizeof(used));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> start[i];
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		if ((start[a] + 1) % h == start[b]) {
			g[a].push_back(b);
			gr[b].push_back(a);
		}
		if ((start[b] + 1) % h == start[a]) {
			g[b].push_back(a);
			gr[a].push_back(b);
		}
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	reverse(eul.begin(), eul.end());
	int col = 1;
	memset(used, 0, sizeof(used));
	for (auto v : eul) {
		if (used[v]) {
			continue;
		}
		dfs_1(v, col++);
	}
	for (int i = 0; i < n; i++) {
		for (auto to : g[i]) {
			if (used[to] != used[i]) {
				bg[used[i]].insert(used[to]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (cnt[used[i]] > MAXN) {
			cnt[used[i]] = 0;
		}
		cnt[used[i]]++;
	}
	for (int i = 0; i < MAXN; i++) {
		if (bg[i].size()) {
			continue;
		}
		ans = min(ans, cnt[i]);
	}
	for (int i = 1; i < MAXN; i++) {
		if (bg[i].size()) {
			continue;
		}
		if (cnt[i] == ans) {
			cout << cnt[i] << '\n';
			for (int j = 0; j < n; j++) {
				if (used[j] == i) {
					cout << j + 1 << ' ';
				}
			}
			cout << '\n';
			break;
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> h)
		solve();
	return 0;
}