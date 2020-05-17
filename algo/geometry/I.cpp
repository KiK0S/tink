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
	const int MAXN = 5000;
#endif

#define double long double

int n;
ll INF = 2e9;
double EPS = 1;

struct V {
	int x, y;
	int c;
	int id;
	V() {}
	V(int a, int b) {
		x = a, y = b;
	}
	V(int a, int b, int _c, int d) {
		x = a, y = b, c = _c, id = d;
	}
};

struct L {
	int a, b;
	V f, s;
	L() {}
	L(V _f, V _s) {
		f = _f, s = _s;
		b = f.x - s.x;
		a = s.y - f.y;
		if (b < 0) {
			a *= -1;
			b *= -1;
		}
	}
};

V operator + (V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

V operator - (V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

int operator * (V a, V b) {
	return a.x * b.x + a.y * b.y;
}

int operator ^ (V a, V b) {
	return a.x * b.y - a.y * b.x;
}

pair<ll, ll> get_k(L l) {
	if (l.b == 0) {
		return make_pair(-INF, 1);
	}
	return make_pair(-l.a, l.b);
}

int pos[MAXN];
V sorted[MAXN];

struct segtree {
	ll sum = 0;
	ll ans = 0;
	ll pref = 0;
	ll suf = 0;
};

segtree t[4 * MAXN];

void upd(int v) {
	t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
	t[v].pref = max(t[2 * v].pref, t[2 * v].sum + t[2 * v + 1].pref);
	t[v].suf = max(t[2 * v + 1].suf, t[2 * v + 1].sum + t[2 * v].suf);
	t[v].ans = max(t[2 * v].ans, t[2 * v + 1].ans);
	t[v].ans = max(t[v].ans, t[2 * v].suf + t[2 * v + 1].pref);
}

void upd(int v, int tl, int tr, int pos, int x) {
	if (tl == tr) {
		t[v].sum = x;
		t[v].ans = max(0ll, t[v].sum);
		t[v].pref = t[v].ans;
		t[v].suf = t[v].ans;
		return;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		upd(2 * v, tl, tm, pos, x);
	}
	else {
		upd(2 * v + 1, tm + 1, tr, pos, x);
	}
	upd(v);
}

ll get_ans() {
	return t[1].ans;
}

inline void init() {

}

void rev(int a, int b) {
	while (a <= b) {
		swap(sorted[a], sorted[b]);
		swap(pos[sorted[a].id], pos[sorted[b].id]);
		upd(1, 0, n - 1, a, sorted[a].c);
		upd(1, 0, n - 1, b, sorted[b].c);
		a++;
		b--;
	}
}

const bool cmp(L a, L b) {
	pair<ll, ll> A = get_k(a);
	pair<ll, ll> B = get_k(b);
	return A.first * B.second < A.second * B.first;
}

const bool cmpeq(L a, L b) {
	pair<ll, ll> A = get_k(a);
	pair<ll, ll> B = get_k(b);
	return A.first * B.second <= A.second * B.first;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		sorted[i] = V(a, b, c, i);
	}
	vector<L> lines;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			lines.emplace_back(sorted[i], sorted[j]);
		}
	}
	sort(lines.begin(), lines.end(), cmp);
	sort(sorted, sorted + n, [&](V a, V b){
		return make_pair(a.x, -a.y) < make_pair(b.x, -b.y);
	});
	for (int i = 0; i < n; i++) {
		pos[sorted[i].id] = i;
		upd(1, 0, n - 1, i, sorted[i].c);
	}
	int pnt = 0;
	ll ans = max(0ll, get_ans());
	for (auto it : lines) {
		vector<int> swaps;
		set<pair<int, int>> used;
		while (pnt < lines.size() && cmpeq(lines[pnt], it)) {
			int id_a = lines[pnt].f.id;
			int id_b = lines[pnt].s.id;
			swaps.emplace_back(pos[id_a]);
			swaps.emplace_back(pos[id_b]);
			used.insert({min(pos[id_a], pos[id_b]), max(pos[id_a], pos[id_b])});
			pnt++;
		}
		int lst = -1;
		int len = 0;
		sort(swaps.begin(), swaps.end());
		swaps.resize(unique(swaps.begin(), swaps.end()) - swaps.begin());
		for (auto it : swaps) {
			if (lst == -1) {
				lst = it;
				len = 0;
			}
			if (!used.count({lst, it})) {
				rev(lst, lst + len - 1);
				lst = it;
				len = 0;
			}
			len++;
		}
		if (lst != -1) {
			rev(lst, lst + len - 1);
		}
		ans = max(ans, get_ans());
	}
	cout << ans << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}