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
	const int MAXN = 2e5;
#endif


int n;
string alp;
string s, t;
char need[26];

bool check() {
	return s == t;
}

inline void init() {
	for (int i = 0; i < 26; i++) {
		need[i] = '0';
	}
}

inline void solve() {
	init();
	string cur = "";
	string res = "";
	for (int i = 0; i < n; i++) {
		if (need[s[i] - 'a'] == '0') {
			need[s[i] - 'a'] = t[i];
			cur.push_back(s[i]);
			res.push_back(t[i]);
		}
		if (need[s[i] - 'a'] != t[i]) {
			cout << "-1\n";
			return;
		}
	}
	for (int i = 0; i < 1e6; i++) {
		if (res == cur) {
			cout << i << '\n';
			return;
		}
		for (int i = 0; i < cur.size(); i++) {
			cur[i] = alp[cur[i] - 'a'];
		}
	}
	cout << "-1\n";
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
	while (cin >> alp >> n >> s >> t)
		solve();
	return 0;
}