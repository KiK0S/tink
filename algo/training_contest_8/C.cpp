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
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 20;
#else
	const int MAXN = 2e6;
#endif

int n;
int val[MAXN];
int pos[MAXN];
int pref[MAXN];
int tmin[4 * MAXN];
int tmax[4 * MAXN];
int a[MAXN];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		tmin[v] = a[tl];
		tmax[v] = a[tl];
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	tmin[v] = min(tmin[2 * v], tmin[2 * v + 1]);
	tmax[v] = max(tmax[2 * v], tmax[2 * v + 1]);
}

int get_min(int v, int tl, int tr, int l, int r) {
	if (tl > r || l > tr) {
		return 1e9;
	}
	if (l <= tl && tr <= r) {
		return tmin[v];
	}
	int tm = (tl + tr) >> 1;
	return min(get_min(2 * v, tl, tm, l, r), get_min(2 * v + 1, tm + 1, tr, l, r));
}



int get_max(int v, int tl, int tr, int l, int r) {
	if (tl > r || l > tr) {
		return -1e9;
	}
	if (l <= tl && tr <= r) {
		return tmax[v];
	}
	int tm = (tl + tr) >> 1;
	return max(get_max(2 * v, tl, tm, l, r), get_max(2 * v + 1, tm + 1, tr, l, r));
}

inline void init() {
	if (n == 1) {
		cout << "2\n";
		exit(0);
	}
	memset(pos, -1, sizeof(pos));
}

inline void solve() {
	init();
	n = 1 << n;	
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		pos[val[i]] = i;
		if (pos[val[i] ^ (n - 1)] != -1) {
			a[i] = pos[val[i] ^ (n - 1)];
			a[pos[val[i] ^ (n - 1)]] = i;
		}
	}
	// for (int i = 0; i < n; i++) {
	// 	cerr << a[i] << ' ';
	// }
	// cerr << '\n';
	build(1, 0, n - 1);
	int ans = n * (n + 1) / 2;
	// int r = -1;
	for (int i = 0; i < n; i++) {
		if (a[i] < i) {
			continue;
		}
		int l = i;
		int r = get_max(1, 0, n - 1, i, a[i]);
		// }
		// cerr << l << ' ' << r << '\n';

		while (r < n) {
			if (get_min(1, 0, n - 1, l, r) < i) {
				break;
			}
			while (r < get_max(1, 0, n - 1, l, r)) {
				// cerr << l << ' ' << r << '\n';
				// if (l < i) {
				// 	break;
				// }
				int nr = get_max(1, 0, n - 1, l, r);
				r = nr;
			}
			if (get_min(1, 0, n - 1, l, r) == i && (r - i + 1) % 4 == 0) {
				ans--;
				// cerr << "! " <<l << ' ' << r << '\n';
			}
			r++;
		}
		// r =
		// cerr << '\n';
		// l 
		// = get_min(1, 0, n - 1, l, r);
		// cerr << l << ' ' << r << ' ' << i << '\n';
		// if (l == i && (r - l + 1) % 4 == 0) {
		// 	ans--;
		// }
		// cerr << l << ' ' << r << '\n';
	}
	cout << ans << '\n';
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