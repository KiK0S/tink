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
vector<pair<int, int>> ans;

void _do(int tl, int tr) {
	if (tl + 1 == tr) {
		ans.emplace_back(tl, tr);
		return;
	}
	int tm = (tl + tr) >> 1;
	_do(tl, tm);
	_do(tm + 1, tr);
	for (int i = 0; i < tm + 1 - tl; i++) {
		ans.emplace_back(tl + i, tm + 1 + i);
	}
}

inline void init() {

}

inline void solve() {
	init();
	if (__builtin_popcount(n) == 1) {
		_do(0, n - 1);
	}
	cout << ans.size() << '\n';
	for (auto it : ans) {
		cout << it.first + 1 << ' ' << it.second + 1 << '\n';
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
	cin >> n;
	solve();
	return 0;
}