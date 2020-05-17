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

int n;

inline void init() {

}

inline void solve() {
	init();
	int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c = 0;
	scanf("%d/%d\n", &a1, &b1);	
	scanf("?/%d\n", &c);
	scanf("%d/%d", &a2, &b2);	
	double L = a1 * c * 1.0 / b1;
	double R = a2 * c * 1.0 / b2;
	if (L > R) {
		cout << "-1\n";
		return;
	}
	for (int res = (int) L - 1; res < (int) R + 3; res++) {
		if (res == 0) {
			continue;
		}
		if (res > L && res < R) {
			cout << res << '/' << c << '\n';
			return;
		}
	}
	cout << "-1\n";
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	solve();
	return 0;
}