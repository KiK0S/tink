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
	const int MAXLOG = 5;
#else
	const int MAXN = 2e6;
	const int MAXLOG = 22;
#endif

int n, m;

struct Tree {
	int x;
	int id = MAXN - 1;
	int color = -1;
	Tree *parent = nullptr;
	vector<Tree *> sons;
	Tree() {}
	Tree(int a) {
		x = a;
	}
	Tree(int a, int b) {
		x = a, id = b;
	}
	ll val() {
		return 1ll * x * MAXN + id;
	}
};

struct Heap {
	int id = -1;
	vector<Tree *> all;
	Heap() {
		all.resize(MAXLOG);
		for (int i = 0; i < MAXLOG; i++) {
			all[i] = nullptr;
		}
	}
};

int r(Tree *t) {
	if (t == nullptr) {
		return -1;
	}
	return t->sons.size();
}


Tree * ptr[MAXN];

void merge_trees(Tree *&a, Tree *&b) {
	if (a->val() > b->val()) {
		swap(a, b);
	}
	a->sons.push_back(b);
	b->parent = a;
}

void meld(Heap *a, Heap *b) {
	Tree *carry = nullptr;
	for (int i = 0; i < MAXLOG; i++) {
		if (carry != nullptr && b->all[i] != nullptr) {
			merge_trees(carry, b->all[i]);
			continue;	
		}
		if (carry == nullptr && b->all[i] == nullptr) {
			continue;
		}
		if (a->all[i] == nullptr) {
			if (carry != nullptr) {
				a->all[i] = carry;
				carry = nullptr;
			}
			if (b->all[i] != nullptr) {
				a->all[i] = b->all[i];
			}
		}
		else {
			if (carry != nullptr) {
				merge_trees(a->all[i], carry);
			}
			if (b->all[i] != nullptr) {
				merge_trees(a->all[i], b->all[i]);
			}
			carry = a->all[i];
			a->all[i] = nullptr;
		}
	}
	for (int i = 0; i < MAXLOG; i++) {
		if (a->all[i] != nullptr) {
			a->all[i]->color = a->id;
		}
		b->all[i] = nullptr;
	}
}

void print(Tree *t, int _t = 0) {
	if (t == nullptr) {
		return;
	}
	for (int i = 0; i < _t; i++) {
		cerr << '\t';
	}
	cerr << t->x << '\n';
	for (auto it : t->sons) {
		print(it, _t + 1);
	}
}

void print(Heap *h) {
	return;
	for (int i = 0; i < MAXLOG; i++) {
		if (h->all[i] != nullptr) {
			cerr << "tree range " << i << '\n';
			print(h->all[i]);
			cerr << '\n';
		}
	}
	cerr << '\n';
}

inline void init() {

}

inline void solve() {
	init();
	vector<Heap *> heaps(n, nullptr);
	for (int i = 0; i < n; i++) {
		heaps[i] = new Heap();
		heaps[i]->id = i;
		heaps[i]->all.resize(MAXLOG);
	}
	int add_id = 1;
	for (int i = 0; i < m; i++) {
		// cerr << "query " << i << '\n';
		cout.flush();
		int type;
		cin >> type;
		if (type == 0) {
			int a, b;
			cin >> a >> b;
			swap(a, b);
			b--;
			Tree * nw = new Tree(a, add_id);
			Heap * tmp = new Heap();
			tmp->all[0] = nw;
			ptr[add_id++] = nw;
			meld(heaps[b], tmp);
			print(heaps[b]);
		}
		if (type == 1) {
			int a, b;
			cin >> a >> b;
			a--, b--;
			swap(a, b);
			meld(heaps[a], heaps[b]);
			print(heaps[a]);
		}
		if (type == 2) {
			int a;
			cin >> a;
			Tree *t = ptr[a];
			if (t == nullptr) {
				continue;
			}
			while (t->parent != nullptr) {
				swap(t->x, t->parent->x);
				swap(t->id, t->parent->id);
				ptr[t->id] = t;
				t = t->parent;
			}
			assert(heaps[t->color]->all[r(t)] == t);
			Heap *tmp = new Heap();
			for (int i = 0; i < r(t); i++) {
				tmp->all[i] = t->sons[i];
				t->sons[i]->parent = nullptr;
			}
			delete t;
			ptr[a] = nullptr;
			heaps[t->color]->all[r(t)] = nullptr;
			meld(heaps[t->color], tmp);
			print(heaps[t->color]);
		}
		if (type == 3) {
			int a, b;
			cin >> a >> b;
			Tree *t = ptr[a];
			if (t == nullptr) {
				continue;
			}
			t->x = b;
			print(heaps[t->color]);
			while (t->parent != nullptr) {
				swap(t->x, t->parent->x);
				swap(t->id, t->parent->id);
				ptr[t->id] = t;
				t = t->parent;
			}
			ptr[a] = t;
			assert(heaps[t->color]->all[r(t)] == t);
			int pos = t->color;
			print(heaps[t->color]);
			Heap *tmp = new Heap();
			heaps[pos]->all[r(t)] = nullptr;
			for (int j = 0; j < r(t); j++) {
				tmp->all[j] = t->sons[j];
				t->sons[j]->parent = nullptr;
			}
			t->sons.clear();
			meld(heaps[pos], tmp);
			tmp = new Heap();
			ptr[a] = t;
			tmp->all[0] = t;
			print(heaps[pos]);

			meld(heaps[pos], tmp);
			print(heaps[pos]);
		}
		if (type == 4) {
			int a;
			cin >> a;
			a--;
			int ans = 2e9;
			for (int i = 0; i < MAXLOG; i++) {
				if (heaps[a]->all[i] != nullptr) {
					ans = min(ans, heaps[a]->all[i]->x);
				}
			}
			cout << ans << '\n';
			print(heaps[a]);
		}
		if (type == 5) {
			int a;
			cin >> a;
			a--;
			ll ans = 1e18;
			int res = -1;
			for (int i = 0; i < MAXLOG; i++) {
				if (heaps[a]->all[i] != nullptr) {
					if (ans > heaps[a]->all[i]->val()) {
						ans = heaps[a]->all[i]->val();
						res = i;
					}
				}
			}
			if (res == -1) {
				continue;
			}
			ptr[heaps[a]->all[res]->id] = nullptr;
			Heap *tmp = new Heap();
			for (int j = 0; j < r(heaps[a]->all[res]); j++) {
				tmp->all[j] = heaps[a]->all[res]->sons[j];
				tmp->all[j]->parent = nullptr;
			}
			heaps[a]->all[res] = nullptr;
			delete heaps[a]->all[res];
			meld(heaps[a], tmp);
			print(heaps[a]);
		}
	}
	exit(0);
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
	while (cin >> n >> m)
		solve();
	return 0;
}