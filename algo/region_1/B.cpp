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

int n, m;
string a, b;

inline void init() {

}

inline void solve() {
	init();
	int Lmax = 0;
	int Rmax = 0;
	int cur = 0;
	for (auto c : b) {
		if (c == 'L') {
			cur--;
			Lmax = max(Lmax, -cur);
		}
		else {
			cur++;
			Rmax = max(Rmax, cur);
		}
	}
	int ml = 0;
	vector<int> ans(n);
	int last = -1;
	for (int i = 0; i < n; i++) {
		if (a[i] == '#') {
			last = i;
		}
		if (i - Lmax <= last) {
			ans[i]++;
		}
	}
	last = n;
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] == '#') {
			last = i;
		}
		if (i + Rmax >= last) {
			ans[i]++;
		}
	}
	vector<int> res;
	for (int i = 0; i < n; i++) {
		if (!ans[i] && a[i] == 'D') {
			res.push_back(i);
		}
	}
	cout << res.size() << '\n';
	for (auto it : res) {
		cout << it + 1 << ' ';
	}
	cout << '\n';

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
	while (cin >> n >> m >> a >> b)
		solve();
	return 0;
}