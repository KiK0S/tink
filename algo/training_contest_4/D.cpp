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
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif
#define int ll
int n;
int val[MAXN];
int perm[MAXN];
int dp[MAXN];

inline void init() {
 	memset(perm, 0, sizeof(perm));
 	memset(dp, 0, sizeof(dp));
}

inline void solve() {
	init();
	vector<pair<int, int>> sorted;
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		int cop = val[i];
		val[i] -= (i == 0 ? 0ll : val[i - 1]);
		val[i]--;
		dp[i] = 1;
		// for (int j = 0; j < sorted.size(); j++) {
		// 	cerr << sorted[j].first << ' ';
		// }
		// cerr << '\n';
		vector<pair<int, int>> tmp;
		bool flag = 0;
		for (int j = 0; j < sorted.size(); j++) {
			// cerr << val[i] << ' ';
			if (val[i] >= sorted[j].first) {
				perm[i]++;
				val[i] -= sorted[j].first;
				dp[i] += sorted[j].first;
				tmp.push_back(sorted[j]);
			}
			else {
				if (!flag) {
					tmp.emplace_back(dp[i], i);
					flag = 1;
				}
				tmp.push_back(sorted[j]);
				perm[sorted[j].second]++;
			}
		}
		if (!flag) {
			tmp.emplace_back(dp[i], i);
			flag = 1;
		}
		// cerr << '\n';
		// for (int j = 0; j <= i; j++) {
		// 	cerr << perm[j] << ' ';
		// }
		// cerr << '\n';
		val[i] = cop;
		sorted = tmp;
	}
	for (int i = 0; i < n; i++) {
		cout << perm[i] + 1 << ' ';
	}
	cout << '\n';
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