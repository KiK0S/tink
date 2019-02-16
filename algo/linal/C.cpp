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
	const int MAXN = 30;
#endif
#define double long double

const double EPS = 1e-9;
int n;

double a[MAXN][MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		int ok = i;
		for (int j = i; j < n; j++) {
			if (abs(a[j][i]) > abs(a[ok][i])) {
				ok = j;
			}
		}
		for (int k = 0; k <= n; k++) {
			swap(a[ok][k], a[i][k]);
		}
		if (abs(a[i][i]) < EPS) {
			continue;
		}
		for (int j = 0; j < n; j++) {
			if (j == i) {
				continue;
			}
			double hm = a[j][i] / a[i][i];
			for (int k = n; k >= 0; k--) {
				a[j][k] -= a[i][k] * hm;
			}
		}
	}
	vector<double> ans;
	bool can = 1;
	bool inf = 1;
	for (int i = 0; i < n; i++) {
		bool zer = 1;
		for (int j = 0; j < n; j++) {
			if (abs(a[i][j]) >= EPS) {
				zer = 0;
			}
		}
		if (zer) {
			if (abs(a[i][i] - a[i][n]) >= EPS) {
				can = 0;
			}
			else {
				inf = 0;
			}
			continue;
		}
		double cur = a[i][n] / a[i][i];
		ans.push_back(cur);
	}
	if (!can) {
		cout << "impossible\n";
		return;
	}
	if (!inf) {
		// while (clock() * 1.0 / CLOCKS_PER_SEC < 1.9) {
		// 	cerr << "kek\n";
		// }
		cout << "infinity\n";
		return;
	}
	cout << "single\n";
	// while (clock() * 1.0 / CLOCKS_PER_SEC < 0.9) {
	// 	cerr << "kek\n";
	// }
	for (auto it : ans) {
		cout << fixed << setprecision(10) << it << ' ';
	}
	cout << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}