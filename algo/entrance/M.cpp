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
	const int MAXN = 1e5;
#else
	const int MAXN = 3e6;
#endif

int n;

struct node {
	int _left, _right;
	int sum;
	int term;
	node() {
		_left = -1;
		_right = -1;
		sum = 0;
		term = -1;
	}
};

node g[MAXN];
int pnt = 1;

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		g[i] = node();
	}
}


void add(int x) {
	int v = 0;
	for (int i = 30; i >= 0; i--) {
		g[v].sum++;
		if (x & (1 << i)) {
			if (g[v]._left == -1) {
				g[v]._left = pnt++;
			}
			v = g[v]._left;
		}
		else {
			if (g[v]._right == -1) {
				g[v]._right = pnt++;
			}
			v = g[v]._right;
		}
	}
	g[v].sum++;
	g[v].term = x;
}

void del(int x) {
	int v = 0;
	for (int i = 30; i >= 0; i--) {
		g[v].sum--;
		if (x & (1 << i)) {
			v = g[v]._left;
		}
		else {
			v = g[v]._right;
		}
	}
	g[v].sum--;
	assert(v != -1);
}

int get(int x) {
	int v = 0;
	for (int i = 30; i >= 0; i--) {
		if (g[v]._right == -1) {
			v = g[v]._left;
			continue;
		}
		if (g[v]._left == -1) {
			v = g[v]._right;
			continue;
		}
		if (x & (1 << i)) {
			if (g[g[v]._right].sum != 0) {
				v = g[v]._right;
			}
			else {
				v = g[v]._left;
			}
		}
		else {
			if (g[g[v]._left].sum != 0) {
				v = g[v]._left;
			}
			else {
				v = g[v]._right;
			}
		}
	}
	return g[v].term;
}


inline void solve() {
	init();
	add(0);
	for (int i = 0; i < n; i++) {
		char c;
		int x;
		cin >> c >> x;
		if (c == '+') {
			add(x);
		}
		if (c == '-') {
			del(x);
		}
		if (c == '?') {
			cout << (x ^ get(x)) << '\n';
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("M.in", "r", stdin);
		freopen("M.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}