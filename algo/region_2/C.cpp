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
	const int MAXN = 2e5;
#endif

#define int ll

int n;
int dp[MAXN];
int val[MAXN];
string s;
int add[MAXN][2];
int push[2];
const int MOD = 1e9 + 7;

inline void init() {
	memset(dp, 0, sizeof(dp));
	memset(add, 0, sizeof(add));
	memset(push, 0, sizeof(push));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		val[i] = s[i] - '0';
	}
	val[n] = -1;
	dp[0] = 1;
	for (int i = 0; i <= n; i++) {
		push[0] += add[i][0];
		push[0] %= MOD;
		push[1] += add[i][1];
		push[1] %= MOD;
		if (i + 1 < n) {
			dp[i] += push[val[i]];
			if (val[i + 1]) {
				add[i + 2][val[i] ^ 1] += dp[i];
				add[i + 2][val[i] ^ 1] %= MOD;
			}
		}
	}
	cout << (push[0] + push[1]) % MOD << '\n';
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
	while (cin >> n >> s)
		solve();
	return 0;
}