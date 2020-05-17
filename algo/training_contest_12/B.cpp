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
	const int MAXN = 2e6;
#endif

#define int ll
int n;
int MOD = 1e9 + 7;
int pw[MAXN];
int sm[MAXN];

struct node {
	node *l = nullptr;
	node *r = nullptr;
	int x;
};

node *ptr[MAXN];

inline void init() {
}

void add(node *v) {
	if (v->l == nullptr) {
		v->l = new node();
		v->l->x = v->x * 2;
		ptr[v->l->x] = v->l;
	}
	else {
		add(v->l);
	}
	if (v->r == nullptr) {
		v->r = new node();
		v->r->x = v->x * 2 + 1;
		ptr[v->r->x] = v->r;
	}
	else {
		add(v->r);
	}
}

int get(node *v) {
	if (v == nullptr) {
		return 0;
	}
	return (v->x + get(v->l) + get(v->r)) % MOD;
}

inline void solve() {
	init();
	ptr[1] = new node();
	ptr[1]->x = 1;
	for (int i = 0; i < n; i++) {
		string s;
		int a;
		cin >> s >> a;
		if (s == "Grow") {
			add(ptr[a]);
		}
		else {
			cout << get(ptr[a]) << '\n';
		}
	}	
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}