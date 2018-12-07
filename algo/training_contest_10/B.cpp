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
int a0;
int a[100];

inline void init() {
	memset(a, 0, sizeof(a));
}

int get(int pos, int s) {
	int l = 0;
	int r = s;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if ((mid * (1ll << pos) - s) * (1ll << (n - pos)) < s / n) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	if ((r * (1ll << pos) - s) * (1ll << (n - pos)) != s / n) {
		cout << "-1\n";
		return 0;
	}
	a[pos] = r;
	return 1;
}

inline void solve() {
	init();
	int A = (1ll << n) * a0 * n;
	int B = (n * (1ll << (n - 1)) + 1);
	if (A % B != 0) {
		cout << "-1\n";
		return;
	}
	int s = A / B;
	a[1] = a0;
	for (int i = 2; i <= n; i++) {
		if (!get(i, s)) {
			return;
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << a[i] << ' ';
	}
	cout << '\n';
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
	int t;
	cin >> t;
	while (cin >> n >> a0)
		solve();
	return 0;
}