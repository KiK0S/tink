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
	const int MAXN = 1e5;
#endif

int n;
string s;
int mt[MAXN];
vector<int> g[MAXN];
int used[MAXN];
int nxt[MAXN];

int dfs(int v) {
	if (used[v]) {
		return 0;
	}
	used[v] = 1;
	for (auto to : g[v]) {
		if (mt[to] == -1 || dfs(mt[to])) {
			mt[to] = v;
			nxt[v] = to;
			return 1;
		}
	}
	return 0;
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		string a;
		cin >> a;
		for (int j = 0; j < s.size(); j++) {
			if (count(a.begin(), a.end(), s[j])) {
				g[j].push_back(i);
			}
		}
	}
	memset(mt, -1, sizeof(mt));
	memset(used, 0, sizeof(used));
	memset(nxt, -1, sizeof(nxt));
	int ans = 0;
	for (int i = 0; i < s.size(); i++) {
		if (dfs(i)) {
			memset(used, 0, sizeof(used));
			ans++;
		}
	}
	if (ans == s.size()) {
		cout << "YES\n";
		for (int i = 0; i < n; i++) {
			cout << nxt[i] + 1 << ' ';
		}
		cout << '\n';
	}
	else {
		cout << "NO\n";
	}

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
	while (cin >> n >> s)
		solve();
	return 0;
}