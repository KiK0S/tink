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
	const int MAXN = 1e5;
#endif

#define int ll

int n;
int val[MAXN];
int MOD = 1e9 + 7;

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	int ans = 0;
	for (int mask = 1; mask < (1 << n); mask++) {
		int cur = 1;
		for (int i = 0; i < n; i++) {
			if (mask & (1 << i)) {
				cur *= val[i];
			}
		}
		int ok = 1;
		int q = cur;
		for (int x = 2; x * x <= cur; x++) {
			int cnt = 0;
			while (q % x == 0) {
				cnt++;
				q /= x;
			}			
			if (cnt & 1) {
				ok = 0;
			}
		}
		if (q != 1) {
			ok = 0;
		}
		if (ok) {
			ans++;
		}
	}
	cout << ans %  MOD << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}