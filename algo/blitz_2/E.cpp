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
#define int ll
#ifdef DEBUG
	const int MAXN = 100;
#else
	const int MAXN = 3e5;
#endif

int n;
int val[MAXN];
int dp[MAXN];
int pre[MAXN];

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dp[i] = 1e18;
		pre[i] = -1;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		val[i] *= -1;
	}
	dp[0] = -1e18;
	map<int, int> s;
	s[-1e18] = -1;
	for (int i = 0; i < n; i++) {
		int lst = upper_bound(dp, dp + MAXN, val[i]) - dp;
		dp[lst] = val[i];
		pre[i] = s[dp[lst - 1]];
		s[val[i]] = i;
	}
	vector<int> res;
	for (int i = n; i >= 0; i--) {
		if (dp[i] < 1e18) {
			int cur = s[dp[i]];
			while (cur >= 0) {
				res.push_back(cur);
				cur = pre[cur];
			}
			break;
		}
	}
	cout << res.size() << '\n';
	reverse(res.begin(), res.end());
	for (auto it : res) {
		cout << it + 1 << ' ';
	}
	cout << '\n';
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