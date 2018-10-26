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
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 3e5 + 100;
#endif

int n, m;
int dp[MAXN];
vector<int> g[MAXN];
vector<int> gr[MAXN];
int cnt[MAXN];

inline void init() {
	for (int i = 0; i < n; i++) {
		dp[i] = -1;
		g[i].clear();
		gr[i].clear();
		cnt[i] = 0;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		gr[b].push_back(a);
		cnt[a]++;
	}
	queue<int> q;
	for (int i = 0; i < n; i++) {
		if (g[i].size() == 0) {
			dp[i] = 0;
			q.push(i);
		}
	}
	while (q.size()) {
		int v = q.front();
		q.pop();
		if (dp[v] == 0) {
			for (auto to : gr[v]) {
				if (dp[to] == -1) {
					dp[to] = 1;
					q.push(to);	
				}
			}
		}
		else {
			for (auto to : gr[v]) {
				cnt[to]--;
				if (cnt[to] == 0 && dp[to] == -1) {
					dp[to] = 0;
					q.push(to);
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (dp[i] == 0) {
			cout << "SECOND\n";
		}
		if (dp[i] == 1) {
			cout << "FIRST\n";
		}
		if (dp[i] == -1) {
			cout << "DRAW\n";
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}