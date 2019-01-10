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
#define int ll
#ifdef DEBUG
	const int MAXN = 20;
#else
	const int MAXN = 20;
#endif

int n;

string a[MAXN];
map<int, int> dp[1 << MAXN][2];
int symb[MAXN];

string bin(int x) {
	string res = "";
	if (x == 0) {
		res = "0";
	}
	while (x) {
		res.push_back('0' + x % 2);
		x /= 2;
	}
	reverse(res.begin(), res.end());
	return res;
}


inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		for (auto c : a[i]) {
			symb[i] |= (1ll << (c - 'a'));
		}
	}
	dp[0][1][0] = 1;
	vector<map<pair<int, int>, pair<int, int>>> kek(n);
	vector<map<tuple<int, int>, pair<int, int>>> kek1(n);
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int start = 0; start < 2; start++) {
			for (int nxt = 0; nxt < n; nxt++) {
				if (mask & (1 << nxt)) {
					continue;
				}
				for (auto it : dp[mask][start]) {
					int alp = it.first;
					int nm = (alp & symb[nxt]);
					int cur = start;
					if (!kek[nxt].count({nm, start})) {
						vector<pair<int, int>> fw(a[nxt].size());
						for (int i = 0; i < a[nxt].size(); i++) {
							int c = a[nxt][i] - 'a';
							int was = (alp >> c) & 1;
							alp ^= (was << c);
							alp |= ((was ^ cur) << c);
							int r = (alp >> c) & 1;
							cur ^= r;
							if (kek1.count({i, alp & symb[nxt], cur})) {
								
							}
							fw[i] = make_pair(alp, cur);
						}
						kek[nxt][{nm, start}] = {alp & symb[nxt], cur};
						cerr << bin(mask) << ' ' << bin(nm) << ' ' << start << ' ' << a[nxt] << ' ' << bin(mask | (1 << nxt)) << ' ' << bin(alp & symb[nxt]) << ' ' << cur << '\n';
					}
					cur = kek[nxt][{nm, start}].second;
					alp = kek[nxt][{nm, start}].first | (alp ^ (alp & symb[nxt]));
					dp[mask | (1 << nxt)][cur][alp] += it.second;
				}
			}
		}
	}
	int ans = 0;
	for (auto it : dp[(1 << n) - 1][0]) {
		ans += it.second;
	}
	cout << ans << '\n';
}
signed main() {
	#ifdef DEBUG
		freopen("10A.in", "r", stdin);
		freopen("10A.out", "w", stdout);
	#else 
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}