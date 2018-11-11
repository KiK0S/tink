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

namespace tl {
	#ifdef DEBUG
		const int MAXN = 150; 
	#else
		const int MAXN = 1100;
	#endif

	int n, l;

	ll dp[MAXN][MAXN];
	int pre[MAXN][MAXN];
	int pd[MAXN];

	vector<pair<int, int>> dots;

	inline void init() {
		// assert(n + 100 < MAXN);
		// assert(l < MAXN);
		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < MAXN; j++) {
				dp[i][j] = 1e18;
				pre[i][j] = -1;
			}
		}
	}

	int sz(int x) {
		int cur = 1;
		ll pw = 1;
		while (pw * 10 <= x) {
			pw *= 10;
			cur++;
		}
		return cur;
	}

	void relax(int a, int b, int c, int d, int e) {
		if (d < 0) {
			return;
		}
		if (c < 0) {
			if (dp[a][b] > e) {
				dp[a][b] = e;
				pre[a][b] = -1;
			}
			return;
		}
		if (dp[a][b] > dp[c][d] + e) {
			dp[a][b] = dp[c][d] + e;
			pre[a][b] = c;
		}
	}

	inline void solve() {
		init();
		for (int i = 0; i < n; i++) {
			int a;
			cin >> a;
			dots.push_back({a, 1});
		}
		for (ll i = 1; i <= 1e10; i *= 10) {
			dots.push_back({i, 0});
			if (i != 1) {
				dots.push_back({i - 1, 0});
			}
		}
		sort(dots.begin(), dots.end());
		for (int i = 0; i < dots.size(); i++) {
			pd[i] = (i == 0 ? 0 : pd[i - 1]) + dots[i].second;
		}
		dp[0][0] = 0;
		n = dots.size();
		for (int i = 0; i < dots.size(); i++) {
			for (int j = 0; j < MAXN; j++) {
				if (dots[i].second == 0) {
					relax(i, j, i - 1, j, 0);
					continue;
				}
				relax(i, j, i - 1, j - sz(dots[i].first) - 1, 0);
				for (int k = 0; k < i; k++) {
					relax(i, j, k - 1, j - sz(dots[i].first) - sz(dots[k].first) - 3, dots[i].first - dots[k].first + 1 - (pd[i] - (k == 0 ? 0ll : pd[k - 1])));
				}
			}
		}
		ll mn = 1e18;
		int len = 0;
		for (int i = 0; i <= l - 1; i++) {
			if (dp[dots.size() - 1][i] < mn) {
				mn = dp[dots.size() - 1][i];
				len = i;
			}
		}
		// cerr << len << ' ' << mn << '\n';
		if (mn > 1e9) {
			exit(1);
		}
		int fin = dots.size() - 1;
		string ans = "";
		ans += "]";
		while (fin >= 0) {
			// cerr << ans << '\n';
			// cerr << fin << ' ' << len << '\n';
			if (pre[fin][len] == fin - 1) {
				if (dots[fin].second == 0) {
					fin--;
					continue;
				}
				int add = ans.size();
				ans = to_string(dots[fin].first) + "," + ans;
				fin = pre[fin][len];
				add -= ans.size();
				len += add;
			}
			else {
				int add = ans.size();
				ans = to_string(dots[pre[fin][len] + 1].first) + ".." + to_string(dots[fin].first) + "," + ans;
				fin = pre[fin][len];
				add -= ans.size();
				len += add;
			}
		}
		ans = "[" + ans;
		ans[ans.size() - 2] = ']';
		ans.pop_back();
		cout << ans << '\n';
	}

}


namespace wa{

	#ifdef DEBUG
		const int MAXN = 150; 
	#else
		const int MAXN = 3500;
	#endif

	int n, l;
	int dp[MAXN][MAXN];
	int pre[MAXN][MAXN];
	int getid[MAXN][MAXN];
	int bestans[MAXN][MAXN];
	short id[MAXN][MAXN];

	int pd[MAXN];

	vector<pair<int, char>> dots;

