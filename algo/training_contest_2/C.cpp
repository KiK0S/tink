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
	const int MAXN = 1e4;
#else
	const int MAXN = 4e5 + 10;
#endif

struct treap {
	treap *l, *r;
	int sz;
	int x;
	int y;
	int sum;
	int balance;
	int push_balance;
	int count_sum = 0;
	int push_x;

	treap(int _x, int _sum) {
		l = nullptr;
		r = nullptr;
		sz = 1;
		x = _x;
		sum = _sum;
		count_sum = sum;
		balance = 0;
		push_balance = 0;
		push_x = 0;
		#ifdef DEBUG
			y = rand();
		#else
			y = (rand() << 15) + rand();
		#endif
	}
};
int n, m;
int val[MAXN];
int nval[MAXN];
treap *root = nullptr, *scnd = nullptr;

int getsz(treap *t) {
	if (t == nullptr) {
		return 0;
	}
	return t->sz;
}

void upd(treap *&t) {
	if (t == nullptr) {
		return;
	}
	t->count_sum = t->sum;
	if (t->l != nullptr) {
		t->l->push_balance += t->push_balance;
		t->l->push_x += t->push_x;
		t->count_sum += t->l->count_sum;
	}
	if (t->r != nullptr) {
		t->r->push_balance += t->push_balance;
		t->r->push_x += t->push_x;
		t->count_sum += t->r->count_sum;
	}
	t->balance += t->push_balance;
	t->x += t->push_x;
	t->push_x = 0;
	t->push_balance = 0;
	t->sz = getsz(t->l) + getsz(t->r) + 1;
}

void split(treap *t, treap *&l, treap *&r, int x) {
	upd(t);
	if (t == nullptr) {
		l = nullptr;
		r = nullptr;
		return;
	}
	if (getsz(t->l) + 1 >= x) {
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

void merge(treap *&t, treap *l, treap *r) {
	upd(l);
	upd(r);
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
	if (l->y >= r->y) {
		merge(l->r, l->r, r);
		t = l;
	}
	else {
		merge(r->l, l, r->l);
		t = r;
	}
	upd(t);
}

treap *& take_left(treap *t) {
	if (t == nullptr) return t;
	upd(t);
	if (t->l == nullptr) return t;
	return take_left(t->l);
}

treap *& take_right(treap *t) {
	if (t == nullptr) return t;
	upd(t);
	if (t->r == nullptr) return t;
	return take_right(t->r);
}

inline void init() {

}

void calc_nval() {
	memset(nval, 0, sizeof(nval));
	int cnt = 0;
	for (int i = MAXN - 1; i >= 1; i--) {				
		cnt += val[i];
		if (cnt) {
			nval[cnt]++;
		}
	}
}

void print(treap *t, ostream &out) {
	upd(t);
	if (t == nullptr) {
		return;
	}
	print(t->l, out);
	for (int i = 0; i < t->sum; i++) {
		out << t->x << ' ';
	}
	print(t->r, out);
}


inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		val[a]++;
	}
	calc_nval();
	for (int i = 1; i < MAXN; i++) {
		merge(root, root, new treap(i, val[i]));
		root->push_balance += val[i];
		merge(scnd, scnd, new treap(i, nval[i]));
		scnd->push_balance += nval[i];
	}
	// print(scnd, cerr);
	// cerr << '\n';
	for (int i = 0; i < m; i++) {
		char c;
		cin >> c;
		if (c == 't') {
			// cerr << "SWAP\n";
			// print(root, cerr);
			// cerr << '\n';
			// print(scnd, cerr);
			// cerr << '\n';
			swap(root, scnd);
		}
		if (c == 'c') {
			int a;
			cin >> a;
			treap *L = nullptr, *R = nullptr, *M = nullptr;
			split(root, L, R, a);
			split(R, M, R, 2);
			if (M != nullptr) {
				cout << M->sum << '\n';
			}
			merge(R, M, R);
			merge(root, L, R);
		}
		if (c == 'a') {
			int a;
			cin >> a;
			treap *L = nullptr, *R = nullptr, *M = nullptr;
			split(root, L, R, a);
			split(R, M, R, 2);
			int total = getsz(L) + 1;
			// print(L, cerr);
			// cerr << '\n';
			// print(M, cerr);
			// cerr << '\n';
			int pos = 0;
			if (M != nullptr) {
				pos = R->count_sum;
				M->sum++;
			}
			// cerr << total << ' ' << pos << '\n';
			merge(R, M, R);
			merge(root, L, R);
			split(scnd, L, R, pos);
			int need;
			need = total - (R == nullptr ? 0ll : R->count_sum);
			// cerr << need << '\n';
			if (pos != 0) {
				split(R, M, R, 2);
				// print(M, cerr);
				// cerr << '\n';
				// print(R, cerr);
				// cerr << '\n';
				// cerr << R->count_sum << '\n';
				// cerr << total << '\n';
				need = total - (R == nullptr ? 0ll : R->count_sum);
				if (M != nullptr) {
					M->sum -= need;
				}
			}
			if (R != nullptr) {
				R->push_x++;
			}
			treap *tmp;
			split(R, R, tmp, getsz(R));
			if (pos != 0) {
				treap *nxt = new treap(M->x + 1, need);
				merge(R, nxt, R);
				merge(L, L, M);
			}
			else {
				merge(R, new treap(1, need), R);
			}
			merge(scnd, L, R);
			// cerr << "! ";
			// print(root, cerr);
			// cerr << '\n';
			// print(scnd, cerr);
			// cerr << '\n';
		}
		if (c == 'r') {
			int a;
			cin >> a;
			treap *L = nullptr, *R = nullptr, *M = nullptr;
			split(root, L, R, a);
			int total = getsz(L) + 1;
			split(R, M, R, 2);
			// print(L, cerr);
			// cerr << '\n';
			// print(M, cerr);
			// cerr << '\n';
			// print(R, cerr);
			// cerr << '\n';
			int pos;
			bool ok = 0;
			if (M != nullptr) {
				pos = R->count_sum;
				if (M->sum != 0) {
					ok = 1;
					M->sum--;
				}
			}
			// cerr << pos << '\n';
			merge(R, M, R);
			merge(root, L, R);
			split(scnd, L, R, pos + 1);
			// print(L, cerr);
			// cerr << '\n';
			// print(R, cerr);
			// cerr << '\n';
			split(R, M, R, 2);
			if (ok) {
				treap *MM = nullptr;
				split(L, L, MM, getsz(L));
				if (MM != nullptr) {
					MM->sum += M->sum;
				}
				merge(L, L, MM);
				if (R != nullptr) {
					R->push_x--;
				}
				merge(R, R, new treap(MAXN - 1, 0));
			}
			else {
				merge(R, M, R);
			}
			merge(scnd, L, R);
			// cerr << "! ";
			// print(root, cerr);
			// cerr << '\n';
			// print(scnd, cerr);
			// cerr << '\n';
		}
	}
	print(root, cout);
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