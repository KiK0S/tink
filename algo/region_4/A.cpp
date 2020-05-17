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
#define int ll
int n, Q;
int l[MAXN];
int r[MAXN];
int a[MAXN];

inline void init() {

}

inline void solve() {
	init();
	int ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> l[i] >> r[i];
		if (Q == 1) {
			ans++;
			continue;
		}
		r[i] += l[i];
		int f = a[i];
		int A = 0;
		int B = 1e13;
		while (A + 1 < B) {
			int mid = (A + B) / 2;
			if (f + mid * (2 * Q - 2) > r[i]) {
				B = mid;
			}
			else {
				A = mid;
			}
		}
		int t = f + A * (2 * Q - 2);
		if (t >= l[i] && t <= r[i]) {
			ans++;
			continue;
		}
		A = 0;
		B = 1e13;
		f = Q + Q - a[i];
		while (A + 1 < B) {
			int mid = (A + B) / 2;
			if (f + mid * (2 * Q - 2) > r[i]) {
				B = mid;
			}
			else {
				A = mid;
			}
		}
		t = f + A * (2 * Q - 2);
		if (t >= l[i] && t <= r[i]) {
			ans++;
			continue;
		}
	}
	cout << ans << '\n';
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
	while (cin >> n >> Q)
		solve();
	return 0;
}