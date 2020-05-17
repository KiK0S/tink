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
#include <complex>
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 100;
#else
	const int MAXN = 1e6 + 1;
#endif

int n;

struct node {
	int go[26];
	int p = -1;
	int link = -1;
	int pc = -1;
	vector<int> term;
};

// map<int, vector<int>> term;

node t[MAXN];
// vector<node> t;
int sz = 0;

int make(int p = 0, int pc = -1) {
	// assert(t.size() == sz);
	// t.push_back(node());
	for (int i = 0; i < 26; i++) {
		t[sz].go[i] = -1;
	}
	t[sz].p = p;
	t[sz].pc = pc;
	t[sz].link = -1;
	// t[sz].term = -1;
	// cerr << sz << ' ';
	return sz++;
}

int get_link(int v);

void add(string s, int id) {
	int v = 0;
	for (auto c : s) {
		// cerr << c << ' ' << v << ' ' << t.size() << '\n';
		// assert((int)v < (int)t.size());
		int nxt = c - 'a';
		if ((int)t[v].go[nxt] == -1) {
			// cerr << "create ";
			make(v, nxt);
			t[v].go[nxt] = sz - 1;
			// cerr << sz << '\n';
		}
		// cerr << t[v].go[c] << '\n';
		v = t[v].go[nxt];
	}
	t[v].term.push_back(id);
	// return v;
}

int get_go(int v, int c) {
	// cerr << c << '\n';
	// assert(v < t.size());
	if (t[v].go[c] != -1) {
		return t[v].go[c];
	}
	if (v == 0) {
		return t[v].go[c] = 0;
	}
	return t[v].go[c] = get_go(get_link(v), c);
}

int get_link(int v) {
	// assert(v < t.size());
	if (t[v].link != -1) {
		return t[v].link;
	}
	if (v == 0 || t[v].p == 0) {
		return t[v].link = 0;
	}
	return t[v].link = get_go(get_link(t[v].p), t[v].pc);
}

// int get_l(int v) {
// 	if (t[v].l != -1) {
// 		return t[v].l;
// 	}
// 	if (t[v].term.size() != 0 || v == 0) {
// 		return t[v].l = v; 
// 	}
// 	return t[v].l = get_l(get_link(v));
// }

inline void init() {

}

vector<int> ans[MAXN];
int SZ[MAXN];
string T;

inline void solve() {
	init();
	make();
	// cerr << t.size() << '\n';
	int n;
	cin >> n;
	assert(n < MAXN);
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		// cerr << i << '\n';
		add(s, i);
		// assert(!term.count(x));
		SZ[i] = s.size();
	}
	int v = 0;
	int cur = 0;
	for (auto c : T) {
		v = get_go(v, c - 'a');
		int cop = v;
		// cerr << v << '\n';
		while (v != 0) {
			// v = get_l(v);
			for (auto it : t[v].term) {
				ans[it].push_back(cur);
			}
			v = get_link(v);
			// cerr << v << ' ';
		}
		v = cop;
		cur++;
		// cerr << '\n';
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i].size() << ' ';
		for (auto it : ans[i]) {
			cout << it - SZ[i] + 2 << ' ';
		}
		cout << '\n';
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
	cin >> T;
	solve();
	return 0;
}