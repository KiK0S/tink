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

int n, m, w, h;

int dsu[MAXN];
int x[MAXN];
int y[MAXN];
int r[MAXN];

int get(int x) {
	if (dsu[x] == x) {
		return x;
	}
	return dsu[x] = get(dsu[x]);
}

void unite(pair<int, int> p) {
	int a = p.first;
	int b = p.second;
	a = get(a);
	b = get(b);
	if (a == b) {
		return;
	}
	dsu[a] = b;
}


inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
	}
}

int ans[MAXN][5];

inline void solve() {
	init();
	vector<pair<double, pair<int, int>>> edges;
	for (int i = 4; i < n + 4; i++) {
		cin >> x[i] >> y[i] >> r[i];
	}
	for (int i = 4; i < n + 4; i++) {
		for (int j = i + 1; j < n + 4; j++) {
			edges.emplace_back(hypot(x[i] - x[j], y[i] - y[j]) - r[i] - r[j], make_pair(i, j));
		}
		edges.emplace_back(y[i] - r[i], make_pair(i, 0));
		edges.emplace_back(x[i] - r[i], make_pair(i, 1));
		edges.emplace_back(h - y[i] - r[i], make_pair(i, 2));
		edges.emplace_back(w - x[i] - r[i], make_pair(i, 3));
	}
	sort(edges.begin(), edges.end());
	vector<pair<int, pair<int, int>>> query;
	for (int i = 0; i < m; i++) {
		int r, e;
		cin >> r >> e;
		query.emplace_back(2 * r, make_pair(e, i));
	}
	sort(query.begin(), query.end());
	int pnt = 0;
	for (auto it : query) {
		while (pnt < edges.size() && edges[pnt].first < it.first - 1e-9) {
			unite(edges[pnt].second);
			pnt++;
		}
		int id = it.second.second;
		int e = it.second.first;
		ans[id][e] = 1;
		if (e == 1) {
			if (get(1) != get(3) && get(2) != get(1) && get(0) != get(1)) {
				ans[id][4] = 1;
			}
			if (get(0) != get(2) && get(3) != get(0) && get(0) != get(1)) {
				ans[id][2] = 1;
			}
			if (get(2) != get(3) && get(0) != get(1) && get(2) != get(0) && get(1) != get(3)) {
				ans[id][3] = 1;
			}
		}
		if (e == 2) {
			if (get(1) != get(3) && get(2) != get(3) && get(0) != get(3)) {
				ans[id][3] = 1;
			}
			if (get(0) != get(2) && get(1) != get(0) && get(0) != get(3)) {
				ans[id][1] = 1;
			}
			if (get(2) != get(1) && get(0) != get(3) && get(2) != get(0) && get(1) != get(3)) {
				ans[id][4] = 1;
			}
		}
		if (e == 3) {
			if (get(1) != get(3) && get(0) != get(3) && get(2) != get(3)) {
				ans[id][2] = 1;
			}
			if (get(0) != get(2) && get(1) != get(2) && get(2) != get(3)) {
				ans[id][4] = 1;
			}
			if (get(2) != get(3) && get(0) != get(1) && get(2) != get(0) && get(1) != get(3)) {
				ans[id][1] = 1;
			}
		}
		if (e == 4) {
			if (get(1) != get(3) && get(0) != get(1) && get(1) != get(2)) {
				ans[id][1] = 1;
			}
			if (get(0) != get(2) && get(3) != get(2) && get(1) != get(2)) {
				ans[id][3] = 1;
			}
			if (get(2) != get(1) && get(0) != get(3) && get(2) != get(0) && get(1) != get(3)) {
				ans[id][2] = 1;
			}
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 1; j <= 4; j++) {
			if (ans[i][j]) {
				cout << j;
			}
		}
		cout << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("H.in", "r", stdin);
		freopen("H.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> w >> h)
		solve();
	return 0;
}