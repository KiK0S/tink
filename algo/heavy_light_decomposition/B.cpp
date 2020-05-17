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
	const int MAXN = 2e7;
	const int BLOCK = 12;
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
int lg_precalc[1 << MAXLOG];
pair<int, int> sparse[MAXLOG + 1][1 << MAXLOG];
pair<int, int> little[1 << (BLOCK - 1)][BLOCK][BLOCK];
int block_mask[MAXN / BLOCK + 1];
pair<int, int> best_in_block[1 << MAXLOG];

inline void init() {
	for (int i = 1; i < MAXN + BLOCK + 1; i++) {
		a[i] = INT32_MIN + 1;
	}
	for (int i = 0; i < (1 << MAXLOG); i++) {
		best_in_block[i] = make_pair(INT32_MIN, 0);
	}
	for (int i = 1; i < n; i++) {
		b = (b * c + d) % TWOPOW;
		a[i] = a[i - 1] + 1 - 2 * ((b % 239179) % 2);
	}
	lg_precalc[0] = MAXLOG - 1;
	for (int i = 1; i < (1 << (MAXLOG)); i++) {
		for (int j = MAXLOG - 1; j >= 0; j--) {
			if (i & (1 << j)) {
				lg_precalc[i] = MAXLOG - 1 - j;
				// cerr << i << ' ' << lg_precalc[i] << '\n';
				break;
			}
		}
	}
}

int f(int a) {
	return a ? 1 : -1;
}

ostream & operator <<(ostream &out, pair<int, int> p) {
	out << p.first << ' ' << p.second;
	return out;
} 

pair<int, int> g(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first) {
		return max(a, b);
	}
	return make_pair(a.first, a.second + b.second);
}

inline void build(int level, int tl, int tr) {
	// cerr << tl << ' ' << tr << "   " << level << '\n';
	if (tl == tr) {
		sparse[level][tl] = best_in_block[tl];
		// cerr << tl << ' ' << sparse[level][tl] << '\n';
		return;
	}
	if (tl > tr) {
		return;
	}
	int tm = (tl + tr) >> 1;
	pair<int, int> cur = make_pair(INT32_MIN, 0);
	for (int i = tm; i >= tl; i--) {
		cur = g(cur, best_in_block[i]);
		sparse[level][i] = cur;
		// cerr << i << ' ' << cur << '\t';
	}
	cur = make_pair(INT32_MIN, 0);
	for (int i = tm + 1; i <= tr; i++) {
		cur = g(cur, best_in_block[i]);
		sparse[level][i] = cur;
		// cerr << i << ' ' << cur << '\t';
	}
	// cerr << '\n';
	build(level + 1, tl, tm);
	build(level + 1, tm + 1, tr);
}

pair<int, int> sp(int l, int r) {
	if (l > r) {
		return make_pair(INT32_MIN, 0);
	}
	if (l == r) {
		return best_in_block[l];
	}
	int lg = lg_precalc[r ^ l];
	return g(sparse[lg][l], sparse[lg][r]);
}

pair<int, int> get(int l, int r) {
	int block_l = l / BLOCK;
	int block_r = r / BLOCK;
	if (block_r == block_l) {
		return make_pair(a[block_l * BLOCK] + little[block_mask[block_l]][l % BLOCK][r % BLOCK].first, little[block_mask[block_l]][l % BLOCK][r % BLOCK].second);
	}
	return g(make_pair(a[block_l * BLOCK] + little[block_mask[block_l]][l % BLOCK][BLOCK - 1].first, little[block_mask[block_l]][l % BLOCK][BLOCK - 1].second), g(make_pair(a[block_r * BLOCK] + little[block_mask[block_r]][0][r % BLOCK].first, little[block_mask[block_r]][0][r % BLOCK].second), sp(block_l + 1, block_r - 1)));
}

inline void solve() {
	init();
	for (int mask = 0; mask < (1 << (BLOCK - 1)); mask++) {
		int start_balance = 0;
		for (int l = 0; l < BLOCK; l++) {
			int balance = start_balance;
			pair<int, int> max_balance = make_pair(start_balance, 1);
			for (int r = l; r < BLOCK; r++) {
				little[mask][l][r] = max_balance;
				balance += f((mask >> r) & 1);
				max_balance = g(max_balance, make_pair(balance, 1));
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
		best_in_block[i / BLOCK] = g(best_in_block[i / BLOCK], make_pair(a[i] + little[block_mask[i / BLOCK]][0][BLOCK - 1].first, little[block_mask[i / BLOCK]][0][BLOCK - 1].second));
		// cerr << best_in_block[i / BLOCK] << '\t';
	}
	// cerr << '\n';
	build(0, 0, (1 << MAXLOG) - 1);
	ll anssum = 0;
	ll last = 0;
	for (int i = 0; i < n; i++) {
		int l = (((x + last) % n) + n) % n;
		int r = (l + i) % n;
		if (l > r) {
			swap(l, r);
		}
		last = get(l, r).second;
		anssum += last;
		x = (x * 1103515245ll + 12345) % TWOPOW;
	}
	cout << anssum << '\n';
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
	while (cin >> n >> a[0] >> b >> c >> d >> x)
		solve();
	return 0;
}