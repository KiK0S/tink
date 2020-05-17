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
	const int MAXN = 2e6;
#endif

const int MOD = 1e9 + 7;

int n, m, k;
int sh[MAXN];
int sv[MAXN];
int h[MAXN];
int v[MAXN];

int bp(int a, int N) {
	if (N == 0) {
		return 1;
	}
	if (N & 1) {
		return (a * bp(a, N - 1)) % MOD;
	} 
	return bp((a * a) % MOD, N / 2);
}

void fit(int &a) {
	a %= MOD;
	a += MOD;
	a %= MOD;
}


int get_number(int x, int y) {
	// if (x < 0 || y < 0) return -100;
	return (x * m + y + 1);
}

int calc_sum(int start, int step, int cnt) {
	fit(start);
	int top = 2 * start + step * (cnt - 1);
	fit(top);
	top *= cnt;
	fit(top);
	return (top * bp(2, MOD - 2)) % MOD; 
}

int cs(int start, int finish) {
	if (finish < start) {
		return 0;
	}
	return calc_sum(start, 1, finish - start + 1);
}

int cs1(int start, int finish) {
	if (finish < start) {
		return 0;
	}
	// cerr << start << ' ' << finish << "\n";
	return calc_sum(start, m, (finish - start) / m + 1);	
}

inline void init() {
	assert(n < MAXN && m < MAXN);
	for (int i = 0; i < MAXN; i++) {
		h[i] = 1;
		v[i] = 1;
	}
}

inline void solve() {
	init();
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < m; j++) {
	// 		cerr << get_number(i, j) << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	for (int i = 0; i < n; i++) {
		sh[i] = calc_sum(get_number(i, 0), 1, m);
		// sh[i] %= MOD;
	}
	for (int i = 0; i < m; i++) {
		sv[i] = calc_sum(get_number(0, i), m, n);
		// sv[i] %= MOD;
	}
	set<int> gx;
	set<int> gy;
	for (int i = 0; i < k; i++) {
		char c;
		int x, y;
		cin >> c >> x >> y;
		x--;
		if (c == 'R') {
			gx.insert(x);
			assert(y == 0 || h[x] == 0 || (h[x] * y) % MOD != 0);
			h[x] *= y;
			fit(h[x]);
		}
		else {
			gy.insert(x);
			assert(y == 0 || v[x] == 0 || (v[x] * y) % MOD != 0);
			v[x] *= y;
			fit(v[x]);
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += sh[i];
		fit(ans);
	}
	// cerr << ans << '\n';
	for (auto x : gx) {
		int last = 0;
		// cerr << "! " << x << '\n';
		for (auto y : gy) {
			// cerr << y << ' ' << '\n';
			int add = cs(get_number(x, last), get_number(x, y - 1)) * (h[x] - 1);
			fit(add);
			ans += add;
			fit(ans);
			ans -= get_number(x, y);
			fit(ans);
			add = get_number(x, y);
			fit(add);
			add *= h[x];
			fit(add);
			add *= v[y];
			fit(add);
			ans += add;
			fit(ans);
			last = y + 1;
			// cerr << "! " << ans << '\n';
		}
		int add1 = cs(get_number(x, last), get_number(x, m - 1)) * (h[x] - 1);
		fit(add1); 
		ans += add1;
		fit(ans);
		// cerr << ans << '\n';
	}
	for (auto y : gy) {
		int last = 0;
		for (auto x : gx) {
			int add = cs1(get_number(last, y), get_number(x - 1, y)) * (v[y] - 1);
			fit(add);
			ans += add;
			fit(ans);
			last = x + 1;
		}
		int add1 = cs1(get_number(last, y), get_number(n - 1, y)) * (v[y] - 1);
		fit(add1);
		ans += add1;
		fit(ans);
	}
	cout << ans << '\n';
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
	while (cin >> n >> m >> k)
		solve();
	return 0;
}