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
	const int MAXN = 1e3;
#else
	const int MAXN = 44e5 + 1000;
#endif
int n;

int dp[MAXN];
int pre[MAXN];

inline void init() {

}

inline void solve() {
	init();
	vector<pair<int, int>> go = {{1, 15}, {5, 70}, {10, 125}, {20, 230}, {60, 440}};
	for (int i = 0; i < MAXN - 500; i++) {
		for (int j = 0; j < 5; j++) {
			auto it = go[j];
			if (dp[i + it.second] < dp[i] + it.first) {
				dp[i + it.second] = dp[i] + it.first;
				pre[i + it.second] = j;
			}
		}
	}
	vector<int> ans(5);
	for (int i = 0; i < MAXN; i++) {
		if (dp[i] >= n) {
			while (i > 0) {
				ans[pre[i]]++;
				i -= go[pre[i]].second;
			}
			break;
		}
	}
	for (auto it : ans) {
		cout << it << ' ';
	}
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