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
	const int MAXN = 2e6 + 10;
#endif

int n, m, k;

int dp[MAXN];
int can[MAXN];

inline void init() {
	memset(dp, 0, sizeof(dp));
}

inline void solve() {
	init();
	for (int i = 0; i < k; i++) {
		cin >> can[i];
	}
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < k; j++) {
			if (i - can[j] < 0) {
				continue;
			}
			if (dp[i - can[j]] == 0) {
				dp[i] = 1;
				break;
			}
		}
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		assert(a < MAXN);
		cout << (dp[a] ? "First\n" : "Second\n");
	}
}

signed main() {
	#ifdef DEBUG
		freopen("2A.in", "r", stdin);
		freopen("2A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> k;
	// while (cin >> k)
		solve();
	return 0;
}