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
	const int MAXN = 10000;
#else
	const int MAXN = 25600;
#endif

int a, b;
bitset<MAXN> dp[MAXN];
bitset<MAXN> used[MAXN];
set<pair<int, int>> hahaha;
set<pair<int, int>> vis;

inline void init() {
}

inline bool get(int A, int B) {
	if (A <= 0 || B <= 0) {
		return 1;
	}
	if (A > B) {
		swap(A, B);
	}
	if (A == 1) {
		return 1 ^ (B % 2);
	}
	int g = __gcd(A, B);
	if (g != 1) {
		return get(A / g, B / g);
	}
	if (A == 2) {
		return 1;
	}
	if (B >= MAXN) {
		if (hahaha.count({A, B})) {
			return 0;
		}
		if (vis.count({A, B})) {
			return 1;
		}
		if (rand() % 2) {
			swap(A, B);
		}
		if ((!get(A - 1, B)) || (!get(A, B - 1))) {
			vis.insert({A, B});
			return 1;
		}
		hahaha.insert({min(A, B), max(A, B)});
		return 0;
	}
	if (used[A][B]) {
		return dp[A][B];
	}
	used[A][B] = 1;
	if (A == 1 && B == 1) {
		return dp[A][B] = 0;
	}
	if (rand() % 2) {
		swap(A, B);
		if ((!get(A - 1, B)) || (!get(A, B - 1))) {
			return dp[B][A] = 1;
		}
		swap(A, B);
	}
	else {
		if ((!get(A - 1, B)) || (!get(A, B - 1))) {
			return dp[A][B] = 1;
		}
	}
	return dp[A][B] = 0;
}

inline void solve() {
	init();
	while (1) {
		// cerr << get(a, b) << '\n';
		if (!get(a - 1, b)) {
			cout << "A" << endl;
			a--;
		}
		else {
			cout << "B" << endl;
			b--;
		}
		int g = __gcd(a, b);
		a /= g;
		b /= g;
		string c;
		cin >> c;
		if (c == "OK") {
			break;
		}
		if (c == "A") {
			a--;
		}
		else {
			b--;
		}
		g = __gcd(a, b);
		a /= g;
		b /= g;
	}
}

signed main() {
	#ifdef DEBUG
		// freopen("D.in", "r", stdin);
		// freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b;
	solve();
	return 0;
}