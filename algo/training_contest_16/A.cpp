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

int n, m, k;

int dsu[MAXN];
int sz[MAXN];
int cnt[MAXN];

int get(int x) {
	if (dsu[x] == x) {
		return x;
	}
	return dsu[x] = get(dsu[x]);
}


void unite(int a, int b) {
	a = get(a);
	b = get(b);
	if (a == b) {
		sz[a]++;
		return;
	}
	if (cnt[a] > cnt[b]) {
		swap(a, b);
	}
	dsu[a] = b;
	sz[b] += sz[a] + 1;
	cnt[b] += cnt[a];
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
		sz[i] = 0;
		cnt[i] = 1;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		unite(a, b);
	}
	set<pair<int, int>> s;
	for (int i = 0; i < n; i++) {
		if (dsu[i] == i) {
			s.insert({cnt[i], i});
		}
	}

	cout << max(1, (int)s.size() - k) << ' ';
	for (auto it : s) {
		int a = cnt[it.second] * (cnt[it.second] - 1) / 2;
		int b = sz[it.second];
		k -= a - b;
	}
	while (k > 0) {
		if (s.size() == 1) {
			break;
		}
		pair<int, int> kek_a = *s.rbegin();
		s.erase(kek_a);
		pair<int, int> kek_b = *s.rbegin();
		s.erase(kek_b);
		int c = kek_b.first * kek_a.first;
		k -= c;
		s.insert({kek_b.first + kek_a.first, kek_b.second});
	}
	cout << s.size() << '\n';
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
	while (cin >> n >> m >> k)
		solve();
	return 0;
}