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
#include <complex>
using namespace std;

typedef long long ll;

// #ifdef DEBUG
// 	const int MAXN = 10;
// #else
	const int MAXN = 1e5;
// #endif

int n, m;

struct Q {
	int l, r, id;
	Q() {}
	Q(int a, int b, int c) {
		l = a, r = b, id = c;
	}
};

const int K = 400;
const int INF = 2e9;

int ans[(int)2e5 + 10];
int mx[MAXN];
int sqr[MAXN];
int pref[MAXN];
int suf[MAXN];
int q_p[MAXN];
int q_s[MAXN];
int q_f[MAXN];
int block[MAXN / K + 1][K];

void add(Q q) {
	// cerr << "add\n";
	int x = q.r;
	int pos = q.id;
	mx[pos] = x;
	sqr[pos / K] = INF;
	int L = pos / K * K;
	int R = L + K - 1; //min(L + K - 1, n);
	for (int i = L; i <= R; i++) {
		sqr[i / K] = min(sqr[i / K], mx[i]);
		pref[i] = min((i == L ? INF : pref[i - 1]), mx[i]);
	}
	for (int i = R; i >= L; i--) {
		suf[i] = min((i == R ? INF : suf[i + 1]), mx[i]);
	}
	int l = pos - 1;
	int r = pos + 1;
	int cur = mx[pos];
	for (int len = 1; len < K; len++) {
		block[L / K][len] = max(block[L / K][len], cur);
		if (r > R) {
			cur = min(cur, mx[l]);
			l--;
		}
		else if (l < L) {
			cur = min(cur, mx[r]);
			r++;
		}
		else {
			if (mx[r] < mx[l]) {
				cur = min(cur, mx[l]);
				l--;
			}
			else {
				cur = min(cur, mx[r]);
				r++;
			}
		}
	}
	// for (int i = 0; i < n; i++) {
	// 	cerr << mx[i] << ' ';
	// }
	// cerr << '\n';
}

int query(Q q) {
	// cerr << "get\n";
	int x = q.l;
	for (int i = 0; i < n / K + 1; i++) {
		int l = 0;
		int r = K;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (pref[i * K + mid - 1] >= x) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		q_s[i] = l;
		// cerr << q_s[i] << ' ';
	}
	// cerr << '\n';
	for (int i = 0; i < n / K + 1; i++) {
		int l = 0;
		int r = K;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (suf[i * K + K - mid] >= x) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		q_p[i] = l;
		// cerr << q_p[i] << ' ';
	}
	// cerr << '\n';
	for (int i = 0; i < n / K + 1; i++) {
		q_f[i] = 0;
		if (sqr[i] >= x) {
			q_f[i] = K;
		}
		// cerr << q_f[i] << ' ';
	}
	// cerr << '\n';
	int ans = 0;
	int cur = 0;
	for (int i = 0; i < n / K + 1; i++) {
		ans = max(ans, cur + q_s[i]);
		if (q_f[i] == 0) {
			cur = q_p[i];
		}
		cur += q_f[i];
	}
	ans = max(ans, cur);
	for (int i = 0; i < n / K + 1; i++) {
		int l = 0;
		int r = K;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (block[i][mid] >= x) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		ans = max(ans, l);
	}
	// cerr << ans << '\n';
	return ans;
}

void init() {
	for (int i = 0; i < MAXN; i++) {
		mx[i] = -INF;	
	}
	for (int i = 0; i < MAXN / K + 1; i++) {
		for (int j = 0; j < K; j++) {
			block[i][j] = -INF;
		}
	}
}

inline void solve() {
	init();
	vector<Q> q;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		q.emplace_back(a, b, i);
	}
	vector<Q> g;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g.emplace_back(a, b, i);
	}
	sort(q.begin(), q.end(), [](Q a, Q b){
		return a.l < b.l;
	});
	sort(g.begin(), g.end(), [](Q a, Q b){
		return a.r < b.r;
	});
	int pnt1 = 0;
	int pnt2 = 0;
	for (int i = 0; i < n + m; i++) {
		if (pnt1 < q.size() && (pnt2 == g.size() || (g[pnt2].r >= q[pnt1].l))) {
			add(q[pnt1++]);
		}
		else {
			ans[g[pnt2].id] = query(g[pnt2]);
			pnt2++;
		}
	}
	for (int i = 0; i < m; i++) {
		cout << ans[i] << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}