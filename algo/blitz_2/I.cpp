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
	const int MAXN = 3e5;
#endif
#define int ll
int n, m, k;
const int K = 300;
int sum[MAXN];
int add[K][K];
int mod = 1e9 + 7;
int fact[MAXN];
int rev[MAXN];

int bp(int a, int N) {
	if (N == 0) {
		return 1;
	}
	if (N & 1) {
		return (a * bp(a, N - 1)) % mod;
	}
	return bp((a * a) % mod, N >> 1);
}

int C(int n, int k) {
	if (k < 0) {
		return 0;
	}
	return (fact[n] * ((rev[n - k] * rev[k]) % mod)) % mod;
}

inline void init() {
	memset(sum, 0, sizeof(sum));
	fact[0] = 1;
	rev[0] = bp(1, mod - 2);
	for (int i = 1; i < MAXN; i++) {
		fact[i] = (i * fact[i - 1]) % mod;
		rev[i] = bp(fact[i], mod - 2);
	}
}

inline void solve() {
	init();
	vector<pair<int, int>> q;
	for (int i = 0; i < m; i++) {
		int a, d;
		cin >> a >> d;
		if (d < K) {
			q.emplace_back(a, d);
		}
		else {
			for (int j = a; j <= n; j += d) {
				sum[j]++;
			}
		}
	}
	sort(q.begin(), q.end());
	int pnt = 0;
	int top = 0;
	for (int i = 1; i <= n; i++) {
		while (pnt < q.size() && q[pnt].first == i) {
			add[q[pnt].second][i % q[pnt].second]++;
			pnt++;
		}
		for (int j = 1; j < K; j++) {
			sum[i] += add[j][i % j];
		}
	}
	for (int i = 1; i <= n; i++) {
		top += C(m, k) - C(m - sum[i], k - sum[i]);
		if (top < 0) {
			top %= mod;
			top += mod;
		}
		top %= mod;
	}
	top *= bp(C(m, k), mod - 2);
	top %= mod;
	cout << top << '\n';
	// for (int i = 1; i <= n; i++) {
	// 	cout << sum[i] << ' ';
	// }
	// cout  << '\n';
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
	while (cin >> n >> m >> k)
		solve();
	return 0;
}