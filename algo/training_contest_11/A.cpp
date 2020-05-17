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
#define int ll
#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e6;
#endif

int n, k;
int used[MAXN];
int val[MAXN];


inline void init() {
	k %= n;
	memset(used, 0, sizeof(used));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int cur = i;
		ll c = 0;
		while (!used[cur]) {
			c += val[cur];
			used[cur] = 1;
			cur += k;
			if (cur >= n) {
				cur -= n;
			}
		}
		ans = max(ans, c);
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}