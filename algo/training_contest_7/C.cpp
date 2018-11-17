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
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e6;
#endif

int n, k;

int val[MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	sort(val, val + n);
	if (val[n - 1 - k] > k) {
		cout << "-1\n";
		return;
	}
	vector<int> ans;
	for (int i = 0; i <= n - 1 - k; i++) {
		ans.push_back(val[i]);
	}
	for (int i = n - 1; i > n - 1 - k; i--) {
		ans.push_back(val[i]);
	}
	reverse(ans.begin(), ans.end());
	int cntbad = 0;
	for (auto it : ans) {
		if (it > cntbad) {
			cntbad++;
		}
	}
	if (cntbad != k) {
		cout << "-1\n";
	}
	else {
		reverse(ans.begin(), ans.end());
		for (auto it : ans) {
			cout << it << ' ';
		}
		cout << '\n';
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
	while (cin >> n >> k)
		solve();
	return 0;
}