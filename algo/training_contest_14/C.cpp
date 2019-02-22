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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 20;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));
const ll INF = 1e18;
const int MOD = 1e9 + 7;

int w, h;
int n, m;

struct segtree {
	ll val = -INF;
};
segtree t[4 * MAXN];

void upd(int v, int tl, int tr, int pos, ll x) {
	if (tl == tr) {
		t[v].val = x;
		return;
	}
	int tm = (tl + tr) >> 1;
	if (pos <= tm) {
		upd(2 * v, tl, tm, pos, x);
	}
	else {
		upd(2 * v + 1, tm + 1, tr, pos, x);
	}
	t[v].val = max(t[2 * v].val, t[2 * v + 1].val);
}

ll get(int v, int tl, int tr, int l, int r) {
	if (l > r || l > tr || tl > r) {
		return -INF;
	}
	if (l <= tl && tr <= r) {
		return t[v].val;
	}
	int tm = (tl + tr) >> 1;
	return max(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
}

vector<int> coord_x;
vector<int> coord_y;
pair<int, int> a[MAXN];
pair<pair<int, int>,  int> b[MAXN]; 

vector<pair<int, int>> scan[MAXN];
int pnt[MAXN];
vector<pair<int, int>> sx[MAXN];

inline void init() {

}

void fix(int pos) {
	ll sum = 0;
	while (pnt[pos] < scan[pos].size() && scan[pos][pnt[pos]].second != -1) {
		sum += scan[pos][pnt[pos]++].second;
	}
	// cerr << "update "  << sum << '\n';
	upd(1, 0, MAXN - 1, pos, sum); 
}

ll get(int l, int r, vector<int> &bp) {
	ll ans = -INF;
	for (auto x : bp) {
		ans = max(ans, get(1, 0, MAXN - 1, l + 1, x - 1));
		l = x;
	}
	ans = max(ans, get(1, 0, MAXN - 1, l + 1, r - 1));
	return ans;
}
 
inline void solve() {
	init();
	// ===================================
	for (int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
		coord_y.push_back(a[i].second);
		coord_x.push_back(a[i].first);
		coord_y.push_back(max(1, a[i].second - 1));
		coord_x.push_back(max(1, a[i].first - 1));
		coord_y.push_back(min(h, a[i].second + 1));
		coord_x.push_back(min(w, a[i].first + 1));
	}
	for (int i = 0; i < m; i++) {
		cin >> b[i].first.first >> b[i].first.second >> b[i].second; 
		coord_y.push_back(b[i].first.second);
		coord_x.push_back(b[i].first.first);
		coord_y.push_back(max(1, b[i].first.second - 1));
		coord_x.push_back(max(1, b[i].first.first - 1));
		coord_y.push_back(min(h, b[i].first.second + 1));
		coord_x.push_back(min(w, b[i].first.first + 1));
	}
	sort(coord_x.begin(), coord_x.end());
	sort(coord_y.begin(), coord_y.end());
	coord_x.resize(unique(coord_x.begin(), coord_x.end()) - coord_x.begin());
	coord_y.resize(unique(coord_y.begin(), coord_y.end()) - coord_y.begin());
	for (int i = 0; i < n; i++) {
		a[i].first = lower_bound(coord_x.begin(), coord_x.end(), a[i].first) - coord_x.begin();
		a[i].second = lower_bound(coord_y.begin(), coord_y.end(), a[i].second) - coord_y.begin();
	}
	for (int i = 0; i < m; i++) {
		b[i].first.first = lower_bound(coord_x.begin(), coord_x.end(), b[i].first.first) - coord_x.begin();
		b[i].first.second = lower_bound(coord_y.begin(), coord_y.end(), b[i].first.second) - coord_y.begin();
	}
	// ===================================
	for (int i = 0; i < n; i++) {
		scan[a[i].second].emplace_back(a[i].first, -1);
	}
	for (int i = 0; i < m; i++) {
		scan[b[i].first.second].emplace_back(b[i].first.first, b[i].second);
	}
	for (int i = 0; i < n; i++) {
		sx[a[i].first].emplace_back(a[i].second, -1);
	}
	for (int i = 0; i < m; i++) {
		sx[b[i].first.first].emplace_back(b[i].first.second, b[i].second);
	}

	for (int i = 0; i < coord_y.size(); i++) {
		sort(scan[i].begin(), scan[i].end());
		pnt[i] = 0;
		fix(i);
	}
	ll ans = 0;
	for (int i = 0; i < coord_x.size(); i++) {	
		sort(sx[i].begin(), sx[i].end());
		int pre = -1;
		ll sum = 0; 
		vector<int> breakpoints;
		for (auto it : sx[i]) {
			if (it.second == -1) {
				pnt[it.first]++;
				fix(it.first);
				// for (auto itt : breakpoints) {
				// 	cerr << itt << ' ';
				// }
				// cerr << '\t';
				// cerr << sum << ' ' << pre << ' ' << get(pre, coord_y.size(), breakpoints) << '\n';
				ans = max(ans, sum + get(pre, it.first, breakpoints));
				pre = it.first;
				sum = 0;
				breakpoints.clear();
			}
			else {
				sum += it.second;
				breakpoints.push_back(it.first);
			}
		}
		// cerr << sum << ' ' << pre << ' ' << get(pre, MAXN, breakpoints) << '\n';
		ans = max(ans, sum + get(pre, coord_y.size(), breakpoints));
	}
	cout << ans << '\n';	
}

signed main( ) {
	#ifdef   DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> w >> h >> n >> m;
	solve();
	return 0;
}