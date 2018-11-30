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
	const int MAXN = 100;
#else
	const int MAXN = 1e6;
#endif

struct node {
	int p = -1;
	map<int, int> go;
	int link = -1;
	node() {

	} 
};

node t[MAXN];
int pnt = 0;

int add(int a, int ch) {
	int b = pnt++;
	t[b].p = a;
	t[b].link = 0;
	while (a != -1) {
		if (!t[a].go.count(ch)) {
			t[a].go[ch] = b;
			a = t[a].link;
			continue;
		}
		int c = t[a].go[ch];
		if (t[c].p == a) {
			t[b].link = c;
			break;
		}
		int d = pnt++;
		t[d].p = a;
		t[d].link = t[c].link;
		t[c].link = d;
		t[d].go = t[c].go;
		t[b].link = d;
		while (a != -1 && t[a].go.count(ch) && t[a].go[ch] == c) {
			t[a].go[ch] = d;
			a = t[a].link;
		}
		break;
	}
	return t[t[b].p].go[ch];
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		t[i] = node();
	}
	pnt++;
}

char q;
string s;
int v = 0;
int k = 25;

inline void solve() {
	for (auto &it : s) {
		if (it >= 'A' && it <= 'Z') {
			it += 'a' - 'A';
		}
	}
	if (q == '?') {
		int cur = 0;
		string res = "YES\n";
		for (auto x : s) {
			if (!t[cur].go.count(x - 'a')) {
				res = "NO\n";
				break;
			}
			cur = t[cur].go[x - 'a'];
		}
		cout << res;
	}
	else {
		k++;
		for (auto x : s) {
			v = add(v, x - 'a');
		}
		// v = add(v, k);
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
	init();
	while (cin >> q >> s)
		solve();
	return 0;
}