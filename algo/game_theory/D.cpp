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
	const int MAXN = 50;
#else
	const int MAXN = 200;
#endif

int n;
int dp[MAXN];

int mex(vector<int> all) {
	sort(all.begin(), all.end());
	all.resize(unique(all.begin(), all.end()) - all.begin());
	for (int i = 0; i < all.size(); i++) {
		if (i != all[i]) {
			return i;
		}
	}
	return all.size();
}

inline void init() {
	dp[0] = 0;
	for (int i = 1; i < MAXN; i++) {
		vector<int> all;
		for (int j = 0; j < i; j++) {
			all.push_back(dp[j]);
		}
		for (int j = 1; j < i; j++) {
			all.push_back(dp[j] ^ dp[i - j]);
		}
		// for (auto it : all) {
		// 	cerr << it << ' ';
		// }
		// cerr << '\n';
		dp[i] = mex(all);
		cerr << dp[i] << ' ';
	}
	cerr << '\n';
}

inline void solve() {
	int x = 0;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		if (a % 4 == 0) {
			a = a - 1;
		}
		else if (a % 4 == 3) {
			a += 1;
		}
		x ^= a;
	}
	if (x == 0) {
		cout << "SECOND\n";
	}
	else {
		cout << "FIRST\n";
	}
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
	int t;
	cin >> t;
	init();
	while (cin >> n)
		solve();
	return 0;
}