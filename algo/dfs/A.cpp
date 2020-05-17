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
	const int MAXN = 1e5;
#endif

int n;
double v;
#define tm TM
int tm[MAXN];
vector<int> g[MAXN];
int mt[MAXN];
int x[MAXN];
int y[MAXN];
int used[MAXN];

inline void init() {
	memset(used, 0, sizeof(used));
	memset(mt, -1, sizeof(mt));
	v /= 60;
}

int dfs(int v) {
	if (used[v]) {
		return 0;
	}
	used[v] = 1;
	for (auto to : g[v]) {
		if (mt[to] == -1 || dfs(mt[to])) {
			mt[to] = v;
			return 1;
		}
	}
	return 0;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int h, m;
		scanf("%d:%d", &h, &m);
		cin >> x[i] >> y[i];
		tm[i] = h * 60 + m;
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				continue;
			}
			if (tm[i] > tm[j]) {
				continue;
			}
			int have = tm[j] - tm[i];
			if (have * v >= hypot(x[i] - x[j], y[i] - y[j])) {
				g[i].push_back(j);
				// cerr << "new edge " << i << ' ' << j << '\n';
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (dfs(i)) {
			ans++;
			memset(used, 0, sizeof(used));
		}
	}
	cout << n - ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	// ios_base::sync_with_stdio(0);
	// cin.tie(0);
	// cout.tie(0);
	while (cin >> n >> v)
		solve();
	return 0;
}