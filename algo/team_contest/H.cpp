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
	const int MAXN = 2201;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const ll INF = 1e18;
const int MOD = 1e9 + 7;

int n, k;
ll a[MAXN];
ll b[MAXN];
pair<ll, int> dp[MAXN][MAXN];

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = make_pair(INF, 0);
		}
	}
}

pair<ll, int> check(ll X) {
	init();
	dp[0][0] = make_pair(0ll, 0);
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (i < n) {
				dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
			}
			if (j < n) {
				dp[i][j + 1] = min(dp[i][j + 1], dp[i][j]);
			}
			if (i <= j && j < n) {
				dp[i + 1][j + 1] = min(dp[i + 1][j + 1], make_pair(dp[i][j].first + X + a[i] + b[j], dp[i][j].second + 1));
			}
		}
	}
	return dp[n][n];
}

inline void solve() {
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int j = 0; j < n; j++) {
		cin >> b[j];
	}
	ll l = -1e14;
	ll r = 1;
	while (l + 1 < r) {
		ll mid = (l + r) >> 1;
		pair<ll, int> x = check(mid);
		if (x.second >= k) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	// cerr << l << ' ' << r << '\n';
	{
		pair<ll, int> x = check(l);
		cout << x.first - l * x.second << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("H.in", "r", stdin);
		freopen("H.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}