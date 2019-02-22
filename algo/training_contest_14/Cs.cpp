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
	const int MAXN = 20;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 1010;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;
#define int ll
int w, h;
int n, m;

int cnt[MAXN][MAXN];
int sum_l[MAXN][MAXN];
int sum_r[MAXN][MAXN];
int sum_u[MAXN][MAXN];
int sum_d[MAXN][MAXN];

inline void init() {
	memset(cnt, 0, sizeof(cnt));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		cnt[a][b] = -1;
	}
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (cnt[a][b] >= 0) {
			cnt[a][b] += c;
		}
	}
	for (int i = 1; i <= w; i++) {
		int sum = 0;
		for (int j = 1; j <= h; j++) {
			if (cnt[i][j] == -1) {
				sum = 0;
			}
			else {
				sum += cnt[i][j];
			}
			sum_l[i][j] = sum;
		}
	}
	for (int i = 1; i <= w; i++) {
		int sum = 0;
		for (int j = h; j >= 1; j--) {
			if (cnt[i][j] == -1) {
				sum = 0;
			}
			else {
				sum += cnt[i][j];
			}
			sum_r[i][j] = sum;
		}
	}
	for (int i = 1; i <= h; i++) {
		int sum = 0;
		for (int j = w; j >= 1; j--) {
			if (cnt[j][i] == -1) {
				sum = 0;
			}
			else {
				sum += cnt[j][i];
			}
			sum_d[j][i] = sum;
		}
	}
	for (int i = 1; i <= h; i++) {
		int sum = 0;
		for (int j = 1; j <= w; j++) {
			if (cnt[j][i] == -1) {
				sum = 0;
			}
			else {
				sum += cnt[j][i];
			}
			sum_u[j][i] = sum;
		}
	}
	int ans = 0;
	for (int i = 1; i <= w; i++) {
		for (int j = 1; j <= h; j++) {
			if (cnt[i][j] != 0) {
				continue;
			}
			ans = max(ans, sum_u[i][j] + sum_l[i][j] + sum_d[i][j] + sum_r[i][j]);
		}
	}
	cout << ans << '\n';
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
	while (cin >> w >> h >> n >> m)
		solve();
	return 0;
}