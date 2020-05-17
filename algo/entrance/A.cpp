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

int n;

int val[MAXN];

inline void init() {

}

inline void solve() {
	init();
	int _min = 1e9;
	int _max = -1e9;
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		_min = min(_min, val[i]);
		_max = max(_max, val[i]);
	}
	for (int i = 0; i < n; i++) {
		if (val[i] == _max) {
			val[i] = _min;
		}
		cout << val[i] << ' ';
	}
	cout << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}