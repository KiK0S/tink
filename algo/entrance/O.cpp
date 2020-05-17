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
	const int MAXLOG = 4;
#else
	const int MAXN = 1e6 + 10;
	const int MAXLOG = 21;
#endif

int n;

int p[MAXN];
int pre[MAXN][MAXLOG];
int h[MAXN];

inline void init() {
	memset(p, 0, sizeof(p));
	memset(pre, 0, sizeof(pre));
	memset(h, 0, sizeof(h));
}

int find_parent(int v, int d) {
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if ((1 << i) <= d) {
			v = pre[v][i];
			d -= 1 << i;
		}
	}
	return v;
}

int lca(int v, int u) {
	v = find_parent(v, max(0, h[v] - h[u]));
	u = find_parent(u, max(0, h[u] - h[v]));
	if (v == u) {
		return v;
	}
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (pre[v][i] != pre[u][i]) {
			v = pre[v][i];
			u = pre[u][i];
		}
	}
	return pre[v][0];
}

int dist(int v, int u) {
	int l = lca(v, u);
	return h[v] + h[u] - 2 * h[l];
}

inline void solve() {
	init();
	int center1 = 0;
	int center2 = 0;
	int curlen = 0;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		p[i]--;
		h[i] = h[p[i]] + 1;
		pre[i][0] = p[i];
		for (int j = 1; j < MAXLOG; j++) {
			pre[i][j] = pre[pre[i][j - 1]][j - 1];
		}
		if (curlen % 2 == 0) {
			if (dist(i, center1) > curlen / 2) {
				if (center1 == lca(i, center1)) {
					center2 = find_parent(i, dist(i, center1) - 1);
				}
				else {
					center2 = p[center1];
				}
				curlen++;
			}
		}
		else {
			if (dist(center1, i) > dist(center2, i)) {
				swap(center2, center1);
			}
			if (dist(i, center1) > curlen / 2) {
				curlen++;
			}		
		}
		cout << curlen << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("O.in", "r", stdin);
		freopen("O.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}