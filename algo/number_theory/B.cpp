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
	const int MAXC = 10;
#else
	const int MAXN = 1e6 + 10;
	const int MAXC = 1e6 + 10;
#endif
const int MOD = 1e9 + 7;
#define int ll

int n;
int val[MAXN];
int cnt[MAXC];
int calc[MAXN];
int divs[MAXC];
int sets[MAXC];

inline void init() {
	memset(cnt, 0, sizeof(cnt));
	memset(divs, 0, sizeof(divs));
	memset(sets, 0, sizeof(sets));
	memset(calc, 0, sizeof(calc));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		cnt[val[i]]++;
	}
	for (int i = 2; i < MAXC; i++) {
		for (int j = 1; i * j < MAXC; j++) {
			divs[i] += cnt[i * j];
		}
	}
	int add = 1;
	int add_sum = 1;
	calc[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		add *= 2;
		add += add_sum;
		add %= MOD;
		add_sum <<= 1;
		add_sum %= MOD;
		calc[i] = (calc[i - 1] + add) % MOD;
	}
	int ans = 0;
	for (int i = MAXC - 1; i >= 2; i--) {
		sets[i] = calc[divs[i]] + MOD;
		sets[i] %= MOD;
		for (int j = 2; j * i < MAXC; j++) {
			sets[i] -= sets[i * j];
			sets[i] += MOD;
			sets[i] %= MOD;
		}
		ans += sets[i] * i;
		ans %= MOD;
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
	while (cin >> n)
		solve();
	return 0;
}