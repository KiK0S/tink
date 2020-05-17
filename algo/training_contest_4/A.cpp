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
#define int long long
int n;

int val[MAXN];


inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}	
	int v, w, q;
	cin >> w >> v >> q;
	for (int i = 0; i < q; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		double ans = (val[n - 1] - a) * 1.0 / c + b;
		int l = 0;
		int r = n - 1;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (val[mid] <= a) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		// cerr << l << ' ';
		int id = l;
		{
			double tin = b + 1.0 * abs(a - val[id]) / c;
			int _l = -1;
			int _r = 1e9;
			while (_l + 1 < _r) {
				int mid = (_l + _r) >> 1;
				if (mid * w + val[id] * 1.0 / v >= tin) {
					_r = mid;
				}
				else {
					_l = mid;
				}
			}
			double tout = _r * w + val[n - 1] * 1.0 / v;
			ans = min(ans, tout);
			// cerr << id << ' ' << tout << '\n';
		}
		id = l + 1;
		{
			double tin = b + 1.0 * abs(a - val[id]) / c;
			int _l = -1;
			int _r = 1e9;
			while (_l + 1 < _r) {
				int mid = (_l + _r) >> 1;
				if (mid * w + val[id] * 1.0 / v >= tin) {
					_r = mid;
				}
				else {
					_l = mid;
				}
			}
			double tout = _r * w + val[n - 1] * 1.0 / v;
			ans = min(ans, tout);
			// cerr << id << ' ' << tout << '\n';
		}
		cout << fixed << setprecision(10) << ans << '\n';
	}

}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}