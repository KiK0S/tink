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
	const int MAXN = 16;
#endif

int n, m;
char g[MAXN][MAXN];
int ans = 0;
string res;
inline void init() {

}

inline void solve() {
	init();
	int start = 0;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			cin >> g[i][j];
			if (g[i][j] == 'M') {
				start = j;
			}
		}
	}
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int submask = mask; submask >= 0; submask = (submask - 1) & mask) {
			int y = start;
			int cnt = 0;
			bool ok = 1;
			string cur = "";
			int used = 0;
			vector<int> open;
			string all = "";
			for (int i = 0; i < n; i++) {
				all.push_back(g[i][y]);
				if (g[i][y] == '*') {
					break;
				}
				if (g[i][y] == '(') {
					open.push_back(i);
				}
				if (g[i][y] == ')' && open.size()) {
					used |= (1 << open.back());
					used |= (1 << i);
					open.pop_back();
					cnt += 2;
				}
				if (submask & (1 << i)) {
					y--;
				}
				else if (mask & (1 << i)) {
					y++;
				}
				if (y < 0 || y >= m) {
					break;
				}
			}
			if (ok) {
				for (int i = 0; i < all.size(); i++) {
					if (all[i] == '*') {
						break;
					}
					if (used & (1 << i)) {
						cur.push_back(all[i]);
					}
				}
				if (ans < cnt) {
					ans = cnt;
					res = cur;
				}
				if (ans == cnt && cur < res) {
					ans = cnt;
					res = cur;
				}
			}
			if (submask == 0) {
				break;
			}
		}
	}
	cout << ans << '\n' << res << '\n';
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