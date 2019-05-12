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
	const int MAXN = 2e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, k;

vector<pair<int, int>> g[MAXN];
int dp[MAXN][2];

struct two_set {
	set<pair<int, int>> s1;
	set<pair<int, int>> s2;
	int sum = 0;
	int sz;

	void update() {
		while (s1.size() < sz && s2.size()) {
			auto it = *s2.rbegin();
			s2.erase(it);
			s1.insert(it);
			sum += it.first;
		}
		while (s1.size() && s2.size() && (*s1.begin()) < (*s2.rbegin())) {
			auto it1 = *s1.begin();
			auto it2 = *s2.rbegin();
			sum -= it1.first;
			sum += it2.first;
			s1.erase(it1);
			s1.insert(it2);
			s2.erase(it2);
			s2.insert(it1); 
		}
	}

	void insert(int a, int b) {
		s2.insert(make_pair(a, b));
		update();
	}

	void erase(int a, int b) {
		if (s1.count(make_pair(a, b))) {
			s1.erase(make_pair(a, b));
			sum -= a;
		}
		if (s2.count(make_pair(a, b))) {
			s2.erase(make_pair(a, b));
		}
		update();
	}
};

void dfs(int v, int p = -1) {
	vector<int> dp_to_0;
	vector<int> dp_to_1;
	for (auto it : g[v]) {
		int to = it.first;
		if (to == p) {
			continue;
		}
		dfs(to, v);
		dp_to_0.emplace_back(dp[to][0] + it.second);
		dp_to_1.emplace_back(dp[to][1] + it.second);
	}
	if (dp_to_0.size() == 0) {
		dp[v][0] = 0;
		dp[v][1] = 0;
		return;
	}
	if (k > 1) {
		sort(dp_to_0.rbegin(), dp_to_0.rend());
		sort(dp_to_1.rbegin(), dp_to_1.rend());
		vector<int> pref_sum(dp_to_0.size());
		for (int i = 0; i < pref_sum.size(); i++) {
			pref_sum[i] = (i == 0 ? 0 : pref_sum[i - 1]) + dp_to_0[i];
		}
		dp[v][0] = pref_sum[min(k - 2, (int)pref_sum.size() - 1)];
		dp[v][1] = pref_sum[min(k - 2, (int)pref_sum.size() - 1)];
	}
	two_set X;
	X.sz = k - 1;
	for (auto it : g[v]) {
		int to = it.first;
		if (to == p) {
			continue;
		}
		X.insert(dp[to][0] + it.second, to);
	}
	for (auto it : g[v]) {
		int to = it.first;
		if (to == p) {
			continue;
		}
		X.erase(dp[to][0] + it.second, to);
		dp[v][1] = max(dp[v][1], dp[to][1] + it.second + X.sum);
		X.insert(dp[to][0] + it.second, to);
	}
}

inline void init() {
	memset(dp, 0, sizeof(dp));
}

inline void solve() {
	init();
	for (int i = 1; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}
	dfs(0);
	for (int i = 0;  i < n; i++) {
		cerr << dp[i][0] << ' ' << dp[i][1] << '\n';
	}
	cout << max(dp[0][0], dp[0][1]) << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("N.in", "r", stdin);
		freopen("N.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}