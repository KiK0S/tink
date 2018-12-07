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
int x, y;
int q = 0;

int query(int p, int l) {
	int a = 0;
	int c = 0;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		if ((i & p) == p && i <= l) {
			if (c == 0) {
				q++;
				if (q > 19) {
					exit(1);
				}
				cout << "? ";
			}
			v.push_back(i + 1);
			a ^= x; 
			c++;
		}
	}
	if (c == 0) {
		return 1;
	}
	cout << c << ' ';
	for (auto it : v) {
		cout << it << ' ';
	}
	cout << endl;
	int res;
	cin >> res;
	assert(res != -1);
	return res == a;
}

inline void init() {

}

inline void solve() {
	init();
	int pos1 = 0, pos2 = 0;
	int mask = 0;
	for (int i = 0; i < 10; i++) {
		int f = query(1 << i, n);
		if (!f) {
			pos1 = (1 << i);
			mask |= (1 << i);
		}
	}
	vector<int> all;
	for (int i = 0; i < n; i++) {
		if ((i & pos1) == pos1) {
			all.push_back(i);
		}
	}
	int l = -1;
	int r = all.size() - 1;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (!query(pos1, all[mid])) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	r = all[r];
	pos1 = r;
	pos2 = mask ^ pos1;
	if (pos1 > pos2) {
		swap(pos1, pos2);
	}
	cout << "! " << pos1 + 1 << ' ' << pos2 + 1 << endl;
}

signed main() {
	cin >> n >> x >> y;
	solve();
	return 0;
}