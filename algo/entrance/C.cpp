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

int n = 3;
string inp[MAXN];

inline void init() {
	for (int i = 0; i < n; i++) {
		cin >> inp[i];
	}
}

bool check(string s) {
	for (int i = 0; i < n; i++) {
		int a = find(s.begin(), s.end(), inp[i][0]) - s.begin();
		int b = find(s.begin(), s.end(), inp[i][2]) - s.begin();
		if (inp[i][1] == '<') {
			if (a > b) {
				return 0;
			}
		}
		if (inp[i][1] == '>') {
			if (a < b) {
				return 0;
			}
		}
	}
	return 1;
}

inline void solve() {
	init();
	string s = "abc";
	do {
		if (check(s)) {
			cout << s << '\n';
			break;
		}
	}
	while (next_permutation(s.begin(), s.end()));
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
		solve();
	return 0;
}