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
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e7;
#endif


ll n;
unsigned long long precalc[MAXN];

unsigned long long gs(ll a){ 
	if (a < MAXN) {
		return precalc[a];
	}
	ull x = precalc[MAXN - 1];
	for (ull i = MAXN; i <= a; i++) {
		x += i * i;
	}
	return x;
	// unsigned long long A = a;
	// return (A * (A + 1) / 2) * (2 * A + 1) / 3;
}

inline void init() {
	// precalc[1] = 1;
	// for (ll i = 2; i < MAXN; i++) {
	// 	precalc[i] = precalc[i - 1] + (unsigned long long) (i * i);
	// }
}

inline void solve() {
	init();	
	__int128 ans = 0;
	for (ll x = 1; x * x * x + 2 <= n; x++) {
		ll l = 0;
		ll r = 1e9 + 10;
		while (l + 1 < r) {
			ll mid = (l + r) >> 1;
			if (mid * mid < n - x * x * x) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		__int128 A = l;
		__int128 B = n - x * x * x;
		ans += A * (6 * B - (A + 1) * (2 * A + 1));
	}
	unsigned long long res = ans / 6;
	cout << res << '\n';
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