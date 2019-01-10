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
typedef long long ull;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

int n;
ull mod = 3e9 + 7;
typedef vector<vector<ull>> matr;

matr operator *(matr a, matr b) {
	assert(a[0].size() == b.size());
	matr c(a.size(), vector<ull>(b[0].size()));
	for (int i = 0; i < c.size(); i++) {
		for (int j = 0; j < c[i].size(); j++) {
			for (int k = 0; k < a[0].size(); k++) {
				c[i][j] += (1ll * a[i][k] * b[k][j]) % mod;
				if (c[i][j] >= mod) {
					c[i][j] -= mod;
				}
			}
		}
	}
	return c;
}

matr E = {{1, 0}, {0, 1}};

matr bp(matr a, int N) {
	if (N == 0) {
		return E;
	}
	if (N & 1) {
		return a * bp(a, N - 1);
	}
	return bp(a * a, N / 2);
}

inline void init() {

}

/*
	dp_i = dp_i-1 + dp_i-2
	dp_i-1 = dp_i
	1 1
	1 0
*/

inline void solve() {
	init();
	cout << rand() << '\n';
	// matr a = {{1, 1}, {1, 0}};
	// matr dp_start = {{1, 1}};
	// a = bp(a, n);
	// cout << a[0][0] << '\n';
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