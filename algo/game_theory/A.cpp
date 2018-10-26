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


inline void init() {

}

inline void solve() {
	init();
	int ans = 0;
	vector<int> val(63);
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		for (int j = 0; j < 62; j++) {
			if ((1ll << j) >= l && (1ll << j) <= r) {
				val[j] = (1ll << j);
			}
		}
		for (int j = 0; j < 62; j++) {
			int cur = (1ll << j);
			for (int k = 61; k >= 0; k--) {
				if (k == j) {
					continue;
				}
				int nxt = cur | (1ll << k);
				if (nxt <= r) {
					cur = nxt;
				}
			}
			if (cur >= l && cur <= r) {
				val[j] = cur;
			}
		}


		if (l & 1) {
			ans ^= l;
			l++;
		}
		if (!(r & 1)) {
			ans ^= r;
			r--;
		}
		if ((r - l + 1) % 4 != 0) {
			ans ^= 1;
		}
	}
	if (ans == 0) {
		cout << "Lose\n";
		return;
	}
	cout << "Win\n";
	int mxlog;
	for (int i = 61; i >= 0; i--) {
		if (ans & (1ll << i)) {
			mxlog = i;
			break;
		}
	}
	for (int i = 61; i >= 0; i--) {
		auto it = val[i];
		if (it & (1ll << mxlog)) {
			cout << it << ' ' << (ans ^ it) << '\n';
			return;
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}