	inline void init() {
		dots.clear();
		// assert(n + 100 < MAXN);
		// assert(l < MAXN);
		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < MAXN; j++) {
				dp[i][j] = 1e9;
				pre[i][j] = -1;
				getid[i][j] = -1;
			}
			for (int j = 0; j < 10; j++) {
				bestans[i][j].clear();
				id[i][j].clear();
			}
		}
	}

	int sz(int x) {
		int cur = 1;
		ll pw = 1;
		while (pw * 10 <= x) {
			pw *= 10;
			cur++;
		}
		return cur;
	}

	// int get(int a, int b, int c) {
	// 	c--;
	// 	if (bestans[b][c].empty()) {
	// 		return -1;
	// 	}
	// 	auto it = lower_bound(bestans[b][c].begin(), bestans[b][c].end(), make_pair((short)a, (int)-1e9));
	// 	it--;
	// 	if (it - bestans[b][c].begin() >= id[b][c].size()) {
	// 		return -1;
	// 	}
	// 	return id[b][c][it - bestans[b][c].begin()];
	// }

	void relax(int a, int b, int c, int d, int e) {
		if (d < 0) {
			return;
		}
		if (c < 0) {
			if (dp[a][b] > e) {
				dp[a][b] = e;
				pre[a][b] = -1;
			}
			return;
		}
		if (dp[a][b] > dp[c][d] + e) {
			dp[a][b] = dp[c][d] + e;
			pre[a][b] = c;
		}
	}

	inline void solve() {
		init();
		for (int i = 0; i < n; i++) {
			int a;
			cin >> a;
			dots.push_back({a, 1});
		}
		for (ll i = 10; i < 1e10; i *= 10) {
			dots.push_back({i - 1, 0});
		}
		sort(dots.begin(), dots.end());
		// for (auto it : dots) {
		// 	cerr << it.first << ' ' << it.second << '\n';
		// }
		// cerr << '\n';
		for (int i = 0; i < dots.size(); i++) {
			pd[i] = (i == 0 ? 0 : pd[i - 1]) + dots[i].second;
		}
		dp[0][0] = 0;
		n = dots.size();
		for (int j = 0; j <= l; j++) {
			for (int i = 0; i < dots.size(); i++) {
				if (dots[i].second == 0) {
					relax(i, j, i - 1, j, 0);
				}
				else {
					// relax(i, j, i - 1, j - sz(dots[i].first) - 1, 0);
					int _s = sz(dots[i].first);
					for (int lg = 1; lg <= _s; lg++) {
						int nj = j - _s - lg - 3;
						if (nj < 0) {
							continue;
						}
						int L = -1;
						if (_s == lg) {
							if (getid[i][nj] > 0) {
								L = id[nj][lg - 1][getid[i][nj] - 1];
							}
						}
						else {
							if (id[nj][lg - 1].size()) {
								L = id[nj][lg - 1].back();
							}
						}
						// int L = id[getid[nj][lg](i, nj, lg);
						if (L < 0) {
							continue;
						}
						// cerr << i << ' ' << j << ' ' << nj << ' ' << lg << ' ' << dots[i].first << ' ' << L << ' ' << dots[L].first << '\n'; 
						// assert(sz(dots[L].first) == lg);
						relax(i, j, L - 1, nj, dots[i].first - dots[L].first + 1 - (pd[i] - (L == 0 ? 0ll : pd[L - 1])));
					}
					// if (i < 100) {
					// 	for (int k = 0; k < i; k++) {
					// 		relax(i, j, k - 1, j - sz(dots[i].first) - sz(dots[k].first) - 3, dots[i].first - dots[k].first + 1 - (pd[i] - (k == 0 ? 0ll : pd[k - 1])));
					// 	}
					// }
				}
				// cerr << "a\n";
				// if ((i == 0 ? 0ll : dp[i - 1][j]) < 1e9) {
					// cerr << "b\n";
					int nw = (i == 0 ? 0ll : dp[i - 1][j]) - dots[i].first + (i == 0 ? 0ll : pd[i - 1]);
					int idx = i;
					// for (int k = (int)bestans[j][sz(dots[i].first)].size() - 1; k >= 0; k--) {
					// 	if (nw >= -bestans[j][sz(dots[i].first)][k]) {
					// 		nw = -bestans[j][sz(dots[i].first)][k];
					// 		idx = id[j][sz(dots[i].first)][k];
					// 	}
					// }
					int ind = sz(dots[i].first) - 1;
					if (bestans[j][ind].size() && -1 * bestans[j][ind].back() <= nw) {
						nw = -1 * bestans[j][sz(dots[i].first) - 1].back();
						idx = id[j][ind].back();
					}
					bestans[j][ind].push_back(-nw);
					// assert(sz(dots[idx].first) == sz(dots[i].first));
					getid[i][j] = id[j][ind].size();
					id[j][ind].push_back(idx);
				// }
			}
		}
		int mn = 1e9;
		int len = 0;
		for (int i = 0; i <= l - 1; i++) {
			if (dp[dots.size() - 1][i] < mn) {
				mn = dp[dots.size() - 1][i];
				len = i;
			}
		}
		// cerr << len << ' ' << mn << '\n';
		if (mn == 1e9) {
			exit(1);
		}
		int fin = dots.size() - 1;
		string ans = "";
		ans += "]";
		while (fin >= 0) {
			// cerr << ans << '\n';
			// cerr << fin << ' ' << len << ' ' << pre[fin][len] << '\n';
			if (pre[fin][len] == fin - 1) {
				if (dots[fin].second == 0) {
					fin--;
					continue;
				}
				int add = ans.size();
				ans = to_string(dots[fin].first) + "," + ans;
				fin = pre[fin][len];
				add -= ans.size();
				len += add;
			}
			else {
				int add = ans.size();
				ans = to_string(dots[pre[fin][len] + 1].first) + ".." + to_string(dots[fin].first) + "," + ans;
				fin = pre[fin][len];
				add -= ans.size();
				len += add;
			}
		}
		ans = "[" + ans;
		assert(ans.size() >= 2);
		ans[ans.size() - 2] = ']';
		ans.pop_back();
		cout << ans << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, l;
	cin >> l >> n;
	if (n < 1000 && l < 1000) {
		tl::n = n;
		tl::l = l;
		tl::solve();
	}
	else {
		wa::n = n;
		wa::l = l;
		wa::solve();
	}
	return 0;
}