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
	const int MAXN = 3e5;
#endif

#define int ll

int n;
int INF = 1e9 + 1;

struct node {
	node *l = nullptr, *r = nullptr;
	int x, dist;
	node(){}
	node(int a) {
		x = a;
	}
};

int get_dist(node *t) {
	return t == nullptr ? 0 : t->dist;
}

int get_x(node *t) {
	return t == nullptr ? INF : t->x;
}

node * merge(node *a, node *b) {
	if (a == nullptr && b == nullptr) {
		return nullptr;
	}
	if (b == nullptr) {
		node * nw = new node();
		nw->dist = get_dist(a);
		nw->x = get_x(a);
		nw->l = a->l;
		nw->r = a->r;
		return nw;
	}
	if (a == nullptr) {
		node * nw = new node();
		nw->dist = get_dist(b);
		nw->x = get_x(b);
		nw->l = b->l;
		nw->r = b->r;
		return nw;
	}
	if (get_x(a) > get_x(b)) {
		node *tmp = a;
		a = b;
		b = tmp;
	}
	node *nw = new node();
	nw->x = a->x;
	nw->l = a->l;
	nw->r = merge(a->r, b);
	if (get_dist(nw->r) > get_dist(nw->l)) {
		node *tmp = nw->l;
		nw->l = nw->r;
		nw->r = tmp;
	}
	nw->dist = get_dist(nw->r) + 1;
	return nw;
}

node *roots[MAXN];

inline void init() {

}

inline void solve() {
	init();
	int s = 0;
	roots[0] = nullptr;
	for (int i = 1; i <= n; i++) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int a, b;
			cin >> a >> b;
			int v = (a + s) % i;
			int x = (b + 17 * s) % INF;
			// cerr << "add " << v << ' ' << x << '\n';
			roots[i] = merge(roots[v], new node(x));
			if (roots[i] != nullptr) {
				int x = get_x(roots[i]);
				cout << x << '\n';
				s = (s + x) % 239017;
			}
			else {
				cout << "empty\n";
			}
		}
		if (tp == 2) {
			int a, b;
			cin >> a >> b;
			int v = (a + s) % i;
			int u = (b + 13 * s) % i;
			// cerr << "merge " << v << ' ' << u << '\n';
			roots[i] = merge(roots[v], roots[u]);
			if (roots[i] != nullptr) {
				int x = get_x(roots[i]);
				cout << x << '\n';
				s = (s + x) % 239017;
			}
			else {
				cout << "empty\n";
			}
		}
		if (tp == 3) {
			int a;
			cin >> a;
			int v = (a + s) % i;
			// cerr << "erase " << v << '\n';
			if (roots[v] != nullptr) {
				roots[i] = merge(roots[v]->l, roots[v]->r);
				int x = get_x(roots[v]);
				cout << x << '\n';
				s = (s + x) % 239017;
			}
			else {
				cout << "empty\n";
			}
		}
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