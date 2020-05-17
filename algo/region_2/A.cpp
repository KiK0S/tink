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
#define y1 lelkekcheburek
int a, b, x1, x2, y1, y2;

inline void init() {

}

inline void solve() {
	init();
	int x = abs(x2 - x1);
	int y = abs(y2 - y1);	
	int cnt = 0;
	for (int i = (x + a - 1) / a; i >= 1; i--) {
		if (x >= a * i && y <= b * i) {
			cout << x << ' ' << i << '\n';
			cout << y << ' ' << i << '\n';
			return;
		}
	}
	cout << "-1\n";
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
	while (cin >> x1 >> y1 >> x2 >> y2 >> a >> b)
		solve();
	return 0;
}