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
	const int MAXN = 1 << 18;
#else
	const int MAXN = 1 << 18;
#endif

int n;

int t[MAXN];
int rt[MAXN];
int ct[MAXN];
int pos[MAXN];
int h[MAXN];
int depth[MAXN];
vector<int> ans;

int mn(int v) {
	return min(t[2 * v], t[2 * v + 1]);
}

void calc(int v, int c = 0) {
	if (v > n) {
		h[v] = 0;
		return;
	}
	depth[v] = c;
	calc(2 * v, c + 1);
	calc(2 * v + 1, c + 1);
	h[v] = max(h[2 * v], h[2 * v + 1]) + 1;
}

void clear(int v) {
	if (v > n) {
		return;
	}
	t[v] = ct[v];
	pos[t[v]] = v;
	clear(2 * v);
	clear(2 * v + 1);
}

void fill(int v, vector<int> &c) {
	queue<int> q;
	q.push(v);
	while (q.size()) {
		int cur = q.front();
		q.pop();
		if (cur > n) {
			continue;
		}
		// cerr << cur << ' ' << t[cur] << '\n';
		c.push_back(t[cur]);
		q.push(cur * 2);
		q.push(cur * 2 + 1);
	}
}

void paint(int v, vector<int> &c) {
	queue<int> q;
	q.push(v);
	int pnt = 0;
	while (q.size()) {
		int cur = q.front();
		q.pop();
		if (cur > n) {
			continue;
		}
		t[cur] = c[pnt++];
		pos[t[cur]] = cur;
		q.push(cur * 2);
		q.push(cur * 2 + 1);
	}	
}

void dfs(int v) {
	if (v > n) {
		return;
	}
	vector<pair<vector<int>, int>> kek;
	// do nothing
	kek.push_back({{t[v], rt[2 * v], rt[2 * v + 1]}, 0});
	// swap with l
	kek.push_back({{t[2 * v], min(t[v], mn(2 * v)), rt[2 * v + 1]}, 1});
	// swap with r
	kek.push_back({{t[2 * v + 1], rt[2 * v], min(t[v], mn(2 * v + 1)), t[2 * v]}, 2});
	// do both
	kek.push_back({{t[2 * v + 1], min(t[v], mn(2 * v)), min(t[2 * v], mn(2 * v + 1)), t[v]}, 3});
	bool fk = ((vector<int>){t[2 * v + 1], min(t[v], mn(2 * v)), min(t[2 * v], mn(2 * v + 1))} == (vector<int>){t[2 * v + 1], rt[2 * v], min(t[v], mn(2 * v + 1))});
	sort(kek.begin(), kek.end());
	int lt = t[v];
	if (kek[0].second & 1) {
		swap(t[v], t[2 * v]);
	}
	if (kek[0].second & 2) {
		swap(t[v], t[2 * v + 1]);
	}
	pos[t[v]] = v;
	dfs(2 * v);
	dfs(2 * v + 1);
	vector<int> cur;
	fill(v, cur);
	// cerr << v << '\n';
	// for (auto it :cur) {
	// 	cerr << it << ' ';
	// }
	// cerr << '\n';
	if (fk) {
		t[v] = lt;
		pos[t[v]] = v;
		clear(2 * v);
		clear(2 * v + 1);
		swap(kek[0], kek[1]);
		if (kek[0].second & 1) {
			swap(t[v], t[2 * v]);
		}
		if (kek[0].second & 2) {
			swap(t[v], t[2 * v + 1]);
		}
		pos[t[v]] = v;
		dfs(2 * v);
		dfs(2 * v + 1);
		vector<int> nx;
		fill(v, nx);
		cur = min(cur, nx);
	}
	paint(v, cur);
}

inline void init() {
	for (int i = 0; i < (MAXN); i++) {
		ct[i] = t[i] = rt[i] = MAXN - 1;
	}
	ans.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		ans[i] = n - i + 1;
	}
}


inline void solve() {
	init();
	for (int i = 1; i <= n; i++) {
		cin >> t[i];
		pos[t[i]] = i;
		ct[i] = t[i];
	}
	for (int i = 1; i <= n; i++) {
		rt[i] = min(min(t[i], t[2 * i]), t[2 * i + 1]);
	}
	calc(1);
	dfs(1);
	for (int i = 1; i <= n; i++) {
		cout << t[i] << ' ';
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}