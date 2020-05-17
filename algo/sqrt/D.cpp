// #pragma GCC optimise("Ofast")
// #pragma GCC optimise("-O2")
// #pragma GCC target("sse,sse2,ssse3,sse4")
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

const int MAXN = 1e5 + 3;
const int MAXK = 500;
const int K = 1000;

int n, m;

vector<int> g[MAXN];
int bigid[MAXN];
int pos[MAXN];
bitset<MAXN> big[MAXK];
int cnt[MAXK][MAXN];
int color[MAXN];
int ans = 0;
int badcnt = 0;

void upd(int v, int c) {
	if (bigid[v] == -1) {
		for (auto to : g[v]) {
			if (bigid[to] != -1) {
				continue;
			}
			if (color[to] == color[v]) {
				ans++;
			}
			if (color[to] == c) {
				ans--;
			}
		}
		for (int i = 0; i < badcnt; i++) {
			if (big[i][v] == 1){
				cnt[i][color[v]]--;
				cnt[i][c]++;
			}
		}
	}
	else {
		ans += cnt[bigid[v]][color[v]];
		ans -= cnt[bigid[v]][c];
	}
	for (int i = 0; i < badcnt; i++) {
		if (big[i][v] == 1 && color[pos[i]] == color[v]) {
			ans++;
		}
		if (big[i][v] == 1 && color[pos[i]] == c) {
			ans--;
		}
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
	memset(bigid, -1, sizeof(bigid));
	badcnt = 0;
	for (int i = 0; i < n; i++) {
		if (g[i].size() >= K) {
			bigid[i] = badcnt++;
			pos[bigid[i]] = i;
			for (auto to : g[i]) {
				big[bigid[i]][to] = 1;
				if (g[to].size() < K) {
					cnt[bigid[i]][color[to]]++;
				}
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