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
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

const int INF = 1e9 + 100;

int n, m;

struct node {
	int left = 0;
	int right = 0;
	int parent = 0;
	int x = 0;
	int id = 0;
	int lft = 0;
	node() {}
	node(int a, int b) {
		x = a;
		id = b;
	}
	int is_left() {
		return lft;
	}
};

vector<node> q;
map<int, node> T;

int cnt_change = 0;

void upd(int t) {
	cnt_change++;
	assert(cnt_change <= 70000);
	cout << "change " << t << ' ' << T[t].left << ' ' << T[t].right << endl;
}

void rotate(int t) {
	int nxt_lft = T[t].lft;
	if (T[T[t].parent].parent != 0) {
		if (T[T[t].parent].is_left()) {
			T[T[T[t].parent].parent].left = t;
			nxt_lft = 1;
		}
		else {
			T[T[T[t].parent].parent].right = t;
			nxt_lft = 0;
		}
	}
	else {
		nxt_lft = 0;
	}
	if (T[t].is_left()) {
		T[T[t].parent].left = T[t].right;
		T[t].right = T[t].parent;
		T[t].parent = T[T[t].parent].parent;
	}
	else {
		T[T[t].parent].right = T[t].left;
		T[t].left = T[t].parent;
		T[t].parent = T[T[t].parent].parent;
	}
	T[t].lft = nxt_lft;
}

bool zig(int t) {
	if (T[T[t].parent].parent == 0) {
		rotate(t);
		return 1;
	}
	return 0;
}

bool zig_zig(int t) {
	bool a = T[t].is_left();
	bool b = T[T[t].parent].is_left();
	if (a ^ b == 0) {
		rotate(T[t].parent);
		rotate(t);
		return 1;
	}
	return 0;
}

bool zig_zag(int t) {
	rotate(t);
	rotate(t);
	return 1;
}


void splay(int t) {
	while (T[t].parent != 0) {
		if (zig(t)) {
			continue;
		}
		if (zig_zig(t)) {
			continue;
		}
		if (zig_zag(t)) {
			continue;
		}
	}
}

int cnt_ask = 0;
void ask(int t, int p, int x) {
	cnt_ask++;
	// assert(cnt_ask <= 70000);
	cout << "val " << t << endl;
	int a, b, c;
	cin >> a >> b >> c;
	node cur(a, t);
	cur.left = b;
	cur.right = c;
	cur.parent = p;
	cur.lft = x;
	q.push_back(cur);
	T[t] = cur;
}

int got = 0;

void get(int t, int x, int p = 0, int l = 0) {
	if (t == 0) {
		return ;
	}
	ask(t, p, l);
	if (q.back().x == x) {
		return ;
	}
	if (q.back().x < x) {
		return get(q.back().right, x, t, 0);
	}
	else {
		return get(q.back().left, x, t, 1);
	}
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		q.clear();
		T.clear();
		int r, x;
		cin >> r >> x;
		get(r, x);
		node t = q.back();
		splay(t.id);
		for (auto it : q) {
			upd(it.id);
		}
		cout << "confirm " << t.id << endl;
	}
}

signed main() {
	cin >> n >> m;
	solve();
	return 0;
}