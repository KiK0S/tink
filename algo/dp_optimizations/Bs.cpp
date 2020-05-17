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
	const int MAXN = 1e5;
#endif

#define int ll

int n, m;
int coord[MAXN];
int cost[MAXN];


inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> coord[i] >> cost[i];
	}
	for (int i = 0; i < m; i++) {
		int x, bad;
		cin >> x >> bad;
		vector<int> bads(bad);
		for (int j = 0; j < bad; j++) {
			int _x;
			cin >> _x;
			bads[j] = _x;
		}
		bads.push_back(n + 1);
		sort(bads.begin(), bads.end());
		int pnt = 0;
		int ans = 1e18;
		for (int j = 0; j < n; j++) {
			if (j == bads[pnt]) {
				pnt++;
				continue;
			}
			ans = min(ans, (coord[j] - x) * (coord[j] - x) + cost[j]);
		}
		cout << ans << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("Bs.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}