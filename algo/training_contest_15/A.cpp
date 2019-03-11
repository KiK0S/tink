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
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
string a, b;


inline void init() {

}

inline void solve() {
	init();
	int l = 0;
	int r = n - 1;
	while (l < n && a[l] == b[l]) {
		l++;
	}
	while (r >= 0 && a[r] == b[r]) {
		r--;
	}
	if (l == n) {
		cout << "Yes\n1 1\n";
		return;
	}
	reverse(a.begin() + l, a.begin() + r + 1);
	if (a == b) {
		cout << "Yes\n";
		cout << l + 1 << ' ' << r + 1 << '\n';
	}
	else {
		cout << "No\n";
	}
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
	while (cin >> n >> a >> b)
		solve();
	return 0;
}