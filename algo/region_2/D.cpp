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
	const int MAXN = 1e5 + 20;
#endif

int n;
int dp[MAXN];
int val[MAXN];
int mod = 1e9 + 7;

inline void init() {
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
}

inline void solve() {
	init();
	int ans = 0;
	for (int l = 0; l < n; l++) {
		int sum = 1;
		memset(dp, 0, sizeof(dp));
		for (int r = l; r < n; r++) {
			int last = dp[val[r]];
			dp[val[r]] = sum;
			sum <<= 1;
			sum += -last;
			sum %= mod;
			sum += mod;
			sum %= mod;
			ans += sum;
			ans %= mod;
			cerr << sum << ' ';
			// cerr << l << ' ' << r << '\t' << sum << '\n';
		}
		cerr << '\n';
	}
	cout << ans << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}