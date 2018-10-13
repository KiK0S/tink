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

pair<int, int> t[4 * MAXN];
int val[MAXN];
int p[MAXN];
int pos[MAXN];
int lft[MAXN];
int rgh[MAXN];

inline void init() {

}

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v] = make_pair(val[tl], tl);
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v] = min(t[2 * v], t[2 * v + 1]);
}

pair<int, int> get(int v, int tl, int tr, int l, int r) {
	if (tl > r || l > tr) {
		return make_pair(1000000000, 1);
	}
	if (l <= tl && tr <= r) {
		return t[v];
	}
	int tm = (tl + tr) >> 1;
	return min(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
}

int slv(int tl, int tr, int pre) {
	if (tl > tr) {
		return -1;
	}
	pair<int, int> got = get(1, 0, n - 1, tl, tr);
	int id = got.second;
	p[pos[id]] = (pre == -1 ? -1 : pos[pre]);
	int l = slv(tl, id - 1, id);
	int r = slv(id + 1, tr, id);
	lft[pos[id]] = (l == -1 ? -1 : pos[l]);
	rgh[pos[id]] = (r == -1 ? -1 : pos[r]);
	return id;
}

int x[MAXN];
int y[MAXN];

inline void solve() {
	init();
	vector<int> coords;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
		coords.push_back(x[i]);
	}
	sort(coords.begin(), coords.end());
	for (int i = 0; i < n; i++) {
		int id = lower_bound(coords.begin(), coords.end(), x[i]) - coords.begin();
		pos[id] = i; 
		val[id] = y[i];
	}
	build(1, 0, n - 1);
	slv(0, n - 1, -1);	
	cout << "YES\n";
	for (int i = 0; i < n; i++) {
		cout << p[i] + 1 << ' ' << lft[i] + 1 << ' ' << rgh[i] + 1 << '\n'; 
	}
}

signed main() {
	#ifdef DEBUG
		freopen("J.in", "r", stdin);
		freopen("J.out", "w", stdout);
	#else
		freopen("tree.in", "r", stdin);
		freopen("tree.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}