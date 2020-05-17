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

int n;

inline void init() {

}



inline void solve() {
	init();
	vector<int> res(n);
	vector<int> a(n + 1);
	vector<int> cur;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		res[i - 1] = n - i + 1;
	}
	for (int mask = 0; mask < (1 << (n - 1)); mask++) {
		cur = a;
		vector<int> ch;
		for (int i = 2; i <= n; i++) {
			if (mask & (1 << (i - 2))) {
				swap(cur[i], cur[i / 2]);
			}
		}
		for (int i = 1; i <= n; i++) {
			ch.push_back(cur[i]);
		}
		res = min(res, ch);
	}
	for (auto it : res) {
		cout << it << ' ';
	}
	cout << '\n';
}


signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("Cs.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}