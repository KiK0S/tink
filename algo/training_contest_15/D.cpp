#include <iostream>
#include <vector>
#include <map>
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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 100;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 6002;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m;
struct my_bitset {
	vector<ull> val;
	my_bitset() {

	}
	my_bitset(int s) {
		val.resize(s / 64 + 1);
	}
};


my_bitset A[MAXN / 2];
my_bitset B[MAXN / 2];

void set(my_bitset &A, int pos, int x) {
	int id = pos / 64;
	int lst = pos & 63;
	if (x) {
		A.val[id] |= (((ull)1) << lst);
	} 
	else {
		if (A.val[id] & ((((ull)1) << lst))) {
			A.val[id] ^= (((ull)1) << lst);	
		}
	}
}

bool check(my_bitset &A, my_bitset &B) {
	for (int i = 0; i < A.val.size(); i++) {
		if (A.val[i] & B.val[i]) {
			return 0;
		}
	}
	return 1;
}

struct query {
	int tp = 0;
	int l, r;
};
int sz;

query a[MAXN / 2];
query b[MAXN / 2];

int dp[MAXN / 2][MAXN / 2];
int can[MAXN / 2][MAXN / 2];

vector<int> coord;

inline void init() {
	for (int i = 0; i < MAXN / 2; i++) {
		for (int j = 0; j < MAXN / 2; j++) {
			dp[i][j] = INF;
		}
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		if (s != "rum") {
			int l, r;
			cin >> l >> r;
			l--, r--;
			if (s == "send") {
				a[i].tp = 1;
			}
			else {
				a[i].tp = 2;
			}
			a[i].l = l;
			a[i].r = r;
			coord.push_back(l);
			coord.push_back(r);
		}
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		if (s != "rum") {
			int l, r;
			cin >> l >> r;
			l--, r--;
			if (s == "send") {
				b[i].tp = 1;
			}
			else {
				b[i].tp = 2;
			}
			b[i].l = l;
			b[i].r = r;
			coord.push_back(l);
			coord.push_back(r);
		}
	}
	sort(coord.begin(), coord.end());
	coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
	for (int i = 0; i <= n; i++) {
		A[i] = my_bitset(coord.size());
	}
	for (int i = 0; i <= m; i++) {
		B[i] = my_bitset(coord.size());
	}
	for (int i = 0; i < n; i++) {
		if (a[i].tp) {
			a[i].l = lower_bound(coord.begin(), coord.end(), a[i].l) - coord.begin();
			a[i].r = lower_bound(coord.begin(), coord.end(), a[i].r) - coord.begin();
		}
	}
	for (int i = 0; i < m; i++) {
		if (b[i].tp) {
			b[i].l = lower_bound(coord.begin(), coord.end(), b[i].l) - coord.begin();
			b[i].r = lower_bound(coord.begin(), coord.end(), b[i].r) - coord.begin();
		}
	}
	for (int i = 1; i <= n; i++) {
		A[i].val = A[i - 1].val;
		if (a[i - 1].tp == 1) {
			for (int j = a[i - 1].l; j <= a[i - 1].r; j++) {
				set(A[i], j, 1);
			}
		}
		if (a[i - 1].tp == 2) {
			for (int j = a[i - 1].l; j <= a[i - 1].r; j++) {
				set(A[i], j, 0);
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		B[i].val = B[i - 1].val;
		if (b[i - 1].tp == 1) {
			for (int j = b[i - 1].l; j <= b[i - 1].r; j++) {
				set(B[i], j, 1);
			}
		}
		if (b[i - 1].tp == 2) {
			for (int j = b[i - 1].l; j <= b[i - 1].r; j++) {
				set(B[i], j, 0);
			}
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (j && (can[i][j - 1] == 0) && b[j - 1].tp != 2) {
				continue;
			}
			if (i && (can[i - 1][j] == 0) && a[i - 1].tp != 2) {
				continue;
			}
			if (i && (can[i - 1][j] == 1) && a[i - 1].tp == 2) {
				can[i][j] = 1;
				continue;
			}
			if (j && (can[i][j - 1] == 1) && b[j - 1].tp == 2) {
				can[i][j] = 1;
				continue;
			}
			if (check(A[i], B[j])) {
				can[i][j] = 1;
			}
		}
	}
	// for (int i = 0; i <= n; i++) {
	// 	for (int j = 0; j <= m; j++) {
	// 		cerr << can[i][j] << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	dp[0][0] = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (!can[i][j]) {
				continue;
			}
			if (i) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j] + (j == m ? 0 : 1));	
			}
			if (j) {
				dp[i][j] = min(dp[i][j], dp[i][j - 1] + (i == n ? 0 : 1));
			}
			if (i && j) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
			}
		}
	}
	cout << dp[n][m];
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
	while (cin >> sz >> n)
		solve();
	return 0;
}