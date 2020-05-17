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
	const int MAXM = 10;
#else
	const int MAXN = 1000;
	const int MAXM = 1000;
#endif

int n, m;
vector<int> g[MAXN];
string edge[MAXN];
int dist[MAXN];
int used[MAXN];
vector<int> parents[MAXN];
vector<int> t[MAXN];

inline void init() {

}

vector<int> eul;
string ans[MAXN];

void rev(int v) {
	if (used[v]) {
		return;
	}
	used[v] = 1;
	for (auto to : t[v]) {
		rev(to);
	}
	eul.push_back(v);
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> edge[i];
		dist[i] = 1e9;
	}
	dist[0] = edge[0].size();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	while (1) {
		int ok = -1;
		for (int i = 0; i < n; i++) {
			if (!used[i]) {
				if (ok == -1 || dist[i] < dist[ok]) {
					ok = i;
				}
			}
		}
		if (ok == -1) {
			break;
		}
		used[ok] = 1;
		for (auto to : g[ok]) {
			if (dist[to] > dist[ok] + edge[to].size()) {
				parents[to].clear();
				dist[to] = dist[ok] + edge[to].size();	
			}
			if (dist[to] == dist[ok] + edge[to].size()) {
				parents[to].push_back(ok);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (auto p : parents[i]) {
			t[p].push_back(i);
		}
	}
	memset(used, 0, sizeof(used));
	rev(0);
	memset(used, 0, sizeof(used));
	for (auto v : eul) {
		string s = edge[v];
		sort(t[v].begin(), t[v].end(), [&](int a, int b){
			return ans[a] < ans[b];
		});
		if (t[v].size()) {
			assert(used[t[v][0]]);
			s += ans[t[v][0]];
		}
		used[v] = 1;
		ans[v] = s;
	}
	cout << ans[0] << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}