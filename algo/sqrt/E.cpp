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
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

int n;

struct seg {
	int l, r;
	seg() {}
	seg(int a, int b) {
		l = a, r = b;
	}
};

seg val[MAXN];
seg t[MAXN][10];

seg merge(seg a, seg b) {
	return seg(max(a.l, b.l), min(a.r, b.r));
}

bool intersect(seg a, seg b) {
	if (a.r < a.l) {
		return 0;
	}
	if (b.r < b.l) {
		return 0;
	}
	return max(a.l, b.l) < min(a.r, b.r);
} 

void build(int l, int r, int level, int len) {
	if (l == r) {
		t[l][level] = val[l];
		return;
	}
	int block = int(sqrt(len));
	seg cur = seg(-1e9, 1e9);
	for (int i = l; i <= r; i += block) {
		build(i, min(r, i + block - 1), level + 1, min(r, i + block - 1) - i + 1);
		cur = merge(cur, t[i][level + 1]);
	}
	t[l][level] = cur;
}

int get(int l, int r, int level, segment need) {
	if (l == r) {
		
	}
}

inline void init() {

}

inline void solve() {
	init();
	
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}