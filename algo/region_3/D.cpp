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
	const int MAXN = 100;
#else
	const int MAXN = 1e3 + 100;
#endif

int n, m, s, k, t;

int dsu[MAXN];
int sum[MAXN];

inline int get(int x) {
	if (dsu[x] == x) {
		return x;
	}
	return get(dsu[x]);
}

inline int unite(int a, int b) {
	a = get(a);
	b = get(b);
	if (a == b) {
		return 0;
	}
	if (sum[a] > sum[b]) {
		swap(a, b);
	}
	dsu[a] = b;
	sum[b] += sum[a];
	return 1;
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
		sum[i] = 1;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		unite(a, b);
	}
	int q;
	cin >> q;
	vector<pair<int, int>> query(q);
	for (int i = 0; i < q; i++) {
		cin >> query[i].first >> query[i].second;
		query[i].first--, query[i].second--;
	}
	vector<int> ans(q, -1);
	for (int h = 0; h < MAXN; h++) {
		for (int i = 0; i < q; i++) {
			if (ans[i] != -1) {
				continue;
			}
			if (get(query[i].first) == get(query[i].second)) {
				ans[i] = h;
			}
		}
		vector<pair<int, int>> eq;
		for (int a = 0; a < k; a++) {
			for (int b = 0; b < k; b++) {
				if (get(a) == get(b)) {
					for (int r = 1; r <= s; r++) {
						eq.emplace_back(r * k + a, r * k + b);
					}
				}
			}
		}
		for (auto it : eq) {
			unite(it.first, it.second);
		}
	}
	for (auto it : ans) {
		cout << it << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k >> s >> m >> t)
		solve();
	return 0;
}