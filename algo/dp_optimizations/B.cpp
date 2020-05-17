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
	const int MAXN = 3e5;
#endif

#define int ll

const int INF = 1e9 + 10;

int n, m;
int coord[MAXN];
int cost[MAXN];


struct line {
	int k, b;
	line() {}
	line(int a, int _b) {
		k = a, b = _b;
	}
	int get(int x) {
		return k * x + b;
	}
};

bool operator < (line a, line b) {
	return a.k > b.k || a.k == b.k && a.b > b.b;
}

int cross(line a, line b) {
	if (a.k < b.k) {
		swap(a, b);
	}
	int x = (b.b - a.b) / (a.k - b.k);		
	if (b.b < a.b) {
		x--;
	}
	return x;
}

struct CHT {
	vector<line> lines;
	vector<int> dots;
	
	CHT() {}

	void add(line cur) {
		while (lines.size() && lines.back().get(dots.back()) > cur.get(dots.back())) {
			lines.pop_back();
			dots.pop_back();
		}
		if (lines.empty()) {
			dots.push_back(-INF);
		}
		else {
			if (lines.back().k != cur.k) {
				dots.push_back(cross(lines.back(), cur));
			}
			else {
				lines.pop_back();
			}
		}
		lines.push_back(cur);
	}

	int get(int x) {
		int pos = lower_bound(dots.begin(), dots.end(), x) - dots.begin();
		pos--;
		return lines[pos].get(x);
	}

	void build(vector<line> all) {
		
		for (line l : all) {
			add(l);
			// cerr << l.k << ' ' << l.b << '\t';
		}
		// cerr << '\n';
		// for (auto l : lines) {
		// 	cerr << l.k << ' ' << l.b << '\t';
		// }	
		// cerr << '\n';
		// for (auto it : dots) {
		// 	cerr << it << '\t';
		// }
		// cerr << '\n';
		// for (int i = 0; i + 1 < lines.size(); i++) {
		// 	assert(lines[i].get(dots[i + 1]) <= lines[i + 1].get(dots[i + 1]));
		// 	assert(lines[i].get(dots[i + 1] + 1) >= lines[i + 1].get(dots[i + 1] + 1));
		// }
	}
};

struct segtree {
	vector<line> lines;
	CHT cht;
};

segtree t[4 * MAXN];
int line_k[MAXN];
int line_b[MAXN];
int pnt;

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].lines.emplace_back(line_k[pnt], line_b[pnt]);
		t[v].cht.build(t[v].lines);
		pnt++;
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v].lines.resize(tr - tl + 1);
	merge(t[2 * v].lines.begin(), t[2 * v].lines.end(), t[2 * v + 1].lines.begin(), t[2 * v + 1].lines.end(), t[v].lines.begin());
	t[v].cht.build(t[v].lines);
}

int get(int v, int tl, int tr, int l, int r, int x) {
	if (tl > r || l > tr || r < l) {
		return (ll) 4e18;
	}
	// cerr << v << ' ' << tl << ' ' << tr << ' ' << l << ' ' << r << '\n';
	if (l <= tl && tr <= r) {
		// cerr << "got" << ' ' << tl << ' ' << tr << '\n';
		return t[v].cht.get(x);
	}
	int tm = (tl + tr) >> 1;
	return min(get(2 * v, tl, tm, l, r, x), get(2 * v + 1, tm + 1, tr, l, r, x));
}

inline void init() {
	pnt = 0;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> coord[i] >> cost[i];
		line_b[i] = coord[i] * coord[i] + cost[i];
		line_k[i] = coord[i] * -2;
	}
	build(1, 0, n - 1);
	for (int i = 0; i < m; i++) {
		int x, bad;
		cin >> x >> bad;
		int last = 0;
		int ans = 4e18;
		vector<int> bads(bad);
		for (int j = 0; j < bad; j++) {
			int _x;
			cin >> _x;
			bads[j] = _x;
		}
		sort(bads.begin(), bads.end());
		for (int _x : bads) {
			_x--;
			// cerr << "get " << last << ' ' << _x - 1 << '\n';
			ans = min(ans, get(1, 0, n - 1, last, _x - 1, x) + x * x);
			last = _x + 1;
		}
		// cerr << "get " << last << ' ' << n - 1 << '\n';
		ans = min(ans, get(1, 0, n - 1, last, n - 1, x) + x * x);
		cout << ans << '\n';
		// cerr << ans << '\n';
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}