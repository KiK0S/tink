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
	const int MAXN = 1e5 + 100;
#endif
const int MAXQ = 1e5 + 3;
int n, m, s, k, t;

int dsu[MAXN];
int root[MAXN];
int sum[MAXN];
int l[MAXQ];
int r[MAXQ];
int pr_dsu[MAXN];
int pr_root[MAXN];
int pr_sum[MAXN];

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
	root[b] = min(root[b], root[a]);
	return 1;
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
		sum[i] = 1;
		root[i] = i;
	}
	for (int i = 0; i < MAXQ; i++) {
		l[i] = -1;
		r[i] = MAXN;
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
	for (int i = 0; i < n; i++) {
		pr_dsu[i] = dsu[i];
		pr_root[i] = root[i];
		pr_sum[i] = sum[i];
	}
	for (int att = 0; att < 20; att++) {
		vector<pair<int, int>> qr(q);
		for (int i = 0; i < q; i++) {
			qr[i] = make_pair((l[i] + r[i]) / 2, i);
		}
		sort(qr.begin(), qr.end());
		vector<bool> can(q);
		for (int i = 0; i < n; i++) {
			dsu[i] = pr_dsu[i];
			root[i] = pr_root[i];
			sum[i] = pr_sum[i];
		}
		vector<pair<int, int>> pre;
		vector<vector<int>> cs(k);
		for (int i = 0; i < k; i++) {
			cs[root[get(i)]].push_back(i);
		}
		for (int i = 0; i < k; i++) {
			for (int j = 0; j + 1 < cs[i].size(); j++) {
				pre.emplace_back(cs[i][j], cs[i][j + 1]);
			}
		}
		int pnt = 0;
		for (int h = 0; h < MAXN; h++) {
			while (pnt < q && qr[pnt].first == h) {
				int id = qr[pnt].second;
				if (get(query[id].first) == get(query[id].second)) {
					r[id] = h;
				}
				else {
					l[id] = h;
				}
				pnt++;
			}
			vector<pair<int, int>> nw;
			for (auto it : pre) {
				for (int c = 1; c <= s; c++) {
					int a = root[get(it.first + c * k)];
					int b = root[get(it.second + c * k)];
					if (unite(it.first + c * k, it.second + c * k) && a < k && b < k) {
						nw.emplace_back(a, b);
					}
				}
			}
			nw.swap(pre);
			nw.clear();
		}
	}
	for (int i = 0; i < q; i++) {
		if (r[i] == MAXN) {
			cout << "-1\n";
			continue;
		}
		cout << r[i] << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("I.in", "r", stdin);
		freopen("I.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k >> s >> m >> t)
		solve();
	return 0;
}