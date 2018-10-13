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

int n, p;

inline void init() {

}

inline void solve() {
	init();
	int cur = 0;
	for (int i = 1; i <= n; i++) {
		cur += p;
		cur %= i;
	}	
	cout << cur + 1 << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("I.in", "r", stdin);
		freopen("I.out", "w", stdout);
	#else
		freopen("joseph.in", "r", stdin);
		freopen("joseph.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> p)
		solve();
	return 0;
}