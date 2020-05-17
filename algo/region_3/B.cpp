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
	const int MAXN = 1e5;
#endif

int n;
string s;

inline void init() {
	n = s.size();
}

inline void solve() {
	init();
	vector<int> pos;
	for (int i = 0; i <= n - 1 - i; i++) {
		if (s[i] != s[n - 1 - i]) {
			pos.push_back(i);
		}
	}
	if (pos.size() == 0) {
		cout << "YES\n";
		return;
	}
	if (pos.size() == 1) {
		if (n % 2 == 1) {
			if (s[n / 2] == s[pos[0]] || s[n/2] == s[n - 1 - pos[0]]){
				cout << "YES";
				return;
			}
		}

		cout << "NO\n";
		return;
	}
	if (pos.size() == 2) {
		int a = pos[0];
		int b = pos[1];
		if (s[a] == s[n - 1 - b] && s[b] == s[n - 1 - a] || s[a] == s[b] && s[n - 1 - a] == s[n - 1 - b]) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
	else {
		cout << "NO\n";
	}
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
	while (cin >> s)
		solve();
	return 0;
}