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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, k;

int l[MAXN], r[MAXN], a[MAXN], b[MAXN];


inline void init() {
	n *= 2;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i] >> a[i];
		l[i]--, r[i]--;
	}
	for (int mask = 0; mask < (1 << n); mask++) {
		if (__builtin_popcount(mask) * 2 != n) {
			continue;
		}
		vector<int> can_a(n), can_b(n);
		int sum_a = 0, sum_b = 0;
		int ok = 1;
		for (int i = 0; i < n; i++) {
			if (mask & (1 << i)) {
				sum_a += a[i];
				if (can_a[l[i]]) {
					ok = 0;
				}
				can_a[l[i]] = 1;
			}
			else {
				sum_b += a[i];
				if (can_b[r[i]]) {
					ok = 0;
				}
				can_b[r[i]] = 1;
			}
		}
		if (ok && abs(sum_b - sum_a) <= k) {
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}