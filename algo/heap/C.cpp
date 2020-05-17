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
	node *left = nullptr;
	node *right = nullptr;
	node *parent = nullptr;
	bool rev = 0;
	int x;
	int ans;
	int sz;
	node () {
		sz = 1;
	}
	node (int a) {
		x = ans = a;
		sz = 1;
	}

	bool is_left() {
		return this->parent->left == this;
	}

	bool is_root() {
		return this->parent == nullptr;
	}
};

int get_ans(node *t) {
	if (t == nullptr) {
		return INF;
	}
	return t->ans;
}

int get_x(node *t) {
	if (t == nullptr) {
		return INF;
	}
	return t->x;
}

int get_sz(node *t) {
	if (t == nullptr) {
		return 0;
	}
	return t->sz;
}

void upd(node *t) {
	if (t == nullptr) {
		return;
	}
	t->sz = 1 + get_sz(t->left) + get_sz(t->right);
	t->ans = min(min(get_ans(t->left), get_ans(t->right)), t->x);
}

void push(node *t, int depth = 1) {
	if (t == nullptr) {
		return;
	}
	if (depth == 0) {
		return;
	}
	if (t->rev == 1) {
		node *tmp = t->left;
		t->left = t->right;
		t->right = tmp;
		if (t->left != nullptr) {
			t->left->rev ^= 1;
		}
		if (t->right != nullptr) {
			t->right->rev ^= 1;
		}
	}
	t->rev = 0;
	push(t->left, depth - 1);
	push(t->right, depth - 1);
}

void rotate(node *t) {
	push(t);
	push(t->parent);
	if (t->parent->parent != nullptr) {
		if (t->parent->is_left()) {
			t->parent->parent->left = t;		
		}
		else {
			t->parent->parent->right = t;
		}
	}
	if (t->is_left()) {
		if (t->right != nullptr) {
			t->right->parent = t->parent;
		}
		t->parent->left = t->right;
		t->right = t->parent;
		t->parent = t->parent->parent;
		t->right->parent = t;
		upd(t->right);
	}
	else {
		if (t->left != nullptr) {
			t->left->parent = t->parent;
		}
		t->parent->right = t->left;
		t->left = t->parent;
		t->parent = t->parent->parent;
		t->left->parent = t;
		upd(t->left);
	}
	upd(t);
}

bool zig(node *t) {
	if (t->parent->is_root()) {
		rotate(t);
		return 1;
	}
	return 0;
}

bool zig_zig(node *t) {
	bool a = t->is_left();
	bool b = t->parent->is_left();
	if (a ^ b == 0) {
		rotate(t->parent);
		rotate(t);
		return 1;
	}
	return 0;
}

bool zig_zag(node *t) {
	rotate(t);
	rotate(t);
	return 1;
}

node *root = nullptr;

void splay(node *t) {
	while (!t->is_root()) {
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
	root = t;
}

node * get(node *t, int x) {
	push(t);
	if (t == nullptr) {
		return nullptr;
	}
	if (get_sz(t->left) >= x) {
		return get(t->left, x);
	}
	if (get_sz(t->left) == x - 1) {
		return t;
	}
	return get(t->right, x - get_sz(t->left) - 1);

}



inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		node * nw = new node(a);
		if (root == nullptr) {
			root = nw;
		}
		else {
			node *t = root;
			while (t->right != nullptr) {
				t = t->right;
			}
			t->right = nw;
			nw->parent = t;
			splay(nw);
		}
	}
	for (int i = 0; i < m; i++) {
		// cerr << "query " << i << '\n';
		int tp, l, r;
		cin >> tp >> l >> r;
		node *L = nullptr, *M = nullptr, *R = nullptr;
		node *t = get(root, r);
		splay(t);
		R = t->right;
		t->right = nullptr;
		if (R != nullptr) {
			R->parent = nullptr;
		}
		upd(t);
		t = get(t, l);
		splay(t);
		L = t->left;
		t->left = nullptr;
		if (L != nullptr) {
			L->parent = nullptr;
		}
		upd(t);
		M = t;
		if (tp == 1) {
			M->rev ^= 1;
			push(M);
		}
		else {
			cout << get_ans(M) << '\n';
		}
		if (L != nullptr) {
			push(L);
			while (L->right != nullptr) {
				L = L->right;
				push(L);
			}
			splay(L);
			L->right = M;
			M->parent = L;
			upd(L);
		}
		else {
			L = M;
		}
		if (R != nullptr) {
			push(L);
			while (L->right != nullptr) {
				L = L->right;
				push(L);
			}
			splay(L);
			L->right = R;
			R->parent = L;
			upd(L);	
		}
		root = L;
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
	while (cin >> n >> m)
		solve();
	return 0;
}