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
	const int MAXN = 3e5;
#endif

#define int ll

int n;

struct V {
	int x, y;
	V() {}
	V(int a, int b) {
		x = a, y = b;
	}
};

const int INF = 1e5 + 10;

ll operator ^(V a, V b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

V operator -(V a, V b) {
	return {a.x - b.x, a.y - b.y};
}

bool operator <(V a, V b) {
	return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}

ll len(V a) {
	return 1ll * a.x * a.x + 1ll * a.y * a.y;
}

V all[MAXN];
int used[MAXN];

inline void init() {
	memset(used, 0, sizeof(used));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		all[i] = V(x, y);
	}
	int sz = 0;
	int cur = 0;
	while (sz < n) {
		cur++;
		V l = {INF, INF};
		int id = -1;
		for (int i = 0; i < n; i++) {
			if (used[i] != 0) {
				continue;
			}
			if (all[i] < l) {
				l = all[i];
				id = i;
			}
		}
		if (id == -1) {
			break;
		}
		used[id] = cur;
		sz++;
		V pre = l;
		while (1) {
			V nxt = {INF, INF};
			id = -1;
			for (int i = 0; i < n; i++) {
				if (used[i] != 0)
					continue;
				if ((nxt.x == INF || ((all[i] - pre) ^ (nxt - pre)) > 0) || ((all[i] - pre) ^ (nxt - pre)) == 0 && len(all[i] - pre) < len(nxt - pre)) {
					nxt = all[i];
					id = i;
				}
			}
			if (((l - pre) ^ (nxt - pre)) > 0) {
				break;
			}
			if (id == -1) {
				break;
			}
			if (used[id] == cur) {
				break;
			}
			used[id] = cur;
			sz++;
			pre = nxt;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << used[i] << '\n';
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("L.in", "r", stdin);
		freopen("L.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}