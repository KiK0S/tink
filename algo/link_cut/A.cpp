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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
	#define rng rand
	// mt19937 rng(228);
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
	mt19937 rng(time(0));
#endif


const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m;

struct path;

struct treap {
	treap *l = nullptr, *r = nullptr, *p = nullptr;
	int y;
	int sz;
	int rev;
	int x;
	path *pre = nullptr;

	treap() {
		y = rng();
		sz = 1;
		rev = 0;
	}

	treap(int a) {
		x = a;
		y = rng();
		sz = 1;
		rev = 0;
	}
};

void push(treap *t) {
	if (t == nullptr) {
		return;
	}
	if (t->rev & 1) {
		t->rev = 0;
		swap(t->l, t->r);
		if (t->l != nullptr) {
			t->l->rev ^= 1;
		}
		if (t->r != nullptr) {
			t->r->rev ^= 1;
		}
	}
	if (t->l != nullptr) {
		t->l->pre = t->pre;
	}
	if (t->r != nullptr) {
		t->r->pre = t->pre;
	}
}

int getsz(treap *t) {
	if (t == nullptr) {
		return 0;
	}
	return t->sz;
}



void print(treap *t, int _t = 0) {
	push(t);
	if (t == nullptr) {
		return;
	}
	print(t->l, _t + 1);
	for (int i = 0; i < _t; i++) {
		cerr << '\t';
	}
	cerr << t << ' ' << getsz(t) << '\n';
	print(t->r, _t + 1);
}



void upd(treap *t) {
	if (t == nullptr) {
		return;
	}
	t->sz = 1 + getsz(t->l) + getsz(t->r);
}

void merge(treap *&t, treap *l, treap *r) {
	push(l);
	push(r);
	if (l == nullptr) {
		t = r;
		upd(t);
		return;
	}
	if (r == nullptr) {
		t = l;
		upd(t);
		return;
	}
	if (l->y > r->y) {
		merge(l->r, l->r, r);
		if (l->r != nullptr) {
			l->r->p = l;
		}
		t = l;
	}
	else {
		merge(r->l, l, r->l);
		if (r->l != nullptr) {
			r->l->p = r;
		}
		t = r;
	}
	upd(t);
}

void split(treap *t, treap *&l, treap *&r, int x) {
	// cerr << "split " << t << ' ' << x << '\n';
	push(t);
	if (t == nullptr) {
		l = nullptr;
		r = nullptr;
		upd(l);
		upd(r);
		return;
	}
	int ss = getsz(t->l) + 1;
	if (ss < x) {
		split(t->r, t->r, r, x - ss);
		l = t;
		if (t->r != nullptr) {
			t->r->p = t;
		}
		if (r != nullptr) {
			r->p = nullptr;
		}
	}
	else {
		split(t->l, l, t->l, x);
		r = t;
		if (t->l != nullptr) {
			t->l->p = t;
		}
		if (l != nullptr) {
			l->p = nullptr;
		}
	}
	upd(l);
	upd(r);
}

treap * vertex[MAXN];

int get_index(int v) {
	// cerr << "get_index\n";
	auto t = vertex[v];
	vector<treap *> tr;
	tr.push_back(t);
	while (t->p != nullptr) {
		t = t->p;
		tr.push_back(t);
	}
	reverse(tr.begin(), tr.end());
	// print(tr[0]);
	for (auto x : tr) {
		push(x);
	}
	t = vertex[v];
	int res = getsz(t->l) + 1;
	while (t->p != nullptr) {
		// cerr << t->x << '\n';
		// cerr << t->p->l << ' ' << t->p->r << ' ' << t << '\n';
		if (t->p->r == t) {
			res += getsz(t->p->l) + 1;
		}
		t = t->p;
	}
	// cerr << "res = " << res + 1 << '\n';
	return res + 1;
}

path * get_path(int v) {
	auto t = vertex[v];
	while (t->p != nullptr) {
		t = t->p;
	}
	return t->pre;	
}
struct path {
	treap *t = nullptr;
	int parent = -1;
};

vector<path *> all_path;

int get_parent(path *p) {
	if (p == nullptr) {
		return -1;
	}
	return p->parent;
}

