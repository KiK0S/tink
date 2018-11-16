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
#define int ll
#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

int n;

vector<int> a[MAXN];
int start[MAXN];

struct segtree {
	vector<int> f;
	vector<int> coords;
	int getid(int a) {
		return lower_bound(coords.begin(), coords.end(), a) - coords.begin();
	}

	int f_less(int a) {
		return lower_bound(coords.begin(), coords.end(), a) - coords.begin() - 1;
	}

	int get(int id) {
		// cerr << "start " << id << '\n';
		id = f_less(id);
		// cerr << "nxt " << id << '\n';
		int ans = 0;
		for (int i = id + 1; i > 0; i -= i & -i) {
			ans += f[i];
		}
		return ans;
	}

	void upd(int id, int x) {
		// cerr << "start " << id << '\n';
		id = getid(id);
		// cerr << "nxt " << id << '\n';
		for (int i = id + 1; i < f.size(); i += i & -i) {
			f[i] += x;
		}
	}

	void u() {
		coords.resize(unique(coords.begin(), coords.end()) - coords.begin());
	}

	void print() {
		// cerr << "print ";
		// for (auto it : coords) {
		// 	cerr << it << ' ';
		// }
		// cerr << '\n';
	}
};

segtree t[4 * MAXN];

void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v].coords = a[tl];
		t[v].u();
		t[v].f.resize(t[v].coords.size() + 1);
		t[v].upd(start[tl], 1);
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v].coords.resize(t[2 * v].coords.size() + t[2 * v + 1].coords.size());
	merge(t[2 * v].coords.begin(), t[2 * v].coords.end(), t[2 * v + 1].coords.begin(), t[2 * v + 1].coords.end(), t[v].coords.begin());
	t[v].u();
	t[v].f.resize(t[v].coords.size() + 1);
	for (int i = tl; i <= tr; i++) {
		t[v].upd(start[i], 1);
	}
}

void upd(int v, int tl, int tr, int pos, int x) {
	// cerr << "upd " << start[pos] << " -1\n";
	t[v].upd(start[pos], -1);
	if (tl == tr) {
		start[pos] = x;
		// cerr << "upd " << start[pos] << " 1\n";
		t[v].upd(start[pos], 1);
		return;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		upd(2 * v, tl, tm, pos, x);
	}
	else {
		upd(2 * v + 1, tm + 1, tr, pos, x);
	}
	// cerr << "upd " << start[pos] << " 1\n";
	t[v].upd(start[pos], 1);
}

pair<int, int> operator +(pair<int, int> a, pair<int, int> b) {
	return {a.first + b.first, a.second + b.second};
}

pair<int, int> get(int v, int tl, int tr, int l, int r, int a, int b) {
	if (tl > r || l > tr) {
		return {0, 0};
	}
	if (l <= tl && tr <= r) {
		// cerr << tl << ' ' << tr << ' ' << a << ' ' << b << '\n';
		t[v].print();
		int cnt = t[v].get((a + b) / 2);
		int cnt2 = 0;
		if ((b - a) % 2 == 0) {
			cnt2 = t[v].get((a + b) / 2 + 1) - cnt;
		}
		// cerr << cnt << ' ' << cnt2 << '\n';
		return {cnt, cnt2};
	}
	int tm = (tl + tr) >> 1;
	return get(2 * v, tl, tm, l, r, a, b) + get(2 * v + 1, tm + 1, tr, l, r, a, b);
}

inline void init() {

}

struct Q {
	int a, b, c, d, t;
	Q(int f, int s, int q) {
		a = f, b = s, t = q;
	}
	Q(int f, int s, int x, int y, int q) {
		a = f, b = s, c = x, d = y, t = q;
	}
};

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> start[i];
		a[i].push_back(start[i]);
	}
	int m;
	cin >> m;
	vector<Q> q;
	for (int i = 0; i < m; i++) {
		char c;
		cin >> c;
		if (c == 'C') {
			int x, z;
			cin >> x >> z;
			x--;
			a[x].push_back(z);
			q.emplace_back(x, z, 0);
		}
		else {
			int x, y, d1, d2;
			cin >> x >> y >> d1 >> d2;
			x--, d1--;
			q.emplace_back(x, d1, y, d2, 1);
		}
	}
	for (int i = 0; i < n; i++) {
		sort(a[i].begin(), a[i].end());
	}
	build(1, 0, n - 1);
	// cerr << '\n';
	for (auto it : q) {
		if (it.t == 0) {
			upd(1, 0, n - 1, it.a, it.b);
		}
		else {
			pair<int, int> got = get(1, 0, n - 1, it.a, it.b, it.c, it.d);
			int s1 = got.first;
			// cerr << '\n';
			// cerr << it.b << ' ' << it.a << '\n';
			int s2 = it.b - it.a + 1 - s1 - got.second;
			// cerr << s1 << ' ' << s2 << ' ' << got.second << '\n';
			if (s1 > s2) {
				cout << "1\n";
			}
			if (s2 > s1) {
				cout << "2\n";
			}
			if (s1 == s2) {
				cout << "0\n";
			}
		}
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
	while (cin >> n)
		solve();
	return 0;
}