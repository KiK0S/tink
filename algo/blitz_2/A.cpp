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

#define int ll

int n, q, k;
int sq;

int random_int() {
	return rand();
}

int query(int l, int r) {
	if (!q) {
		exit(0);
	}
	assert(l <= r);
	q--;
	// l = max(1ll, l);
	// r = min(n, r); 
	cout << l << ' ' << r << endl;
	string s;
	cin >> s;
	if (l == r && s == "Yes") {
		exit(0);
	}
	return s == "Yes";
}

inline void init() {
	sq = q;
}

inline void solve() {
	init();
	int l = 1;
	bool f = 0;
	int r = n;
	while (1) {
		l = max(1ll, l);
		r = min(n, r);
		while (l + 4 * k + 1 <= r) {
			// cerr << l << ' ' << r << '\n';
			int mid = (l + r) >> 1;
			int res = query(l, mid);
			if (res == 1) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
			r += k;
			l -= k;
			l = max(1ll, l);
			r = min(n, r);
		}
		// assert(f || sq - q < 1000);
		// f = 1;
		int pos = random_int() % (r - l + 1) + l;
		query(pos, pos);
		l -= k;
		r += k;
	}
}

signed main() {
	srand(time(0));
	cin >> n >> k >> q;
	solve();
	return 0;
}