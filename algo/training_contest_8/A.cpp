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
	const int MAXN = 1e5;
#endif
#define int ll
int a, b;

inline void init() {

}

inline void solve() {
	init();
	int ans = 0;
	for (int l = 63; l >= 0; l--) {
		for (int r = l; r >= 0; r--) {
			for (int x = r - 2; x >= 0; x--) {
				int cur = 0;
				for (int i = 0; i <= 63; i++) {
					if (l >= i && i >= r || x >= i) {
						cur += (1ll << i);
					}
				}
				if (a <= cur && cur <= b) {
					ans++;
				}
			}
		}
	}
	cout << ans << '\n';
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
	while (cin >> a >> b)
		solve();
	return 0;
}