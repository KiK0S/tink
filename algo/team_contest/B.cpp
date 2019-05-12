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
	const int MAXN = 5e5 + 1;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;
#define int ll
int n, k;


int val[MAXN];
vector<int> q[MAXN];
set<pair<int, int>> cur;

int ans = 0;

inline void init() {
	ans = 0;
	cur.clear();
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		q[val[i]].push_back(i);
	}
	for (int i = 0; i < MAXN; i++) {
		q[i].push_back(INF);
	}
	for (int i = 0; i < MAXN; i++) {
		reverse(q[i].begin(), q[i].end());
	}
	for (int i = 0; i < n; i++) {
		if (!cur.count({q[val[i]].back(), val[i]})) {
			ans++;
			if (cur.size() == k) {
				cur.erase(*cur.rbegin());
			}
		}
		else {
			cur.erase({q[val[i]].back(), val[i]});
		}
		q[val[i]].pop_back();
		cur.insert({q[val[i]].back(), val[i]});
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
	while (cin >> n >> k)
		solve();
	return 0;
}