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
	const int MAXN = 200;
#endif

#define int ll

int n;
int MOD = 1e9 + 7;
bitset<10000> a[MAXN];
set<int> divisors;
int val[MAXN];

int bp(int a, int n) {
	if (n == 0) {
		return 1;
	}
	if (n & 1) {
		return (1ll * a * bp(a, n - 1)) % MOD;
	}
	return bp((1ll * a * a) % MOD, n >> 1);
}

void div3(int a) {
	int q = a;
	for (int x = 2; 1ll * x * x <= a; x++) {
		if (q % x == 0) {
			divisors.insert(x);
		}
		while (q % x == 0) {
			q /= x;
		}
	}
	if (q != 1) {
		divisors.insert(q);
	}
}

inline void init() {

}

inline void solve() {
	init();
	divisors.insert(2);
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		div3(val[i]);
	}
	for (int i = 0; i < n; i++) {
		int pnt = 0;
		for (auto it : divisors) {
			int cnt = 0;
			while (val[i] % it == 0) {
				val[i] /= it;
				cnt ^= 1;
			}
			a[i][pnt++] = cnt;
		}
		assert(val[i] == 1);
	}
	assert(divisors.size());
	int ptr = 0;
	int row = 0;
	while (ptr < divisors.size() && row < n) {
		int ok = 0;
		for (int j = row; j < n; j++) {
			if (a[j][ptr]) {
				ok = 1;
				swap(a[j], a[row]);
				break;
			}
		}
		if (!ok) {
			ptr++;
			continue;
		}
		for (int j = row + 1; j < n; j++) {
			if (a[j][ptr]) {
				a[j] ^= a[row];
			}
		}
		row++;
		ptr++;
	}
	int k = 0;
	for (int i = 0; i < n; i++) {
		if (a[i].count() == 0) {
			k++;
		}
	}
	cout << (bp(2, k) + MOD - 1) % MOD << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}