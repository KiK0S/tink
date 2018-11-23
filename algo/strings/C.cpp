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
	const int MAXN = 1e5 + 100;
#endif

int n, m;

int a[MAXN];
int b[MAXN];
int ha[MAXN];
int hb[MAXN];
int rnd[MAXN];
int mod = 4e18 + 7;

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		rnd[i] = ((rand() * 1ll << 15) + ((rand() * 1ll)) << 15) + rand();
		// rnd[i] %= 10;
		// cerr << rnd[i] << ' ';
	}
	// cerr << '\n';
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		ha[i] = (i == 0 ? 0 : ha[i - 1]) + rnd[a[i]];
		ha[i] %= mod;
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> b[i];
		hb[i] = (i == 0 ? 0 : hb[i - 1]) + rnd[b[i]];
		hb[i] %= mod;
	}
	for (int len = min(n, m); len > 0; len--) {
		set<int> A;
		for (int i = len - 1; i < n; i++) {
			int cur = ha[i] - (i - len == -1 ? 0 : ha[i - len]);
			cur %= mod;
			cur += mod;
			cur %= mod;
			// cerr << cur << ' ';
			A.insert(cur);
		}
		// cerr << '\n';
		for (int i = len - 1; i < m; i++) {
			int cur = hb[i] - (i - len == -1 ? 0 : hb[i - len]);
			cur %= mod;
			cur += mod;
			cur %= mod;
			// cerr << cur << ' ';
			if (A.count(cur)) {
				cout << len << '\n';
				return;
			}
		}
		// cerr << '\n';
	}
	cout << "0\n";
}

signed main() {
	srand(time(0));
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}