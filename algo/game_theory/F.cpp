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
	const int MAXN = 10;
#else
	const int MAXN = 5e5 + 100;
#endif

int n;

const int LOG = 20;

struct node {
	node *l = nullptr, *r = nullptr;
	int cnt = 0;
};

struct trie {
	node * t = new node();
	int _xor = 0;
};

int sum(node *v) {
	return v == nullptr ? 0 : v->cnt;
}

void add(trie *t, int x) {
	// x ^= t->_xor;
	// cerr << "add " << x << '\n';
	node * v = t->t;
	vector<node *> all_v;
	for (int i = LOG - 1; i >= 0; i--) {
		v->cnt++;
		all_v.push_back(v);
		if (!(x & (1 << i))) {
			if (v->l == nullptr) {
				v->l = new node();
			}
			v = v->l;
		}
		else {
			if (v->r == nullptr) {
				v->r = new node();
			}
			v = v->r;		
		}
	}
	v->cnt++;
	if (v->cnt == 2) {
		v->cnt--;
		for (auto it : all_v) {
			it->cnt--;
		}
	}
}

int mex(trie *t) {
	// cerr << "mex xor " << t->_xor << '\n';
	int res = 0;
	node *v = t->t;
	for (int i = LOG - 1; i >= 0; i--) {
		if (v == nullptr) {
			break;
		}
		if (!(t->_xor & (1 << i))) {
			if (sum(v->l) < (1 << i)) {
				v = v->l;
			}
			else {
				v = v->r;
				res += (1 << i);
			}
		}	
		else {
			if (sum(v->r) < (1 << i)) {
				v = v->r;
				// cerr  << "1 << " << i << ' ' << '\n';
			}
			else {
				v = v->l;
				res += (1 << i);
			}
		}
	}
	return res;
}

void refill(node *v, int cur, int lg, int _xor, trie *b) {
	if (v == nullptr) {
		return;
	}
	if (lg == -1) {
		// cerr << "add " << cur << ' ' << (cur ^ _xor) << '\n';
		add(b, cur ^ _xor);
		return;
	}
	refill(v->l, cur, lg - 1, _xor, b);
	refill(v->r, cur + (1 << lg), lg - 1, _xor, b);
}

int dp[MAXN];
vector<int> g[MAXN];
trie * roots[MAXN];
int ans = 0;

void dfs(int v) {
	if (g[v].size() == 0) {
		roots[v]->t = new node();
		dp[v] = 1;
		add(roots[v], 0);
		return;
	}
	int mx = -1;
	int id = -1;
	int total_xor = 0;
	for (auto to : g[v]) {
		dfs(to);
		if (mx < sum(roots[to]->t)) {
			mx = sum(roots[to]->t);
			id = to;
		}
		total_xor ^= dp[to];
	}
	// cerr << "vertex " << v << '\n';
	// cerr << "xor_over_sons " << total_xor << '\n';
	// cerr << "favorite_son " << id << '\n';
	// cerr << "his dp " << dp[id] << '\n';
	// cerr << "his xor " << roots[id]->_xor << '\n';
	// cerr << "new_xor " << (roots[id]->_xor ^ total_xor ^ dp[id]) << '\n';
	roots[v]->t = roots[id]->t;
	roots[v]->_xor = roots[id]->_xor ^ (total_xor ^ dp[id]);
	for (auto to : g[v]) {
		if (to == id) {
			continue;
		}
		refill(roots[to]->t, 0, LOG - 1, roots[v]->_xor ^ roots[to]->_xor ^ (total_xor ^ dp[to]), roots[v]);
	}
	if (mex(roots[v]) != 0) {
		ans++;
	}
	// cerr << "current_ans " << mex(roots[v]) << '\n';
	add(roots[v], total_xor ^ roots[v]->_xor);
	dp[v] = mex(roots[v]);
	// cerr << '\n';
	// cerr << '\n';
}

inline void init() {
	for (int i = 0; i < n; i++) {
		roots[i] = new trie();
		g[i].clear();
	}
	ans = 0;
}

inline void solve() {
	init();
	// assert(n == 7);
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
	}
	dfs(0);
	cout << ans << '\n';
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