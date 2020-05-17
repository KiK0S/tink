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
	const int MAXN = 100;
#else
	const int MAXN = 2e6;
#endif

int n, k;
int perm[MAXN];
int used[MAXN];
int cnt[MAXN];
int mod2[3];
int counter;
bitset<MAXN> dp;

inline void init() {

}

void dfs(int v) {
	if (used[v]) {
		return;
	}
	used[v] = 1;
	counter++;
	dfs(perm[v]);
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> perm[i];
		perm[i]--;
		assert(perm[i] != i);
	}
	int minans = 1e9;
	int maxans = 0;
	for (int i = 0; i < n; i++) {
		counter = 0;
		dfs(i);
		if (counter) {
			cnt[counter]++;
		}
	}
	for (int i = 2; i <= n; i++) {
		mod2[i % 2] += cnt[i];
		maxans += (i / 2) * cnt[i];
	}
	if (maxans >= k) {
		maxans = 2 * k;
	}
	else {
		int left = k - maxans;
		maxans *= 2;
		for (int i = 1; i >= 0; i--) {
			while (mod2[i] && left) {
				left--;
				maxans += i;
				mod2[i]--;
			}
		}
	}
	dp[0] = 1;
	vector<int> w;
	for (int i = 2; i <= n; i++) {
		if (cnt[i]) {
			int sum = 0; 
			for (int j = 0; j <= 25; j++) {
				if (sum + (1 << j) <= cnt[i]) {
					sum += 1 << j;
					w.push_back((1 << j) * i);
				}
			}
			w.push_back((cnt[i] - sum) * i);
		}
	}
	for (auto x : w) {
		// cerr << x << ' ';
		dp |= dp << x;
	}
	// cerr << '\n';
	// cout << dp << '\n';
	if (dp[k] == 1) {
		minans = k;
	}
	else {
		minans = k + 1;
	}
	cout << minans << ' ' << maxans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}