#pragma GCC optimise("Ofast")
#pragma GCC target("sse,sse2,ssse3,sse4")
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

const int MAXN = 1e5 + 1;

int K = 100;

int n, m;

vector<int> g[MAXN];
vector<int> big[MAXN];
int color[MAXN];
unordered_multiset<int> cnt[MAXN];
int ans = 0;

// n / k * q = q * k * 4
// k^2 = (n / logn)
// set<pair<int, int>> edges;
void upd(int v, int c) {
	for (auto to : big[v]) {
		if (color[to] == color[v]) {
			ans++;
		}
		if (color[to] == c) {
			ans--;
		}
	}
	ans += cnt[v].count(color[v]);
	ans -= cnt[v].count(c);
	if (g[v].size() >= K) {
		color[v] = c;
		return;
	}
	for (auto to : g[v]) {
		cnt[to].erase(cnt[to].find(color[v]));
		cnt[to].insert(c);
	}
	color[v] = c;
}


inline void solve() {
	for (int i = 0; i < n; i++) {
		cin >> color[i];
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
		if (color[a] != color[b]) {
			ans++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (auto to : g[i]) {
			if (g[to].size() >= K) {
				big[i].push_back(to);
			}
			else {
				cnt[i].insert(color[to]);
			}	
		}
	}
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		upd(a, b);
		cout << ans << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}