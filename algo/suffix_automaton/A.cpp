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
	const int MAXN = 20;
#else
	const int MAXN = 6e5;
#endif

int n;
string s;

ll ans = 0;

struct node {
	int p = -1;
	int go[26];
	int link = -1;
	ll ans = 0;
	node() {
		memset(go, -1, sizeof(go));
	} 
};

node t[MAXN];
int pnt = 0;

int add(int a, int ch) {
	int b = pnt++;
	t[b].p = a;
	t[b].link = 0;
	while (a != -1) {
		if (t[a].go[ch] == -1) {
			t[a].go[ch] = b;
			t[b].ans += t[a].ans;
			ans += t[a].ans;
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
		for (int i = 0; i < 26; i++) {
			t[d].go[i] = t[c].go[i];
		}
		t[b].link = d;
		while (a != -1 && t[a].go[ch] == c) {
			t[a].go[ch] = d;
			t[d].ans += t[a].ans;
			t[c].ans -= t[a].ans;
			ans += t[a].ans;
			ans -= t[a].ans;
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
	t[0].ans = 1;
	ans = 0;
}

inline void solve() {
	init();
	int v = 0;
	for (auto c : s) {
		v = add(v, c - 'a');
		cout << ans << '\n';
	}
	for (int i = 0; i < pnt; i++) {
		cerr << "vertex " << i << '\n';
		for (int j = 0; j < 2; j++) {
			cerr << t[i].go[j] << ' ';
		}
		cerr << "\nparent " << t[i].p << '\n';
		cerr << "link " << t[i].link << '\n';
		cerr << "ans " << t[i].ans << '\n';
		cerr << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> s)
		solve();
	return 0;
}