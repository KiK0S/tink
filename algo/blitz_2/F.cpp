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

int f[MAXN];
int val[MAXN];
int ans[MAXN];
int n;

int get(int id) {
	int res = 0;
	for (int i = id + 1; i > 0; i -= i & -i) {
		res += f[i];
	}
	return res;
}

void upd(int id) {
	for (int i = id + 1; i < MAXN; i += i & -i) {
		f[i]++;
	}
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		val[i] = n - val[i];
	}
	int res = 0;
	{
		memset(f, 0, sizeof(f));
		for (int i = 0; i < n; i++) {
			ans[i] += get(val[i]);
			upd(val[i]);
		}
	}
	{
		memset(f, 0, sizeof(f));
		for (int i = n - 1; i >= 0; i--) {
			res += ans[i] * (n - 1 - i - get(val[i]));
			upd(val[i]);
		}
	}
	cout << res << '\n';
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