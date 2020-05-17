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
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

int n, m, k;
int a[MAXN];
int b[MAXN];

inline void init() {

}

inline void solve() {
	init();
	int A = 0, B = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		A += a[i];
	}
	for (int j = 0; j < m; j++) {
		cin >> b[j];
		B += b[j];
	}
	if (A >= B) {
		cout << (k + B - 1) / B + 1 << '\n';
		return;
	}
	else {
		cout << (k + A - 1) / A + 1 << '\n';
	}
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
	while (cin >> n >> m >> k)
		solve();
	return 0;
}