void expose(int v) {
	path * p = get_path(v);
	// assert(p != nullptr);
	while (p->parent != -1) {
		int to = p->parent;
		auto P = get_path(to);
		// assert(P != nullptr);
		// cerr << p << ' ' << P << '\n';
		// cerr << "vertex " << to << ' ' << get_index(to) << '\n';
		treap *L = nullptr, *R = nullptr;
		// cerr << "nect treap vefore split\n";
		// print(P->t);
		split(P->t, L, R, get_index(to));
		// cerr << getsz(L) << ' ' << getsz(R) << '\n';
		// assert(L != nullptr);
		L->p = nullptr;
		p->parent = get_parent(L->pre);
		// cerr << "my treap\n";
		// print(p->t);
		// cerr << "next treap\n";
		// print(L);
		merge(p->t, L, p->t);
		p->t->pre = p;
		if (R != nullptr) {
			R->p = nullptr;
			R->pre->parent = to;
			R->pre->t = R;
		}
	}
	// for (int j = 0; j < n; j++) {
	// 	cerr << vertex[j] << ' ' << vertex[j]->l << ' ' << vertex[j]->r << ' ' << vertex[j]->p << '\n';
	// }
	{
		treap *L = nullptr, *R = nullptr;
		// assert(p != nullptr);
		// cerr << "last split\n";
		// print(p->t);
		// cerr << getsz(p->t) << ' ' << get_index(v) + 1 << '\n';
		split(p->t, L, R, get_index(v));
		if (R != nullptr) {
			R->pre = new path();
			R->pre->t = R;
			all_path.push_back(R->pre);
			R->pre->parent = v;
		}
		p->t = L;
		p->t->p = nullptr;
	}
}

void make_parent(int v) {
	// cerr << "expose\n";
	expose(v);
	// cerr << "rev\n";
	// assert(get_path(v) != nullptr);
	// assert(get_path(v)->t != nullptr);
	get_path(v)->t->rev ^= 1;
}

void link(int a, int b) {
	make_parent(a);
	make_parent(b);
	// assert(get_path(b) != nullptr);
	get_path(b)->parent = a;
	// cerr << get_path(a) << ' ' << get_path(b) << '\n';
	// cerr << get_path(a)->parent << ' ' << get_path(b)->parent << '\n';
}

void cut(int a, int b) {
	// cerr << "make_parent\n";
	make_parent(a);
	// cerr << "expose\n";
	expose(b);
	treap *L = nullptr, *R = nullptr;
	split(get_path(b)->t, L, R, 2);
	// cerr << getsz(L) << ' ' << getsz(R) << '\n';
	// cerr << L->x << ' ' << R->x << '\n';
	L->p = nullptr;
	L->pre = new path();
	all_path.push_back(L->pre);
	L->pre->t = L;
	L->pre->parent = -1;
	if (R != nullptr) {
		R->p = nullptr;
		R->pre->t = R;
		R->pre->parent = -1;
	}
}

int get(int a, int b) {
	// cerr << get_path(a) << ' ' << get_path(b) << '\n';
	// cerr << get_path(a)->parent << ' ' << get_path(b)->parent << '\n';
	make_parent(a);
	// print(get_path(a)->t);
	// cerr << "exposing\n";
	expose(b);
	// print(get_path(b)->t);
	// cerr << get_path(a) << ' ' << get_path(b) << '\n';
	// cerr << get_path(a)->parent << ' ' << get_path(b)->parent << '\n';
	if (get_path(a) != get_path(b)) {
		return -1;
	}
	// assert(get_path(b) != nullptr);
	return getsz(get_path(b)->t) - 1;
}


inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		vertex[i] = new treap(i);
		vertex[i]->pre = new path();
		vertex[i]->pre->t = vertex[i];
		vertex[i]->pre->parent = -1;
		all_path.push_back(vertex[i]->pre);
		// cerr << vertex[i]->y << ' ';
	}
	// cerr << '\n';
	// treap *root = nullptr; TEST TREAP
	// for (int i = 0; i < n; i++) {
	// 	merge(root, root, new treap(i));
	// }
	// treap *L = nullptr, *R = nullptr;
	// split(root, L, R, 2);
	// cerr << getsz(L) << ' ' << getsz(R) << '\n';
	for (int i = 0; i < m; i++) {

		cerr << "QUERY " << i << '\n';
		string s;
		cin >> s;
		int a, b;
		cin >> a >> b;
		a--, b--;
		if (s == "link") {	
			link(a, b);
		}
		if (s == "cut") {
			cut(a, b);
		}
		if (s == "get") {
			cout << get(a, b) << endl;
		}
		// for (int j = 0; j < n; j++) {
		// 	if (vertex[j]->p == nullptr) {
		// 		cerr << "[\n";
		// 		print(vertex[j]);
		// 		cerr << "]\n";
		// 	}
		// }
		// for (int j = 0; j < n; j++) {
		// 	cerr << vertex[j] << ' ' << vertex[j]->l << ' ' << vertex[j]->r << ' ' << vertex[j]->p << '\n';
		// }
		// for (int j = 0; j < n; j++) {
		// 	cerr << get_path(j) << ' ';
		// }
		// cerr << '\n';
		// for (int j = 0; j < n; j++) {
		// 	cerr << get_path(j)->parent << ' ';
		// }
		// cerr << '\n';
		// if (i == 2) {
		// 	break;
		// }
	}
	for (auto x : all_path) {
		delete x;
		// cerr << x << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}