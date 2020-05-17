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
#define int ll
const int MAXLOG = 30;
int n, q;

struct node {
	int parent;
	int pchar;
	int link = -1;
	int to[3];
	int ans = 0;
	
	node() {
		memset(to, -1, sizeof(to));
	}

	node(int p, int c) {
		parent = p;
		pchar = c;
		memset(to, -1, sizeof(to));
	}
};

struct Aho{
	vector<node> g;
	vector<string> all;
	int used = 0;
	
	Aho() {
		g.push_back(node());
	}
	
	void add(string s) {
		int v = 0;
		all.push_back(s);
		for (auto c : s) {
			if (g[v].to[c - 'a'] == -1) {
				g[v].to[c - 'a'] = g.size();
				g.emplace_back(v, c - 'a');
			}
			v = g[v].to[c - 'a'];
		}
		g[v].ans++;
	}

	void build() {
		queue<int> q;
		q.push(0);
		while (q.size()) {
			int v = q.front();
			q.pop();
			if (v == 0 || g[v].parent == 0) {
				g[v].link = 0;
			}
			else {
				g[v].link = g[g[g[v].parent].link].to[g[v].pchar];
			}
			if (v != 0) {
				g[v].ans += g[g[v].link].ans;
			}
			for (int c = 0; c < 3; c++) {
				if (g[v].to[c] != -1) {
					q.push(g[v].to[c]);
					continue;
				}
				if (v == 0) {
					g[v].to[c] = 0;
				}
				else {
					g[v].to[c] = g[g[v].link].to[c];
				}
			}
		}
	}

	int get(string s) {
		int ans = 0;
		int v = 0;
		for (auto c : s) {
			v = g[v].to[c - 'a'];
			ans += g[v].ans;
		}
		return ans;
	}
};


struct T {
	Aho all[MAXLOG];
	
	void add(string s) {
		int final = 0;
		for (int i = 0; i < MAXLOG; i++) {
			if (!all[i].used) {
				final = i;
				break;
			}
		}
		for (int i = 0; i < final; i++) {
			all[i].used = 0;
			for (auto it : all[i].all) {
				all[final].add(it);
			}
			all[i].g.clear();
			all[i].all.clear();
			all[i].g.push_back(node());
		}
		all[final].add(s);
		all[final].used = 1;
		all[final].build();
	}

	int get(string s) {
		int ans = 0;
		for (int i = 0; i < MAXLOG; i++) {
			if (all[i].used) {
				ans += all[i].get(s);
			}
		}
		return ans;
	}
};

inline void init() {

}

inline void solve() {
	init();
	T pos, neg;
	int last = 0;
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
			pos.add(s);
		}
		if (c == '-') {
			if (!all.count(s)) {
				continue;
			}
			all.erase(s);
			neg.add(s);
		}
		if (c == '?') {
			int ans = pos.get(s) - neg.get(s);
			last = ans;
			cout << ans << '\n';
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("I.in", "r", stdin);
		freopen("I.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> q)
		solve();
	return 0;
}