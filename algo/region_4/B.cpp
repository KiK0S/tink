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
int a[MAXN];
int c[MAXN];
int pos = 0;
int ans;

int check(int h) {
	int cur = 0;
	for (int i = 0; i < n; i++) {
		cur += abs(a[i] - h) * c[i];
	}
	if (cur < ans) {
		ans = cur;
		pos = h;
	}
	return cur;
}

inline void init() {
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> c[i];
	}
	ans = check(pos);
	int l = 0;
	int r = 1e6 + 10;
	while (l + 100 < r) {
		int m1 = (2 * l + r) / 3;
		int m2 = (l + 2 * r) / 3;
		if (check(m1) < check(m2)) {
			r = m2;
		}
		else {
			l = m1;
		}
	}
	for (int i = l; i <= r; i++) {
		check(i);
	}
	cout << pos << ' ' << ans << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}