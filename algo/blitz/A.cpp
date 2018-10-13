#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 5;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
#endif

#define int long long

int n, m;
int val[MAXN];
int sparse[MAXN][MAXLOG];
int precalc[MAXN];

void build() {
	precalc[1] = 0;
	for (int i = 2; i < MAXN; i++) {
		precalc[i] = precalc[i >> 1] + 1;
	}
	for (int i = 0; i < MAXN; i++) {
		sparse[i][0] = val[i];
	}
	for (int i = 1; i < MAXLOG; i++) {
		for (int j = 0; j < MAXN; j++) {
			if (j + (1 << (i - 1)) < MAXN) {
				sparse[j][i] = max(sparse[j][i - 1], sparse[j + (1 << (i - 1))][i - 1]);
			}
		}
	}
}

int get(int l, int r) {
	int lg = precalc[r - l + 1];
	return max(sparse[l][lg], sparse[r - (1 << lg) + 1][lg]);
}

void solve() {
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	build();
	cin >> m;
	int l1, r1;
	cin >> l1 >> r1;
	int pre = 0;
	int ans = 0;
	for (int i = 0; i < m; i++) {
		pre = get(l1, r1);
		ans += pre;
		int A = min(r1, (l1 * pre + pre * pre) % n);
		int B = max(r1, (l1 * pre + pre * pre) % n);
		l1 = A;
		r1 = B;
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG 
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
		freopen("mushrooms.in", "r", stdin);
		freopen("mushrooms.out", "w", stdout);	
	#endif
	while (cin >> n) {
		solve();
	}
	return 0;
}