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
	const int MAXN = 80;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, k;


int val[MAXN];
set<int> cur;
int ans = 0;

inline void init() {
	ans = 0;
	cur.clear();
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	for (int i = 0; i < n; i++) {
		if (!cur.count(val[i])) {
			ans++;
			if (cur.size() == k) {
				int mx = -INF;
				int res = -1;
				for (auto it : cur) {
					int pos = INF;
					for (int j = n - 1; j > i; j--) {
						if (val[j] == it) {
							pos = j;
						}
					}
					if (pos > mx) {
						mx = pos;
						res = it;
					}
				}
				if (res != -1) {
					cur.erase(res);
				}	
			}
			cur.insert(val[i]);
		}
	}
	cout << ans << '\n';
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
	while (cin >> n >> k)
		solve();
	return 0;
}