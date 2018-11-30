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
	const int MAXN = 5001;
#endif

int n;

bitset<MAXN> g[MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			int a;
			cin >> a;
			a--;
			g[a][i] = 1;
		}
	}
	int best_ans = 1e9;
	for (int i = 0; i < n; i++) {
		int ans = 0;
		vector<int> start;
		bitset<MAXN> used;
		for (int j = 0; j < n; j++) {
			used[j] = 1;
		}
		start.push_back(i);
		int level = 0;
		while (start.size()) {
			ans += start.size() * level;
			bitset<MAXN> nxt;
			for (auto v : start) {
				used[v] = 0;
				nxt |= g[v];
			}
			nxt &= used;
			start.clear();
			for (int j = nxt._Find_first(); j < MAXN; j = nxt._Find_next(j)) {
				start.push_back(j);
			}
			// for (int j = 0; j < n; j++) {
			// 	if (nxt[j]) {
			// 		start.push_back(j);
			// 	}
			// }
			level++;
		}
		if (used.count() == 0) {
			best_ans = min(best_ans, ans);
		}
	}
	cout << best_ans + n << '\n';
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