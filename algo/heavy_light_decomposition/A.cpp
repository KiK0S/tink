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
	const int MAXN = 2e7 + 1000;
	const int BLOCK = 14;
	const int MAXLOG = 21;
#else
	const int MAXN = 2e7;
	const int BLOCK = 12;
	const int MAXLOG = 21;
#endif


const int TWOPOW = 1 << 31;
ll n, b, c, d;
int a[MAXN + BLOCK + 1];
ll x;
int lg_precalc[MAXN / BLOCK + 1];
int sparse[MAXLOG][MAXN / BLOCK + 1];
int little[1 << (BLOCK - 1)][BLOCK][BLOCK];
int block_mask[MAXN / BLOCK + 1];

inline void init() {
	for (int i = 1; i < n + BLOCK + 1; i++) {
		a[i] = INT32_MIN;
	}
	for (int i = 1; i < n; i++) {
		b = (b * c + d) % TWOPOW;
		a[i] = a[i - 1] + 1 - 2 * ((b % 239179) % 2);
	}
	lg_precalc[1] = 0;
	for (int i = 2; i <= n / BLOCK; i++) {
		lg_precalc[i] = lg_precalc[i >> 1] + 1;
	}
}

int f(int a) {
	return a ? 1 : -1;
}

int sp(int l, int r) {
	if (l > r) {
		return INT32_MIN;
	}
	int lg = lg_precalc[r - l + 1];
	return max(sparse[lg][l], sparse[lg][r - (1 << lg) + 1]);
}

int get(int l, int r) {
	int block_l = l / BLOCK;
	int block_r = r / BLOCK;
	if (block_r == block_l) {
		return a[block_l * BLOCK] + little[block_mask[block_l]][l % BLOCK][r % BLOCK];
	}
	return max(a[block_l * BLOCK] + little[block_mask[block_l]][l % BLOCK][BLOCK - 1], max(a[block_r * BLOCK] + little[block_mask[block_r]][0][r % BLOCK], sp(block_l + 1, block_r - 1)));
}

inline void solve() {
	init();
	for (int mask = 0; mask < (1 << (BLOCK - 1)); mask++) {
		int start_balance = 0;
		for (int l = 0; l < BLOCK; l++) {
			int balance = start_balance;
			int max_balance = start_balance;
			for (int r = l; r < BLOCK; r++) {
				little[mask][l][r] = max_balance;
				balance += f((mask >> r) & 1);
				max_balance = max(max_balance, balance);
			}
			start_balance += f((mask >> l) & 1);
		}
	}
	for (int i = 0; i < n; i += BLOCK) {
		for (int j = 0; j < BLOCK - 1; j++) {
			if (a[i + j + 1] == a[i + j] + 1) {
				block_mask[i / BLOCK] |= 1 << j;
			}
		}
		sparse[0][i / BLOCK] = a[i] + little[block_mask[i / BLOCK]][0][BLOCK - 1];
	}
	for (int i = 1; i < MAXLOG; i++) {
		for (int j = 0; j + (1 << i) <= n / BLOCK + 1; j++) {
			sparse[i][j] = max(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
		}
	}
	ll anssum = 0;
	ll last = 0;
	for (int i = 0; i < n; i++) {
		int l = (((x + last) % n) + n) % n;
		int r = (l + i) % n;
		if (l > r) {
			swap(l, r);
		}
		last = get(l, r);
		anssum += last;
		x = (x * 1103515245ll + 12345) % TWOPOW;
	}
	cout << anssum << '\n';
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
	while (cin >> n >> a[0] >> b >> c >> d >> x)
		solve();
	return 0;
}