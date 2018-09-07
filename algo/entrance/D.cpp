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

int n;

set<int> uniq;
map<char, int> num;

inline void init() {
	num['a'] = 2;
	num['b'] = 2;
	num['c'] = 2;
	num['d'] = 3;
	num['e'] = 3;
	num['f'] = 3;
	num['g'] = 4;
	num['h'] = 4;
	num['i'] = 4;
	num['j'] = 5;
	num['k'] = 5;
	num['l'] = 5;
	num['m'] = 6;
	num['n'] = 6;
	num['o'] = 6;
	num['p'] = 7;
	num['q'] = 7;
	num['r'] = 7;
	num['s'] = 7;
	num['t'] = 8;
	num['u'] = 8;
	num['v'] = 8;
	num['w'] = 9;
	num['x'] = 9;
	num['y'] = 9;
	num['z'] = 9;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int val = 0;
		for (int j = 0; j < s.size(); j++) {
			val *= 10;
			val += num[s[j]];
		}
		uniq.insert(val);
	}
	cout << uniq.size()  << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}