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
	const int MAXN = 2e7 + 1000;
	const int BLOCK = 14;
	const int MAXLOG = 21;
#else
	const int MAXN = 2e7 + 1000;
	const int BLOCK = 14;
	const int MAXLOG = 21;
#endif

const int TWOPOW = 1 << 31;

ll n, b, c, d;
int a[MAXN];
ll x;

inline void init() {
	for (int i = 1; i < n; i++) {
		b = (b * c + d) % TWOPOW;
		a[i] = a[i - 1] + 1 - 2 * (b % 2);
	}
}

inline void solve() {
	init();
	ll anssum = 0;
	ll last = 0;
	for (int i = 0; i < n; i++) {
		int l = (((x + last) % n) + n) % n;
		int r = (l + i) % n;
		if (l > r) {
			swap(l, r);
		}
		last = INT32_MIN;
		for (int j = l; j <= r; j++) {
			last = max(last, 1ll * a[j]);
		}
		anssum += last;
		x = (x * 1103515245ll + 12345) % TWOPOW;
	}
	cout << anssum << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("As.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> a[0] >> b >> c >> d >> x)
		solve();
	return 0;
}