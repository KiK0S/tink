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
	const int MAXN = 2e5;
#endif

int n, m;
int val[MAXN];

struct segtree {
	vector<int> q;
};

segtree t[4 * MAXN];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].q.push_back(val[tl]);
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v].q.resize(t[2 * v].q.size() + t[2 * v + 1].q.size());
	merge(t[2 * v].q.begin(), t[2 * v].q.end(), t[2 * v + 1].q.begin(), t[2 * v + 1].q.end(), t[v].q.begin());
}

int get(int v, int tl, int tr, int l, int r, int a, int b) {
	if (tl > r || l > tr) {
		return 0;
	}
	if (l <= tl && tr <= r) {
		// for (auto it : t[v].q) {
		// 	cerr << it << ' ';
		// }
		return upper_bound(t[v].q.begin(), t[v].q.end(), b) - upper_bound(t[v].q.begin(), t[v].q.end(), a - 1);
	}
	int tm = (tl + tr) >> 1;
	return get(2 * v, tl, tm, l, r, a, b) + get(2 * v + 1, tm + 1, tr, l, r, a, b);
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	build(1, 0, n - 1);
	for (int i = 0;  i < m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--, b--;
		cout << get(1, 0, n - 1, a, b, c, d) << '\n';
		cerr << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}