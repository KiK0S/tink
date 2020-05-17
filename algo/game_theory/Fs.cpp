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
#include <complex>
using namespace std;

typedef long long ll;
#define int ll
#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e6 + 100;
#endif

int n;

int _ans[MAXN];
int dp[MAXN];
vector<int> g[MAXN];
int tx[MAXN];

int mex(vector<int> q) {
	sort(q.begin(), q.end());
	q.resize(unique(q.begin(), q.end()) - q.begin());
	for (int i = 0; i < q.size(); i++) {
		if (q[i] != i) {
			return i;
		}
	}
	return q.size();
}

vector<int> dfs(int v) {
	if (g[v].size() == 0) {
		_ans[v] = 0;
		dp[v] = 1;
		tx[v] = 0;
		return {v};
	}
	vector<vector<int>> all;
	int all_xor = 0;
	for (auto to : g[v]) {
		vector<int> cur = dfs(to);
		all.push_back(cur);
		all_xor ^= dp[to];
	}
	tx[v] = all_xor;
	vector<int> q;
	vector<int> ret;
	for (int i = 0; i < g[v].size(); i++) {
		for (auto to : all[i]) {
			q.push_back(all_xor ^ dp[g[v][i]] ^ _ans[to]);
			ret.push_back(to);
		}
	}
	// cerr << v << ' ' << all_xor << '\n';
	// for (auto it : q) {
	// 	cerr << it << ' ';
	// }
	// cerr << '\n';
	ret.push_back(v);
	_ans[v] = mex(q);
	q.push_back(all_xor);
	dp[v] = mex(q);
	return ret;
}

inline void init() {

}

inline void solve() {
	init();
	// assert(n == 7);
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
	}
	dfs(0);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		// cerr << _ans[i] << ' ';
		if (_ans[i] != 0) {
			ans++;
			// cerr << i << ' ';
		}	
	}
	// cerr << '\n';
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("Fs.in", "r", stdin);
		freopen("Fs.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}