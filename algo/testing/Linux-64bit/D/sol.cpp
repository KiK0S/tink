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
	const int MAXN = 30;
#else
	const int MAXN = 3e5;
#endif

const int MAXLOG = 20;

int n;

int val[MAXN];
vector<int> q[MAXN];
int _or[MAXN][MAXLOG];
int t[4 * MAXN];
vector<int> coord;
int lg[MAXN];

inline void build(int v, int tl, int tr) {
	if (tl == tr) {
		t[v] = val[tl];
		// cerr << val[tl] << '\n';
		return;
	}
	int tm = (tl + tr) >> 1;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	t[v] = max(t[2 * v], t[2 * v + 1]);
	// cerr << "tl/tr of " << v << ' ' << tl << ' ' << tr << ' ' << _or[v] << '\n';
}

int get_id(int x) {
	return lower_bound(coord.begin(), coord.end(), x) - coord.begin();
}

int get_or(int l, int r) {
	int ln = lg[r - l + 1];
	return _or[l][ln] | _or[(r - (1 << ln) + 1)][ln];
}

inline int get(int v, int tl, int tr, int l, int r) {
	if (l > tr || tl > r) {
		return -1e9;
	}
	if (l <= tl && tr <= r) {
		return t[v];
	}
	int tm = (tl + tr) >> 1;
	return max(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
}

inline void init() {
	lg[1] = 0;
	for (int i = 2; i < MAXN; i++) {
		lg[i] = 1 + lg[i / 2];
	}
}

inline int _f(int x, int pos) {
	// cerr << "get " << x << ' ' << pos << ' ';
	if (lower_bound(q[x].begin(), q[x].end(), pos) == q[x].end()) {
		return -1e9;
	}
	else {
		return *lower_bound(q[x].begin(), q[x].end(), pos);
	}
	// cerr << res << '\n';	
	// return res;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		coord.push_back(val[i]);
	}
	val[n] = 2e9;
	coord.push_back(val[n]);
	sort(coord.begin(), coord.end());
	coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
	for (int i = 0; i <= n; i++) {
		q[get_id(val[i])].push_back(i);
		_or[i][0] = val[i];
	}
	for (int i = 1; i < MAXLOG; i++) {
		for (int j = 0; j <= n; j++) {
			if (j + (1 << (i - 1)) > n) {
				continue;
			}
			_or[j][i] = _or[j][i - 1] | _or[j + (1 << (i - 1))][i - 1];
		}
	}
	build(1, 0, n);
	ll ans = 0;
	// cerr << '\n';
	for (int i = 0; i < n - 1; i++) {
		// cerr << "\ncurrent l = " << i << '\n';
		int lst = i + 1;
		while (lst < n) {
			int cur = get_or(i, lst);
			// cerr << "cur or " << i << ' ' << lst << " is " << cur << '\n';
			int pre = lst;
			int l = lst;
			int r = n;
			while (l + 1 < r) {
				int mid = (l + r) >> 1;
				if (get_or(i, mid) > cur) {
					r = mid;
				}
				else {
					l = mid;
				}
			}
			lst = l;
			int need = get_or(i, lst);
			int mx = get(1, 0, n, i, lst);
			// cerr << i << ' ' << pre << ' ' << lst << ' ' << need <<  ' ' << mx << '\n';
			if (mx < need) {
				// cerr << "before " << ans << " after ";
				ans += lst - pre + 1;
				// cerr << ans << '\n';
			}
			else {
				// cerr << "before " << ans << " after ";
				ans += max(0, _f(get_id(mx), i) - pre);
				// cerr << ans << '\n';
			}
			lst++;
		}
		// cout << ans << '\n';
	}
	cout << ans << '\n';
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}