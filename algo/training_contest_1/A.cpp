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
	const int MAXN = 15;
#else
	const int MAXN = 1e5;
#endif

int n, k;
pair<int, int> val[MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i].first;
		val[i].second = i;
	}
	sort(val, val + n);
	int uk = 0;
	int ans = 0;
	int id = 0;
	while (uk < n) {
		int start = uk;
		while (uk + 1 < n && val[uk + 1].first - val[uk].first <= k) {
			uk++;
		}
		if (uk - start + 1 > ans) {
			ans = uk - start + 1;
			id = start;
		}
		uk++;
	}
	cout << ans << '\n';
	for (int i = id; i < id + ans; i++) {
		cout << val[i].second + 1 << ' ';
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
	while (cin >> n >> k)
		solve();
	return 0;
}