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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 4e3 + 1;
	const int MAXLOG = 7;
	const int MAXSQRT = 4;
#else
	const int MAXN = 1e6 + 10;
	const int MAXLOG = 29;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;

int val[MAXN];
int lol[MAXN];
int pos[MAXN];
int nlol[MAXN];
int npos[MAXN];

inline void init() {
	for (int i = 0; i < n; i++) {
		pos[i] = i;
	}
}

inline int solve(int log) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (!(val[pos[i]] & (1 << log))) {
			npos[cnt] = pos[i];
			nlol[cnt++] = lol[i];
		}
	}
	for (int i = 0; i < n; i++) {
		if ((val[pos[i]] & (1 << log))) {
			npos[cnt] = pos[i];
			nlol[cnt++] = lol[i] | (1 << log);
		}
	}
	for (int i = 0; i < n; i++) {
		lol[i] = nlol[i];
		pos[i] = npos[i];
	}
	int ans = 0;
	int ptr_1 = 0;
	int ptr_2 = 0;
	int ptr_3 = 0;
	for (int i = 0; i < n; i++) {
		while (ptr_1 >= 0 && lol[i] + lol[ptr_1] >= (1 << log)) {
			ptr_1--;
		}
		while (ptr_2 >= 0 && lol[i] + lol[ptr_2] >= (1 << (log + 1))) {
			ptr_2--;
		}
		while (ptr_3 >= 0 && lol[i] + lol[ptr_3] >= (1 << (log + 1)) + (1 << log)) {
			ptr_3--;
		}
		ans ^= (ptr_2 - ptr_1) & 1;
		ans ^= (i - ptr_3) & 1;
		ptr_1++;
		ptr_2++;
		ptr_3++;
	}
	return ans;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	int ans = 0;
	for (int i = 0; i <= MAXLOG; i++) {
		ans |= solve(i) << i;
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