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
	const int MAXC = 10;
#else
	const int MAXN = 1e5 + 1;
	const int MAXC = 1001;
#endif

int n;

int cur[MAXC];

struct ev {
	int coord, l, r, val;
	ev() {}
	ev(int a, int b, int c, int d) {
		coord = a, l = b, r = c, val = d;
	}
};

ev all[2 * MAXN];

inline void init() {
	memset(cur, 0, sizeof(cur));
}

void add(int l, int r, int x) {
	for (int i = l; i <= r; i++) {
		cur[i] += x;
	}
}

int get() {
	int ans = 0;
	for (int i = 0; i < MAXC; i++) {
		if (cur[i] != 0) 
			ans++;
	}
	return ans;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int x_1, x_2, y_1, y_2;
		cin >> x_1 >> y_1 >> x_2 >> y_2;
		all[2 * i] = ev(x_1, y_1, y_2, 1);
		all[2 * i + 1] = ev(x_2 + 1, y_1, y_2, -1);
	}
	sort(all, all + 2 * n, [](ev a, ev b) {
		return a.coord < b.coord;
	});
	int pnt = 0;
	int ans = 0;
	for (int i = 0; i <= MAXC + 1; i++) {
		while (pnt < 2 * n && all[pnt].coord == i) {
			add(all[pnt].l, all[pnt].r, all[pnt].val);
			pnt++;
		}
		ans += get();
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("H.in", "r", stdin);
		freopen("H.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}