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
	const int MAXN = 1e5 + 10;
#endif

int n, m, k;

struct V {
	int x, y;
	V() {}
	V(int a, int b) {
		x = a, y = b;
	}
};

V operator + (V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

V operator - (V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

ll operator * (V a, V b) {
	return 1ll * a.x * b.x + 1ll * a.y * b.y;
}

ll operator ^ (V a, V b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

istream & operator >> (istream &in, V &a) {
	in >> a.x >> a.y;
	return in;
}

V all[MAXN];

int s(V a, V b, V c) {
	return abs((b - a) ^ (c - a));
}

int check(V a, V b, V c, V x) {
	return s(a, b, c) == s(x, a, b) + s(x, b, c) + s(x, c, a);
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> all[i];
	}
	for (int i = 0; i < m; i++) {
		V x;
		cin >> x;
		int l = 1;
		int r = n - 1;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			V a = all[mid] - all[0];
			V b = x - all[0];
			if ((a ^ b) >= 0) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		// cerr << i << ' ' << l << ' ' << r << '\n';
		if (check(all[0], all[l], all[r % n], x)) {
			k--;
			// cerr << i << '\n';
		}
	}
	if (k <= 0) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
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
	while (cin >> n >> m >> k)
		solve();
	return 0;
}