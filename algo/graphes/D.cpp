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
	const int MAXN = 4e5;
#endif

int n;
vector<int> g[MAXN];
int sz[MAXN];
int tin[MAXN];
int total = 1;
int color[MAXN];
int pos[MAXN];
int pre[MAXN];
int timer = 0;


void dfs(int v, int p = -1) {
	sz[v] = 1;
	int mx = -1;
	int pos = 0;
	int res = 0;
	if (count(g[v].begin(), g[v].end(), p)) {
		g[v].erase(find(g[v].begin(), g[v].end(), p));
	}
	for (auto to : g[v]) {
		pos++;
		dfs(to, v);
		sz[v] += sz[to];
		if (mx == -1 || sz[to] > sz[mx]) {
			mx = to;
			res = pos - 1;
		}
	}
	if (sz[v] > 1) {
		swap(g[v][0], g[v][res]);
	}
}

void eul(int v, int p = -1, int c = 0, int ps = 0) {
	tin[v] = timer++;
	color[v] = c;
	pos[v] = ps;
	for (auto to : g[v]) {
		if (to == g[v][0]) {
			eul(to, v, c, ps + 1);
		}
		else {
			pre[total++] = v;
			eul(to, v, total - 1, 0);
		}
	}
}

vector<int> all[MAXN];
int tmr[MAXN];

void update(int v, int tm) {
	if (tmr[v] < tm) {
		all[v].clear();
		tmr[v] = tm;
	}
}

inline void init() {
	memset(tmr, -1, sizeof(tmr));
}

inline void solve() {
	init();
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(0);
	eul(0);
	int q;
	cin >> q;
	pre[0] = -1;
	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;
		vector<int> rd(k);
		set<int> colors;
		for (int j = 0; j < k; j++) {
			cin >> rd[j];
			rd[j]--;
			// cerr << "! " << j << '\n';
			int v = rd[j];
			while (v != -1) {
				// cerr << v << ' ';
				update(color[v], i);
				colors.insert(color[v]);
				all[color[v]].push_back(pos[v]);
				assert(color[v] < MAXN);
				v = pre[color[v]];
			}
			// cerr << '\n';
		}
		int ans = n;
		vector<int> res(k + 1);
		for (auto it : colors) {	
			sort(all[it].begin(), all[it].end());
			reverse(all[it].begin(), all[it].end());
			// cerr << it << '\t';
			// for (auto x : all[it]) {
			// 	cerr << x << ' ';
			// }
			// cerr << '\n';
			int pre = -1;
			int cnt = 0;
			assert(all[it].size() <= k);
			for (auto v : all[it]) {
				if (pre == -1) {
					pre = v;
					cnt++;
				}
				else {
					res[cnt] += pre - v;
					ans -= pre - v;
					cnt++;
					pre = v;
				}
			}
			if (pre != -1) {
				res[cnt] += pre + 1;
				ans -= pre + 1;
			}
		}
		res[0] = ans;
		for (int j = 0; j <= k; j++) {
			cout << res[j] << ' ';
		}
		cout << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}