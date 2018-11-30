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
	const int MAXN = 3000;
#endif
#define int ll
int n, q;
int g[MAXN][MAXN];
int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

inline void init() {

}

inline void solve() {
	init();
	int cur = 1;
	int x = n;
	int y = n;
	g[x][y] = cur++;
	int pnt = 0;
	for (int i = 1; i <= 2 * n + 1; i++) {
		for (int j = 0; j < i; j++) {
			x += dx[pnt];
			y += dy[pnt];
			g[x][y] = cur++;
		}
		pnt++;
		pnt %= 4;
		if (i == 2 * n + 1) {
			break;
		}
		for (int j = 0; j < i; j++) {
			x += dx[pnt];
			y += dy[pnt];
			g[x][y] = cur++;
		}
		pnt++;
		pnt %= 4;	
	}
	// for (int i = 0; i <= 2*n; i++) {
	// 	for (int j = 0; j <= 2 * n; j++) {
	// 		cout << g[i][j] << '\t';
	// 	}
	// 	cout << '\n';
	// }
	for (int i = 0; i < q; i++) {
		int l, r, t, b;
		cin >> b >> r >> t >> l;
		int ans = 0;
		if (b == r && t == l) {
			int x = b;
			int y = r;
			if (x == 0 && y == 0) {
				cout << "1\n";
				continue;
			}
			if (y >= x) {
				ans = (2 * (abs(y))) * (2 * (abs(y))) + 1 + y - x;
			}
			else {
				ans = (2 * abs(y) + 1) * (2 * abs(y) + 1) + 1 + 
			}
		}
		l += n;
		b += n;
		r += n;
		t += n;
		l = 2 * n - l;
		r = 2 * n - r;
		// cerr << l << ' ' << r << ' ' << b << ' ' << t << '\n';
		for (int j = l; j <= r; j++) {
			for (int k = b; k <= t; k++) {
				ans += g[j][k];
				ans %= (int)(1e9 + 7);
			}
		}
		cout << ans << '\n';
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
	while (cin >> n >> q)
		solve();
	return 0;
}