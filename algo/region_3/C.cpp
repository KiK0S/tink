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

int n, m;

inline void init() {

}

inline int go(int a, int b) {
	return min(abs(b - a), n - abs(b - a));
}

inline int f(int a, int b, int mid) {
	return go(a, mid) + go(mid, b);
}

inline void solve() {
	init();
	set<int> all;
	for (int i = 0; i < n; i++) {
		all.insert(i);
	}
	for (int i = 0; i < m; i++) {
		int t, a, b;
		cin >> t;
		if (t == 1) {
			cin >> a;
			a--;
			all.erase(a);
		}
		else {
			cin >> a >> b;
			a--, b--;
			int ans = 1e9;
			auto it = all.lower_bound(a);
			if (it == all.end()) {
				it = all.begin();
			}
			ans = min(ans, f(a, b, *it));
			if (it == all.begin()) {
				it = all.end();
			}
			it--;
			ans = min(ans, f(a, b, *it));
			it = all.lower_bound(b);
			if (it == all.end()) {
				it = all.begin();
			}
			ans = min(ans, f(a, b, *it));
			if (it == all.begin()) {
				it = all.end();
			}
			it--;
			ans = min(ans, f(a, b, *it));
			cout << ans << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}