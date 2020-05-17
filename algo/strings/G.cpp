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

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 12;
#endif

int n;
string s[MAXN];
string dp[1 << MAXN][MAXN];
string add[MAXN][MAXN];

bool cmp(string a, string b) {
	if (a.size() != b.size()) {
		return a.size() < b.size();
	}
	return a < b;
}

string INF;

inline void init() {
	INF = "";
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < 51; j++) {
			INF.push_back('Z');
		}
	}
	for (int i = 0; i < (1 << MAXN); i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = INF;
		}
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		dp[1 << i][i] = s[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || s[i].size() <= s[j].size()) {
				continue;
			}
			for (int k = 0; k + s[j].size() - 1 < s[i].size(); k++) {
				if (s[i].substr(k, s[j].size()) == s[j]) {
					s[j] = "";
					break;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		dp[1 << i][i] = s[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			string res = s[j];
			for (int k = s[j].size(); k > 0; k--) {
				if (s[i].size() >= k) {
					if (s[i].substr(s[i].size() - k, k) == s[j].substr(0, k)) {
						reverse(res.begin(), res.end());
						for (int l = 0; l < k; l++) {
							res.pop_back();
						}
						reverse(res.begin(), res.end());
						break;
					}
				}
			}
			cerr << s[i] << ' ' << s[j] << ' ' << res << '\n';
			add[i][j] = res;
		}
	}
	for (int mask = 1; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
			if (!(mask & (1 << i))) {
				continue;
			}
			for (int j = 0; j < n; j++) {
				if (!((1 << j) & mask)) {
					int maskto = mask | (1 << j);
					if (cmp(dp[mask][i] + add[i][j], dp[maskto][j])) {
						dp[maskto][j] = dp[mask][i] + add[i][j];
					}
				}
			}
		}
	}
	string ans = INF;
	for (int i = 0; i < n; i++) {
		if (cmp(dp[(1 << n) - 1][i], ans)) {
			ans = dp[(1 << n) - 1][i];
		}
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}