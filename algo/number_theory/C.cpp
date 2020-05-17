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
	const int MAXN = 100;
#else
	const int MAXN = 2e6;
#endif

#define int ll

const int MOD = (ll)1e9 + 7;

int n, k;
int pnt;
int fact[MAXN];
int ifact[MAXN];
int lp[MAXN];
int pr[MAXN];
int pre[MAXN];
int deg[MAXN];

int bp(int a, int N) {
	if (N == 0) {
		return 1;
	}
	if (N & 1) {
		return (a * bp(a, N - 1)) % MOD;
	}
	return bp((a * a) % MOD, N >> 1);
}

int binom(int n, int k) {
	return (((fact[n] * ifact[k]) % MOD) * ifact[n - k]) % MOD;
}

void erat() {
	for (int i = 2; i <= n; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr[pnt++] = i;
			deg[i] = 1;
			pre[i] = 1;
		}
		for (int j = 0; j < pnt && i * pr[j] <= n && pr[j] <= i; j++) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i]) {
				pre[i * pr[j]] = pre[i];
				deg[i * pr[j]] = deg[i] + 1;
			}
			else {
				pre[i * pr[j]] = i;
				deg[i * pr[j]] = 1;
			}
		}
	}
}

int calc(int x, int diff = 0, int cnt = 0) {
	if (x == 1) {
		return binom(pnt + k - cnt - diff, pnt - diff);
	}
	int sum = 0;
	for (int i = 0; i <= deg[x]; i++) {
		if (i == 0) {
			sum += calc(pre[x], diff, cnt);
		}
		else {
			sum += calc(pre[x], diff + 1, cnt + i);
		}
		sum %= MOD;
	}
	return sum;
}

inline void init() {
	pnt = 0;
	for (int i = 0; i < MAXN; i++) {
		pre[i] = 0;
		lp[i] = 0;
		fact[i] = 0;
		ifact[i] = 0;
		deg[i] = 0;
		pr[i] = 0;
	}
	fact[0] = 1;
	ifact[0] = bp(1, MOD - 2);
	for (int i = 1; i < MAXN; i++) {
		fact[i] = i * fact[i - 1];
		fact[i] %= MOD;
		ifact[i] = bp(fact[i], MOD - 2);
	}
	erat();
}

inline void solve() {
	init();
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		int add = (i * calc(i, 0, 0));
		sum += add;
		sum %= MOD;
	}
	cout << sum << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}