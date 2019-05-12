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
	const int MAXN = 3001;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 5001;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
int ans[MAXN];

inline void init() {

}

inline void solve() {
	init();
	memset(ans, 0, sizeof(ans));
	int k = 250;
	int min_input = INF;
	int max_input = 0;
	double med = 0;
	vector<int> v;
	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		v.push_back(a);
		min_input = min(min_input, a);
		max_input = max(max_input, a);
		ans[a]++;
		med += a;
	}
	med /= k;
	int cur = 0;
	// cout << med << '\n';
	// 0.1 * 250 = 25
	for (int i = med * 1.5; i <= 2 * med; i++) {
		if (i >= 0 && i < MAXN) {
			cur += ans[i];
		}
	}
	for (int i = 0; i <= 0.5 * med; i++) {
		if (i >= 0 && i < MAXN) {
			cur += ans[i];
		}
	}
	if (cur < 60) {
		cout << round(med) << '\n';
	}
	else {
		cout << max_input / 2 << '\n';
	}
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
	cin >> n;
	while (n--)
		solve();
	return 0;
}