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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));
#define int ll
const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
int a = 0, b = 0;
int c, d;

int dist(int xa, int ya, int xb, int yb) {
	return abs(xa - xb) + abs(ya - yb);
}

int dx[] = {1, -1, 1, -1};
int dy[] = {1, 1, -1, -1};
int x[MAXN];
int y[MAXN];

inline void init() {

}

int check(int dir) {
	int cur_x = a;
	int cur_y = b;
	for (int i = 0; i < n; i++) {
		if (x[i] * dx[dir] + y[i] * dy[dir] > 0) {
			cur_y += y[i];
			cur_x += x[i];
		}
	}
	return dist(cur_x, cur_y, c, d);
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		ans = max(ans, check(i));
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> c >> d)
		solve();
	return 0;
}