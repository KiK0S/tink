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
	const int MAXN = 3e5;
#endif

int n;
int s[MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	if (n % 2 == 1) {
		cout << "0\n";
		return;
	}
	map<int, set<int>> fst;
	int ans = 1e9;
	for (int i = 0; i < n; i++) {
		fst[s[i]].insert(i);
	}
	for (int i = 0; i < n; i++) {
		int id = n - 1 - i;
		auto it = fst[s[i]].lower_bound(id);
		if (it != fst[s[i]].end()) {
			if (*it != i) {
				ans = min(ans, abs(id - *it));
			}
		}
		if (it != fst[s[i]].begin()) {
			it--;
			if (*it != i) {
				ans = min(ans, abs(id - *it));
			}
		}
	}
	cout << ans << '\n';
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