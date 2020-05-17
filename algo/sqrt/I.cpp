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

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 2e5 + 10;
#endif
#define int ll

int K = 450;
int INF = 1e18;
int n, m, l;

struct block {
	vector<int> dots;
	vector<int> nxt;
	vector<int> cnt;
	int l, r, sz;
};

vector<block> q;
int val[MAXN];

void rebuild(block &bl, int ind) {
	bl.sz = bl.dots.size();
	if (bl.sz == 0) {
		return;
	}
	bl.l = bl.dots[0];
	bl.r = bl.dots.back();
	if (ind == 0) {
		bl.l = -INF;
	}
	if (ind == q.size() - 1) {
		bl.r = INF;
	}
	int pnt = bl.sz;
	bl.nxt.resize(bl.sz);
	bl.cnt.resize(bl.sz);
	// cerr << '\n';
	// for (auto it : bl.dots) {
	// 	cerr << it << ' ';
	// }
	// cerr << '\n';
	for (int i = bl.sz - 1; i >= 0; i--) {
		while (pnt > 0 && bl.dots[pnt - 1] > bl.dots[i] + l) {
			pnt--;
		}
		if (pnt == bl.sz) {
			bl.nxt[i] = bl.dots[i] + l + 1;
			bl.cnt[i] = 1;
		}
		else {
			bl.nxt[i] = bl.nxt[pnt];
			bl.cnt[i] = bl.cnt[pnt] + 1;
		}
	}
	// cerr << '\n';
	// for (auto it : bl.nxt) {
	// 	cerr << it << ' ';
	// }
	// cerr << '\n';
}

void build() {
	vector<int> sorted(n);
	for (int i = 0; i < n; i++) {
		sorted[i] = val[i];
	}
	sort(sorted.begin(), sorted.end());
	q.clear();
	for (int i = 0; i < n; i++) {
		if (i % K == 0) {
			q.push_back(block());
		}
		q.back().dots.push_back(sorted[i]);
	}
	for (int i = 0; i < q.size(); i++) {
		rebuild(q[i], i);
	}
}

void upd(int from, int to) {
	// cerr << from << ' ' << to << '\n';
	int cnt = 0;
	for (auto &it : q) {
		if (it.sz != 0 && from <= it.r) {
			it.dots.erase(find(it.dots.begin(), it.dots.end(), from));
			rebuild(it, cnt);
			break;
		}
		cnt++;
	}
	cnt = 0;
	for (auto &it : q) {
		if (it.sz != 0 && to <= it.r) {
			it.dots.push_back(to);
			int pnt = it.dots.size() - 1;
			while (pnt && it.dots[pnt] < it.dots[pnt - 1]) {
				swap(it.dots[pnt], it.dots[pnt - 1]);
				pnt--;
			}
			rebuild(it, cnt);
			break;
		}
		cnt++;
	}
}

int get() {
	int ans = 0;
	int pnt = 0;
	while (pnt < q.size() && q[pnt].sz == 0) {
		pnt++;
	}
	int cur = q[pnt].l;
	while (1) {
		// cerr << cur << ' ';
		while (pnt < q.size() && (q[pnt].sz == 0 || q[pnt].dots.back() < cur)) {
			// cerr << "! " << q[pnt].dots.back() << ' ';
			pnt++;
		}
		if (pnt == q.size()) {
			break;
		}
		int pos = lower_bound(q[pnt].dots.begin(), q[pnt].dots.end(), cur) - q[pnt].dots.begin();
		// cerr << pnt << ' ' << pos << ' ';
		// cerr << '\n';
		// if (cur > 0) {
		// 	break;
		// }
		ans += q[pnt].cnt[pos];
		cur = q[pnt].nxt[pos];
	}
	// cerr << '\n';
	return ans;
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	int c = 0;
	for (int i = 0; i < m; i++) {
		if (i % K == 0) {
			build();
		}
		// cerr << i << '\n';
		int a, b;
		cin >> a >> b;
		a += c;
		a %= n;
		upd(val[a], b);
		// cerr << i << '\n';
		val[a] = b;
		cout << (c = get()) << ' ';
		// cout.flush();ч	
		// cerr << i << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("I.in", "r", stdin);
		freopen("I.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> l) {
		solve();
	}
	return 0;
}