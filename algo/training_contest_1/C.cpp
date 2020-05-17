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
	const int MAXN = 1e6;
#else
	const int MAXN = 2e6;
#endif
const int SZ = int(1.5 * MAXN);
#define int ll

int n;
int l, r;
string s;
string all;
int dp[SZ][8];

inline void init() {
	all = "";
	if (count(s.begin(), s.end(), '*')) {
		for (int i = 1; i <= MAXN; i++) {
			if (all.size() + to_string(i).size() >= SZ - 10) {
				break;
			}
			all += to_string(i);
		}
		for (int i = 0; i < all.size(); i++) {
			for (int j = 0; j < 8; j++) {
				dp[i][j] = 1e9;
			}
		}
	}
	else {
		for (int i = 1; i <= MAXN; i++) {
			all += to_string(i);
		}
	}
}

inline void solve() {
	init();
	if (count(s.begin(), s.end(), '*')) {
		int ans = 1e9;
		int r = -1;
		for (int i = 0; i < all.size(); i++) {
			dp[i][0] = i;
			for (int j = 0; j < n; j++) {
				if (s[j] == '?') {
					dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
				}					
				if (s[j] == '*') {
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
					dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
				}
				if (s[j] == all[i]) {
					dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
				}
			}
		}
		for (int i = 0; i < all.size(); i++) {
			if (dp[i][n] < ans) {
				ans = dp[i][n];
				r = i;
			}
		}
		cout << ans + 1 << ' ' << r << '\n';
		return;
	}
	for (int i = 0; i < all.size(); i++) {
		bool ok = 1;
		for (int j = 0; j < n; j++) {
			if (s[j] != all[i + j] && s[j] != '?') {
				ok = 0;
				break;
			}
		}
		if (ok) {
			cout << i + 1 << ' ' << i + n << '\n';
			return;
		}
	}
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