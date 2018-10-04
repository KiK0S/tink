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
	const int MAXN = 11;
#else
	const int MAXN = 4e5;
#endif

int n;

vector<int> g[MAXN];
int ch[MAXN];

inline void init() {

}

struct node {
	node *go[26];
	int sz;
	node() {
		sz = 1;
		for (int i = 0; i < 26; i++) {
			go[i] = nullptr;
		}
	}
};
node *root;

int getsz(node *a) {
	if (a == nullptr) {
		return 0;
	}
	return a->sz;
}

void add(node *v, string s) {
	vector<node *> all;
	for (int i = 0; i < s.size(); i++) {
		all.push_back(v);
		if (v->go[s[i] - 'a'] == nullptr) {
			v->go[s[i] - 'a'] = new node();
		}
		v = v->go[s[i] - 'a'];
	}
	for (int i = (int)all.size() - 1; i >= 0; i--) {
		all[i]->sz = 1;
		for (int k = 0; k < 26; k++) {
			all[i]->sz += getsz(all[i]->go[k]);
		}
	}
}

void dfs(int v, int skip, int p, string &s) {
	if (skip != 0 && p != -1) {
		s.push_back(ch[v] + 'a');
	}
	if (g[v].size() == 0) {
		add(root, s);
		if (skip != 0 && p != -1) {
			s.pop_back();
		}
		return;
	}
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		dfs(to, skip - 1, v, s);
	}
	if (skip != 0 && p != -1) {
		s.pop_back();
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		char c;
		cin >> a >> b >> c;
		a--, b--;
		g[a].push_back(b);
		ch[b] = c - 'a';
	}
	int id = 0;
	int ans = MAXN;
	for (int i = 1; i < MAXN; i++) {
		root = new node();
		string tmp;
		dfs(0, i, -1, tmp);
		// cerr << getsz(root) << ' ';
		if (getsz(root) < ans) {
			ans = getsz(root);
			id = i;
		}
	}
	// cerr << '\n';
	cout << ans << '\n' << id << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("Fs.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}