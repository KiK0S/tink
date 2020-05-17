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
unsigned int a0;

inline void init() {

}

inline void solve() {
	init();
	vector<pair<unsigned int, pair<int, int>>> q;
	vector<pair<unsigned int, int>> nq;
	q.emplace_back(UINT32_MAX, make_pair(-1, -1));
	nq.emplace_back(UINT32_MAX, -1);
	ll ans = 1;
	q.emplace_back(a0, make_pair(0, 0));
	nq.emplace_back(a0, 0);
	unsigned int pre = a0;
	// vector<int> all;
	// all.push_back(a0);
	for (int i = 1; i < n; i++) {
		unsigned int cur = pre * 214013 + 2531011;
		// cin >> cur;
		// all.push_back(cur);
		while (q.back().second.first != -1 && q.back().first <= cur) {
			q.pop_back();
		}
		q.emplace_back(cur, make_pair(q.back().second.second + 1, i));
		// for (auto it : q) {
		// 	cerr << it.second << ' ';
		// }
		// cerr << '\n';
		ans += i - q.back().second.first + 1; 
		// cerr << "!" << i - q.back().second.first + 1 << '\n';
		pre = cur;
	}
	// cerr << '\n';
	// all.push_back(UINT32_MAX);
	pre = a0;
	for (int i = 1; i <= n; i++) {
		unsigned int cur = pre * 214013 + 2531011;
		if (i == n) {
			cur = UINT32_MAX;
		}
		// cur = all[i];
		while (nq.back().second != -1 && (nq.back().first < cur || i == n)) {
			ans += i - nq.back().second - 1;
			// cerr << i - nq.back().second - 1 << ' ';
			nq.pop_back();
		}
		nq.emplace_back(cur, i);
		pre = cur;
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
	while (cin >> n >> a0)
		solve();
	return 0;
}