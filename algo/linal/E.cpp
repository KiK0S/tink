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

const int MAXN = 50;

#define int ll
ll n;

ll dp[MAXN][10];

inline void init() {
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i < 10; i++) {
		dp[1][i] = 1;
	}
}

inline void solve() {
	init();
	for (int i = 2; i < MAXN; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = j; k < 10; k++) {
				dp[i][j] += dp[i - 1][k];
			}
		}
	}
	string ans;
	int last = 0;
	for (int i = MAXN - 1; i >= 1; i--) {
		for (int j = last; j < 10; j++) {
			if (dp[i][j] < n) {
				n -= dp[i][j];
			}
			else {
				last = j;
				ans.push_back('0' + j);
				break;
			}
		}
	}
	reverse(ans.begin(), ans.end());
	while (ans.back() == '0') {
		ans.pop_back();
	}
	reverse(ans.begin(), ans.end());
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}