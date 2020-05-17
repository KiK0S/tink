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
	const int MAXN = 1e5 + 100;
#endif

#define int ll

const int MOD = 1e9 + 7;

int n, m, k;

int val[MAXN];
int pw[MAXN][21];

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		pw[i][0] = 1;
		for (int j = 1; j < 21; j++) {
			pw[i][j] = (pw[i][j - 1] * i) % MOD;
		}
	}
}

inline void solve() {
	init();
	int ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	if (k <= 1) {
		int sum = 0;
		for (int i = 0; i < m; i++) {
			ans += val[i] * (i + 1);
			ans %= MOD;
			sum += val[i];
			sum %= MOD;
		}
		for (int i = 0; i < n - m + 1; i++) {
			if (k == 1) {
				cout << ans << '\n';
			}
			else {
				cout << sum << '\n';
			}
			ans -= val[i];
			sum -= val[i];
			ans -= sum;
			ans += val[i + m] * m;
			sum += val[i + m];
			ans %= MOD;
			sum %= MOD;
			ans += MOD;
			sum += MOD;
			ans %= MOD;
			sum %= MOD;
		}
	}
	else if (k == 2) {
		int dec = 0;
		int ans = 0;
		for (int i = 0; i < n; i++) {
			ans += val[i] * pw[m][2] - dec;
			dec += 2 * val[i] - 1;
			if (i >= m - 1) {
				dec -= 2 * val[i - m + 1] - 1;
				cout << ans << '\n';
			}
			cerr << ans << ' ' << dec << '\t';
		}
	}
	else {
		for (int i = 0; i < n - m + 1; i++) {
			int ans = 0;
			for (int j = i; j < i + m; j++) {
				ans += val[j] * pw[j - i + 1][k];
				ans %= MOD;
			}
			cout << ans << '\n';
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
	cin >> n >> m >> k;
	solve();
	return 0;
}