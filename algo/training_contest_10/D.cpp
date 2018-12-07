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
	const int MAXN = 20;
#else
	const int MAXN = 3e5;
#endif

int n;
int a[MAXN];
int b[MAXN];



inline void init() {
	
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> b[i];
	}
	int len = 0;
	int res = 0;
	vector<vector<int>> masks;
	for (int mask = 0; mask < (1 << m); mask++) {
		if (__builtin_popcount(mask) % 2 == 0) {
			continue;
		}
		int last = 1e9;
		int cnt = 0;
		bool ok = 1;
		for (int i = 0; i < m; i++) {
			if (mask & (1 << i)) {
				if (cnt % 2 == 0) {
					if (last <= b[i]) {
						ok = 0;
						break;
					}
				}
				else {
					if (last >= b[i]) {
						ok = 0;
						break;
					}
				}
				last = b[i];
				cnt++;
			}
		}
		if (!ok) {
			continue;
		}
		int pnt1 = 0;
		int pnt2 = 0;
		ok = 1;
		vector<int> rm;
		while (pnt2 < m) {
			while (pnt2 < m && !(mask & (1 << pnt2))) {
				pnt2++;
			}
			if (pnt2 == m) {
				break;
			}
			while (pnt1 < n && a[pnt1] != b[pnt2]) {
				pnt1++;
			}
			if (pnt1 == n) {
				ok = 0;
				break;
			}
			rm.push_back(b[pnt2]);
			pnt1++;
			pnt2++;
		}
		if (ok) {
			if (__builtin_popcount(mask) > len) {
				len = __builtin_popcount(mask);
				masks.clear();
			}
			if (__builtin_popcount(mask) == len) {
				masks.push_back(rm);
			}
		}
	}	
	masks.resize(unique(masks.begin(), masks.end()) - masks.begin());
	assert(len % 2 == 1 || len == 0);
	cout << len << ' ' << (masks.size() % ((int)1e9 + 9)) << '\n';
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