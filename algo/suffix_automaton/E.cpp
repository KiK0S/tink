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
	const int MAXN = 1e7 + 10;
#endif

#define int ll

int n;
int q;
string s;
int timer = 0;

struct node {
	int p = -1;
	int go[3];
	int link = -1;
	ll ans = 0;
	ll precalc = 0;
	int last_used = -1; 
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
		for (int i = 0; i < 3; i++) {
			t[d].go[i] = t[c].go[i];
		}
		t[b].link = d;
		while (a != -1 && t[a].go[ch] == c) {
			t[a].go[ch] = d;
			a = t[a].link;
		}
		break;
	}
	return t[t[b].p].go[ch];
}

ll get_ans(int v) {
	if (v < 0) {
		return 0;
	}
	if (t[v].last_used == timer) { // i now dont precalc it in case of bug
		return t[v].precalc;
	}
	t[v].last_used = timer;
	return t[v].precalc = t[v].ans + get_ans(t[v].link);
}

inline void init() {
	pnt++;
}

inline void solve() {
	init();
	int v = 0;
	ll last = 0;
	unordered_set<string> all; // i check out str on being in set before add/delete
	for (int i = 0; i < q; i++) {
		char c;
		string s;
		cin >> c >> s;
		int del = last % s.size();
		s = s.substr(del, s.size() - del) + s.substr(0, del);	
		if (c == '+') {
			if (all.count(s)) {
				continue;
			}
			all.insert(s);
			for (auto x : s) {
				v = add(v, x - 'a');
			}
			t[v].ans++; // add ans in terminal
			// cerr << v << '\n';
			v = 0;
		}
		if (c == '-') {
			if (!all.count(s)) {
				continue;
			}
			all.erase(s);
			for (auto x : s) {
				v = add(v, x - 'a');
			}
			t[v].ans--; // delete ans in terminal
			// cerr << v << '\n';
			v = 0;
		}
		if (c == '?') {
			ll ans = 0;
			vector<int> l;
			for (auto x : s) {
				v = add(v, x - 'a');
				ans += get_ans(v); // for every prefix vertex get sum on suflinks
			}
			cout << ans << '\n';
			timer++;
			v = 0;
			last = ans;
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> q;
	solve();
	return 0;
}