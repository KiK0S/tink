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

const int MAXN = 5002;

int n;

int dp[MAXN][MAXN];

void init() {
	memset(dp, -1, sizeof(dp));
}

vector<double> sr;

int get(int l, int r, int p = 0) {
	if (l + 1 >= r) {
		return 0;
	}
	if (!p && dp[l][r] != -1) {
		return dp[l][r];
	}
	int best = 1e9;
	int opt = l;
	for (int i = l + 1; i <= r - 1; i++) {
		best = min(best, i + max(get(l, i), get(i, r)));
		if (best == i + max(get(l, i), get(i, r))) {
			opt = i;
		}
	}
	if (p) {
		sr.push_back(1.0 * opt / (l + r));
		get(l, opt, 1);
		get(opt, r, 1);
	}
	return dp[l][r] = best;
}

inline void solve() {
	init();
	get(1, 3000, 1);
	double s = 0;
	for (auto x : sr) {
		s += x;
	}
	cerr << s / sr.size() << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("D_dp.in", "r", stdin);
		freopen("D_dp.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}