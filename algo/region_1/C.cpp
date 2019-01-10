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

inline void init() {

}

inline void solve() {
	init();
	map<int, int> all;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		int cur = 1;
		while (a % 2 == 0) {
			cur *= 2;
			a /= 2;
		}
		all[a] += cur;
	}
	int last = 0;
	for (auto it : all) {
		if (it.second >= 2) {
			all[it.first * 2] += it.second / 2;
		}
		last = it.first;
	}
	cout << last << '\n';
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