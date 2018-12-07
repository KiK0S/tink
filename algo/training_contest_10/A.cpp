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
#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e6;
#endif

int n;
int q;
int t[4 * MAXN];
int val[MAXN];
int ans[MAXN];
int pnt = 1;

void upd(int v, int tl, int tr, int l, int r, int x) {
	if (tl > r || l > tr) {
		return;
	}
	if (l <= tl && tr <= r) {
		t[v] = x;
		return;
	}
	int tm = (tl + tr) >> 1;
	upd(2 * v, tl, tm, l, r, x);
	upd(2 * v + 1, tm + 1, tr, l, r, x);
	t[v] = t[2 * v] + t[2 * v + 1];
}

int get(int v, int tl, int tr, int l, int r) {
	if (tl > r || l > tr) {
		return 0;
	}
	if (l <= tl && tr <= r) {
		return t[v];
	}
	int tm = (tl + tr) >> 1;
	return get(2 * v, tl, tm, l, r) + get(2 * v + 1, tm + 1, tr, l, r);
}


inline void init() {
	memset(ans, -1, sizeof(ans));
	memset(t, 0, sizeof(t));
}

inline void solve() {
	init();
	for (int i = 0; i < q; i++) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int x;
			cin >> x;
			val[pnt++] = x;
			upd(1, 0, MAXN - 1, pnt - 1, pnt - 1, x);
		}
		else {
			int pos;
			cin >> pos;
			int res = get(1, 0, MAXN - 1, 0, pos - 1);
			upd(1, 0, MAXN - 1, pos, pos, 0);
			cout << res << '\n';
		}
	}	
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
	while (cin >> q)
		solve();
	return 0;
}