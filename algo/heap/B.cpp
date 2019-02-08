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

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

int n;
int INF = 2e9;

struct node {
	int x;
	node *parent = nullptr;
	node *left = nullptr;
	node *right = nullptr;
	int mn = INF;
	int mx = -INF;
	node(){}
	node(int a) {
		x = a;
	}
	bool is_left() {
		if (this->parent == nullptr) {
			return 0;
		}
		return this->parent->left == this;
	}
};

int get_mn(node *t) {
	return t == nullptr ? INF : t->mn;
}

int get_mx(node *t) {
	return t == nullptr ? -INF : t->mx;
}

void print(node *t, int tb = 0) {
	if (t == nullptr) {
		return;
	}
	print(t->left, tb + 1);
	for (int i = 0; i < tb; i++) {
		std::cerr << '\t';
	}
	std::cerr << t->x << '\n';
	print(t->right, tb + 1);
}

void upd(node *t) {
	if (t == nullptr) {
		return;
	}
	t->mn = std::min(t->x, std::min(get_mn(t->left), get_mn(t->right)));
	t->mx = std::max(t->x, std::max(get_mx(t->left), get_mx(t->right)));
}

node *root;

bool is_root(node *t) {
	return t->parent == nullptr;
}

void make_parent(node *t, node *p) {
	if (t == nullptr) {
		return;
	}
	t->parent = p;
}

void rotate(node *t) {
	if (t->parent->is_left()) {
		t->parent->parent->left = t;
	}
	else if (t->parent->parent != nullptr) {
		t->parent->parent->right = t;
	}
	if (t->is_left()) {
		make_parent(t->right, t->parent);
		t->parent->left = t->right;
		t->right = t->parent;
		t->parent = t->parent->parent;
		t->right->parent = t;
		upd(t->right);
		upd(t);
	}
	else {
		make_parent(t->left, t->parent);
		t->parent->right = t->left;
		t->left = t->parent;
		t->parent = t->parent->parent;
		t->left->parent = t;
		upd(t->left);
		upd(t);
	}
	
}

bool zig(node *t) {
	if (is_root(t->parent)) {
		rotate(t);
		return 1;
	}
	return 0;
}

bool zig_zig(node *t) {
	if (!(t->is_left() ^ t->parent->is_left())) {
		rotate(t->parent);
		rotate(t);
		return 1;
	}
	return 0;
}

void zig_zag(node *t) {
	rotate(t);
	rotate(t);
}

void splay(node *t) {
	while (!is_root(t)) {
		if (zig(t)) {
			continue;
		}
		if (zig_zig(t)) {
			continue;
		}
		zig_zag(t);
	}
	root = t;
}

node * find(node *t, int x) {
	if (t == nullptr || t->x == x) {
		return t;
	}
	if (t->x > x) {
		return find(t->left, x);
	}
	return find(t->right, x);
}

void insert(node *&t, node *nw) {
	if (t == nullptr) {
		t = nw;
		return;
	}
	if (t->x == nw->x) {
		return;
	}
	if (t->x > nw->x) {
		if (t->left == nullptr) {
			t->left = nw;
			nw->parent = t;
			upd(t);
			splay(nw);
			return;
		}
		insert(t->left, nw);
	}
	else {
		if (t->right == nullptr) {
			t->right = nw;
			nw->parent = t;
			upd(t);
			splay(nw);
			return;
		}
		insert(t->right, nw);
	}
}

node * merge(node *A, node *B) {
	if (A == nullptr) {
		return B;
	}
	while (A->right != nullptr) {
		A = A->right;
	}
	splay(A);
	A->right = B;
	make_parent(B, A);
	upd(A);
	return A;
}

void erase(node *&t, int x) {
	node *p = find(t, x);
	if (p == nullptr) {
		return;
	}
	splay(p);
	if (p->left != nullptr) {
		p->left->parent = nullptr;
	}
	if (p->right != nullptr) {
		p->right->parent = nullptr;
	}
	t = merge(p->left, p->right);
}

void exists(node *t, int x) {
	node *p = nullptr;
	if ((p = find(t, x)) == nullptr) {
		std::cout << "false\n";
		return;
	}
	splay(p);
	std::cout << "true\n";
}

int next(node *t, int x) {
	if (t == nullptr) {
		return get_mx(t);
	}
	if (get_mx(t->left) > x) {
		return next(t->left, x);
	}
	if (t->x > x) {
		splay(t);
		return t->x;
	}
	if (t->right == nullptr) {
		splay(t);
		return -INF;
	}
	return next(t->right, x);
}

int prev(node *t, int x) {
	if (t == nullptr) {
		return get_mn(t);
	}
	if (get_mn(t->right) < x) {
		return prev(t->right, x);
	}
	if (t->x < x) {
		splay(t);
		return t->x;
	}
	if (t->left == nullptr) {
		splay(t);
		return INF;
	}
	return prev(t->left, x);
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::string s;
	int x;
	root = nullptr;
	while (std::cin >> s >> x) {
		if (s == "insert") {
			insert(root, new node(x));
		}
		if (s == "delete") {
			erase(root, x);
		}
		if (s == "exists") {
			exists(root, x);
		}
		if (s == "next") {
			int res = next(root, x);
			if (res == -INF) {
				std::cout << "none\n";
			}
			else {
				std::cout << res << '\n';
			}
		}
		if (s == "prev") {
			int res = prev(root, x);
			if (res == INF) {
				std::cout << "none\n";
			}
			else {
				std::cout << res << '\n';
			}		
		}
	}

	return 0;
}