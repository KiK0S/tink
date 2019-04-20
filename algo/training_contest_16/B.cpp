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
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif
#define int ll

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m, k;

int val[MAXN];
int dp[MAXN];
int pref[MAXN];
int pre[MAXN];
pair<int, int> f[MAXN];
int pos[MAXN];

void upd(int v, pair<int, int> x) {
	for (int i = v + 1; i < MAXN; i += i & -i) {
		f[i] = max(f[i], x);
	}
}

pair<int, int> get(int v) {
	pair<int, int> res = {-INF, 0};
	for (int i = v + 1; i > 0; i -= i & -i) {
		res = max(res, f[i]);
	}
	return res;
}

int check(double d, int p = 0) {
	for (int i = 0; i < MAXN; i++) {
		dp[i] = -INF;
		f[i] = {-INF, 0};
		pre[i] = -1;
	}
	vector<pair<double, int>> coords;
	for (int i = 0; i < n; i++) {
		coords.push_back({(i == 0 ? 0ll : pref[i - 1]) - d * i, i});
	}
	sort(coords.begin(), coords.end());
	for (int i = 0; i < n; i++) {
		pos[coords[i].second] = i;
	}
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		if (i >= m) {
			upd(pos[i - m], {dp[i - m], i - m});
		}
		double fnd = pref[i - 1] - d * i;
		int ps = upper_bound(coords.begin(), coords.end(), make_pair(fnd, -1ll)) - coords.begin() - 1;
		pair<int, int> got = get(ps);
		dp[i] = got.first + 1;
		pre[i] = got.second;
	}
	if (p) {
		int f = n;
		vector<int> bck;
		while (f != 0) {
			// cerr << f << '\n';
			bck.push_back(f);
			f = pre[f];
		}
		reverse(bck.begin(), bck.end());
		bck[k - 1] = n;
		int a = 0;
		for (int i = 0; i < k; i++) {
			int b = bck[i] - a;
			a += b;
			cout << b << ' ';
		}
		return 0;
	}
	else {
		// cerr << d << ' ' << dp[n] << '\n';
		return dp[n] >= k;
	}
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		pref[i] = (i == 0 ? 0ll : pref[i - 1]) + val[i];
	}
	double l = 0;
	double r = INF;
	for (int i = 0; i < 50; i++) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	// cerr << l << '\n';
	check(l, 1);
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