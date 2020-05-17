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
	const int MAXN = 100;
#else
	const int MAXN = 4e5 + 500;
#endif

#define int ll

int n;

struct treap {
	treap *l = nullptr, *r = nullptr, *p = nullptr;
	int sz = 1;
	int y;
	pair<int, int> x;
	pair<int, int> ans;
	int push = 0;
	treap(int v, int H) {
		x = {H, v};
		ans = x;
		y = rand();
		// cerr << "new vertex: " << v << ' ' << y << '\n';
	}
};

int getsz(treap *&t) {
	return t == nullptr ? 0ll : t->sz;
}

pair<int, int> getans(treap *&t) {
	return t == nullptr ? make_pair(MAXN + 100ll, 0ll) : t->ans;
}

void push(treap *&t) {
	if (t == nullptr) {
		return;
	}
	t->x.first += t->push;
	t->ans.first += t->push;
	if (t->l != nullptr) {
		t->l->push += t->push;
	}
	if (t->r != nullptr) {
		t->r->push += t->push;
	}
	t->push = 0;
}

void upd(treap *&t) {
	if (t == nullptr) {
		return;
	}
	t->sz = 1 + getsz(t->l) + getsz(t->r);
	t->ans = min(t->x, min(getans(t->l), getans(t->r)));
	if (t->l != nullptr) {
		t->l->p = t;
	}
	if (t->r != nullptr) {
		t->r->p = t;
	}
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
	push(l->l);
	push(l->r);
	push(r->l);
	push(r->r);
	if (l->y > r->y) {
		merge(l->r, l->r, r);
		t = l;
	}
	else {
		merge(r->l, l, r->l);
		t = r;
	}
	upd(t);
}

void split(treap *t, treap *&l, treap *&r, int x) {
	push(t);
	if (t == nullptr) {
		l = nullptr;
		r = nullptr;
		return;
	}
	push(t->l);
	push(t->r);
	if (x <= getsz(t->l)) {
		split(t->l, l, t->l, x);
		r = t;
	}
	else {
		split(t->r, t->r, r, x - getsz(t->l) - 1);
		l = t;
	}
	upd(l);
	upd(r);
}

int pre[MAXN];
int add[MAXN];
vector<int> g[MAXN];
vector<int> eul;
int h[MAXN];
int dsu[MAXN];
treap *roots[MAXN];
treap *vert[MAXN];

int get(int x) {
	if (dsu[x] == x) {
		return x;
	}
	return dsu[x] = get(dsu[x]);
}

void dfs(int v, int H = 1) {
	eul.push_back(v);
	h[v] = H;
	for (auto to : g[v]) {
		dfs(to, H + 1);
		eul.push_back(v);
	}
	eul.push_back(v);
}

int get_sz(int v) {
	// cerr << "getsz " << v << ' ';
	auto t = vert[v];
	push(t);
	upd(t);
	int lft = getsz(t->l);
	while (t->p != nullptr) {
		upd(t->p);
		if (t->p->r == t) {
			lft += getsz(t->p->l) + 1;
		}
		t = t->p;
	}
	// cerr << lft << '\n';
	return lft;
}

int get_r(treap *t) {
	push(t);
	if (t->r == nullptr) {
		return t->x.first;
	}
	return get_r(t->r);
}

void print(treap *t) {
	if (t == nullptr) {
		return;
	}
	push(t);
	print(t->l);
	#ifdef DEBUG
		cerr << t->x.second << ' ';
	#endif
	print(t->r);
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
		add[i] = -1;
	}
}

inline void solve() {
	init();
	for (int i = 1; i <= n; i++) {
		cin >> pre[i];
		g[pre[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		if (pre[i] == 0) {
			eul.clear();
			dfs(i);
			treap *t = nullptr;
			for (auto it : eul) {
				dsu[it] = i;
				treap *nxt = new treap(it, h[it]);
				if (add[it] == -1) {
					add[it] = getsz(t);
					vert[it] = nxt; 
				}
				merge(t, t, nxt);
			}
			roots[i] = t;
		}
	}
	int k;
	cin >> k;
	int last = 0;
	for (int i = 0; i < k; i++) {
		// last = 0;
		int t;
		cin >> t;
		if (t == 0) {
			int a, b;
			cin >> a >> b;
			a = (a - 1 + last) % n + 1;
			b = (b - 1 + last) % n + 1;
			#ifdef DEBUG
				cerr << "get " << a << ' ' << b << '\n';
			#endif
			if (a == b) {
				last = a;
				cout << a << '\n';
				#ifdef DEBUG
					cerr << '\n';
				#endif
				continue;
			}
			if (get(a) != get(b)) {
				last = 0;
				cout << "0\n";
				#ifdef DEBUG
					cerr << '\n';
				#endif
				continue;
			}
			// print(roots[get(a)]);
			#ifdef DEBUG
				cerr << '\n';
			#endif
			int sza = get_sz(a);
			int szb = get_sz(b);
			if (sza > szb) {
				swap(a, b);
				swap(sza, szb);
			}
			#ifdef DEBUG
				cerr << "sza/b: " << sza << ' ' << szb << '\n';
			#endif
			treap *L = nullptr, *M = nullptr, *R = nullptr;
			split(roots[get(a)], L, R, szb + 1);
			split(L, L, M, sza);
			// #ifdef CERR
			// 	print(M);
			// 	cerr << '\n';
			// #endif
			int ans = getans(M).second;
			last = ans;
			cout << ans << '\n';
			merge(L, L, M);
			merge(roots[get(a)], L, R);
		}
		else {
			int a, b;
			cin >> a >> b;
			a = (a - 1 + last) % n + 1;
			b = (b - 1 + last) % n + 1;
			#ifdef DEBUG
				cerr << "query " << a << ' ' << b << '\n';
			#endif
			swap(a, b);
			int sza = get_sz(a);
			treap *L = nullptr, *R = nullptr;
			split(roots[get(a)], L, R, sza + 1);
			#ifdef DEBUG
				cerr << "szl/r: " << getsz(L) << ' ' << getsz(R) << '\n';
			#endif
			dsu[b] = a;
			#ifdef DEBUG
				cerr << get_r(L) << '\n';
			#endif
			roots[b]->push += get_r(L);
			push(roots[b]);
			#ifdef DEBUG
				cerr << "h of vert: " << get_r(L) << '\n';
			#endif
			merge(roots[b], roots[b], new treap(a, get_r(L)));
			merge(L, L, roots[b]);
			merge(roots[get(a)], L, R);
			// print(roots[get(a)]);
			#ifdef DEBUG
				cerr << '\n';
			#endif
		}
		#ifdef DEBUG
			cerr << '\n';
		#endif
	}
}


signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}