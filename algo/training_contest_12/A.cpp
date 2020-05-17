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
	const int MAXN = 11;
#endif

int n, m;
int val[MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int c;
		cin >> c;
		for (int j = 0; j < c; j++) {
			int a;
			cin >> a;
			a--;
			val[i] |= (1 << a);
		}
	}
	int res_mask = 0;
	int ans = 0;
	for (int mask = 0; mask < (1 << m); mask++) {
		int cur = 0;
		for (int j = 0; j < m; j++) {
			if (mask & (1 << j)) {
				cur |= val[j];
			}
			else {
				cur |= (1 << n) - 1 - val[j];
			}
		}
		if (__builtin_popcount(cur) > __builtin_popcount(ans)) {
			res_mask = mask;
			ans = cur;
		}
	}
	while (m--) {
		cout << (1 ^ (res_mask & 1));
		res_mask >>= 1;
	}
	cout << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}