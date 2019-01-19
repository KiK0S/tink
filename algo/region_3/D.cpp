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
	const int MAXN = 1e5 + 100;
#endif

int n, m, s, k, t;

int dsu[MAXN];
int sum[MAXN];

inline int get(int x) {
	if (dsu[x] == x) {
		return x;
	}
	return get(dsu[x]);
}

inline int unite(int a, int b) {
	a = get(a);
	b = get(b);
	if (a == b) {
		return 0;
	}
	if (sum[a] > sum[b]) {
		swap(a, b);
	}
	dsu[a] = b;
	sum[b] += sum[a];
	return 1;
}

void check(int a, int b) {
	if (get(a) == get(b)) {
		int cnt = 0;
		vector<int> A, B;
		while (dsu[a] != a) {
			A.push_back(a);
			a = dsu[a];
			cnt++;
		}
		A.push_back(a);
		while (dsu[b] != b) {
			B.push_back(b);
			b = dsu[b];
			cnt++;
		}
		B.push_back(b);
		for (auto it : A) {
			cerr << it << ' ';
		}
		cerr << '\n';
		reverse(A.begin(), A.end());
		reverse(B.begin(), B.end());
		int pnt = 0;
		while (pnt < A.size() && pnt < B.size() && A[pnt] == B[pnt]) {
			cnt -= 2;
			pnt++;
		}
		cout << cnt << '\n';
		exit(0);
	}
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dsu[i] = i;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		unite(a, b);
	}
	int q;
	cin >> q;
	int _a, _b;
	if (q == 1) {
		cin >> _a >> _b;
		_a--, _b--;
		if (get(_a) == get(_b)) {
			cout << "0\n";
			return;
		}
	}
	while (clock() * 10 < 4 * CLOCKS_PER_SEC) {
		for (int a = 0; a < k; a++) {
			for (int b = a + 1; b < k; b++) {
				if (get(a) != get(b)) {
					continue;
				}
				for (int r = 1; r <= s; r++) {
					unite(r * k + a, r * k + b);
					if (q == 1) {
						check(_a, _b);
					}
				}
			}
		}
	}
	if (q == 1) {
		cout << "-1\n";
		return;
	}
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		if (get(a) == get(b)) {
			cout << "1\n";
		}
		else {
			cout << "-1\n";
		}
		// cout << get(a, b) - 1 << '\n';
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
	while (cin >> n >> k >> s >> m >> t)
		solve();
	return 0;
}