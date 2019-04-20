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

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, k;

double ans_x[MAXN];
double ans_y[MAXN];

double center_x[MAXN];
double center_y[MAXN];
double dist[MAXN];
double x[MAXN];
double y[MAXN];
int color[MAXN];

double ans = 1ll * INF * INF;

void kek() {
	int sum_x = 0;
	int sum_y = 0;
	for (int i = 0; i < k; i++) {
		int idx = rng() % n;
		center_x[i] = x[idx];
		center_y[i] = y[idx];
	}
	while (clock() * 10 < 9 * CLOCKS_PER_SEC) {
		double cur = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				if (
					(x[i] - center_x[j]) * (x[i] - center_x[j]) + (y[i] - center_y[j]) * (y[i] - center_y[j])
					< 	
					(x[i] - center_x[color[i]]) * (x[i] - center_x[color[i]]) + (y[i] - center_y[color[i]]) * (y[i] - center_y[color[i]])
					) {
					color[i] = j;
				}
			}
			dist[i] = sqrt((x[i] - center_x[color[i]]) * (x[i] - center_x[color[i]]) + (y[i] - center_y[color[i]]) * (y[i] - center_y[color[i]]));
			cur += dist[i];
		}
		if (cur < ans) {
			for (int i = 0; i < k; i++) {
				ans_x[i] = center_x[i];
				ans_y[i] = center_y[i];
			}
		}
		for (int i = 0; i < k; i++) {
			int znam = 0;
			center_y[i] = 0;
			center_x[i] = 0;
			for (int j = 0; j < n; j++) {
				if (color[j] != i) {
					continue;
				}
				center_x[i] += x[j];
				center_y[i] += y[j];
				znam += 1;
			}
			if (znam != 0) {
				center_y[i] /= znam;
				center_x[i] /= znam;
			}
			else {
				int idx = rng() % n;
				// for (int j = 0; j < n; j++) {
				// 	if (dist[j] > dist[idx]) {
				// 		idx = j;
				// 	}
				// }
				center_x[i] = x[idx];
				center_y[i] = y[idx];
				dist[idx] = 0;
			}
		}
	}
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	kek();
	for (int i = 0; i < k; i++) {
		cout << fixed << setprecision(10) << ans_x[i] << ' ' << ans_y[i] << '\n';
	}
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
	while (cin >> n >> k)
		solve();
	return 0;
}