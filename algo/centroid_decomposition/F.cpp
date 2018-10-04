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

struct node {
	node * go[26];
	int sz;
	node() {
		sz = 1;
		for (int i = 0; i < 26; i++) {
			go[i] = nullptr;
		}
	}
};

node * root[MAXN];
vector<int> g[MAXN];
int sz[MAXN];
int h[MAXN];
int ch[MAXN];
int cnt[MAXN];
int ans[MAXN];

int getsz(node *a) {
	if (a == nullptr) {
		return 0;
	}
	return a->sz;
}

void print(node *v) {
	if (v == nullptr) {
		return;
	}
	cerr << getsz(v) << '\n';;
	for (int i = 0; i < 26; i++) {
		if (v->go[i] != nullptr) {
			cerr << char(i + 'a') << '\n';
			print(v->go[i]);
		}
	}
}

void add(node *a, node *b) {
	if (b == nullptr) {
		return;
	}
	for (int i = 0; i < 26; i++) {
		if (b->go[i] != nullptr) {
			if (a->go[i] != nullptr) {
				add(a->go[i], b->go[i]);
			}
			else {
				a->go[i] = new node();
				add(a->go[i], b->go[i]);
			}
		}
	}
	a->sz = 1;
	for (int i = 0; i < 26; i++) {
		a->sz += getsz(a->go[i]);
	}
}

int calc_add_size(node *a, node *b) {
	if (b == nullptr) {
		return 0;
	}
	int ans = 0;
	for (int i = 0; i < 26; i++) {
		if (b->go[i] != nullptr) {
			if (a->go[i] == nullptr) {
				ans += getsz(b->go[i]);
			}
			else {
				ans += calc_add_size(a->go[i], b->go[i]);
			}
		}
	}
	return ans;
}


void dfs(int v, int p = -1) {
	int mx = -1;
	h[v] = (p == -1 ? 1 : h[p] + 1);
	cnt[h[v]]++;
	sz[v] = 1;
	if (g[v].size() == 0) {
		root[v] = new node();
		return;
	}
	int id = -1;
	for (auto to : g[v]) {
		if (to == p) {
			continue;
		}
		dfs(to, v);
		sz[v] += sz[to];
		if (getsz(root[to]) > mx) {
			mx = getsz(root[to]);
			id = to;
		}
	}
	// cerr << v << ' ' << id << '\n';
	node *all = new node();
	for (auto to : g[v]) {
		if (to == p || to == id) {
			continue;
		}
		add(all, root[to]);
	}
	int cur = getsz(root[id]) + calc_add_size(root[id], all) - 1;
	ans[h[v]] += cur;
	// cerr << v << ' ' << getsz(root[id]) << ' ' << calc_add_size(root[id], all) << ' ' << cur << '\n';
	root[v] = new node();
	root[v]->go[ch[id]] = root[id];
	root[v]->sz += getsz(root[id]);
	for (auto to : g[v]) {
		if (to == id || to == p) {
			continue;
		}
		if (root[v]->go[ch[to]] == nullptr) {
			root[v]->go[ch[to]] = root[to];
			root[v]->sz += getsz(root[to]);
		}
		else {
			add(root[v]->go[ch[to]], root[to]);
		}
	}
	// cerr << "! " << v << ' ' << getsz(root[v]) << '\n';
}

inline void init() {

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
	dfs(0);
	int best = 1;
	int cur = 0;
	for (int i = 1; i < MAXN; i++) {
		cur += cnt[i];
		ans[i] += cur;
		// cerr << ans[i] << ' ';
		if (ans[i] < ans[best]) {
			best = i;
		}
	}
	// cerr << '\n';
	cout << ans[best] << '\n' << best << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}