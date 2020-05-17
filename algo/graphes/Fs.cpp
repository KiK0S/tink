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
	const int MAXN = 3e5;
#endif

int n, m, q;

vector<int> a[MAXN];
int dsu[MAXN];
set<int> st[MAXN];
int sum[MAXN];
set<int> all;
set<int> coord;

int get(int x) {
	if (dsu[x] == x) {
		return x;
	}
	return dsu[x] = get(dsu[x]);
}

void unite(int a, int b) {
	a = get(a);
	b = get(b);
	if (sum[a] > sum[b]) {
		dsu[b] = a;
		sum[a] += sum[b];
		for (auto x : st[b]) {
			st[a].insert(x);
		}
		all.erase(b);
	}
	else {
		dsu[a] = b;
		sum[b] += sum[a];
		for (auto x : st[a]) {
			st[b].insert(x);
		}
		all.erase(a);
	}
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
		st[i].clear();
		sum[i] = 0;
		a[i].clear();
	}
	all.clear();
	coord.clear();
	for (int i = 0; i < m; i++) {
		all.insert(i);
	}
}

inline void solve() {
	init();
	if (q == 0) {
		cout << n + m - 1 << '\n';
		return;
	}
	for (int i = 0; i < q; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
	}	
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> q)
		solve();
	return 0;
}