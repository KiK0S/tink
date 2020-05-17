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
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif
#define int ll
const int MOD = 1e9 + 7;


vector<vector<int>> operator *(vector<vector<int>> a, vector<vector<int>> b) {
	int n = a.size();
	int m = b[0].size();
	int k = b.size();
	assert(k == a[0].size());
	vector<vector<int>> c(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int t = 0; t < k; t++) {
				c[i][j] += (1ll * a[i][t] * b[t][j]) % MOD;
				c[i][j] %= MOD;
			}
		}
	}
	return c;
}

vector<vector<int>> bp(vector<vector<int>> a, int n) {
	if (n == 0) {
		vector<vector<int>> E(a.size(), vector<int>(a[0].size()));
		for (int i = 0; i < a.size(); i++) {
			E[i][i] = 1;
		}
		return E;
	}
	if (n & 1) {
		return a * bp(a, n - 1);
	}
	return bp(a * a, n >> 1);
}

inline void init() {

}

inline void solve() {
	init();
	int a, b, c, d, e, n;
	cin >> a >> b >> c >> d >> e >> n;
	if (n <= 2) {
		cout << 1 << '\n';
		return;
	}
	vector<vector<int>> matr = {
		{a, b, c, d, e},
		{1, 0, 0, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 0, 1, 1},
		{0, 0, 0, 0, 1}
	};
	vector<vector<int>> st = {
		{1},
		{1},
		{8},
		{3},
		{1}
	};
	matr = bp(matr, n - 2) * st;
	cout << matr[0][0] << '\n';
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
	solve();
	return 0;
}