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

const int MAXN = 2e5;

int K = 3000;
int n, m;
int val[MAXN];
int ans[MAXN];
int sqr[MAXN];
int cnt[MAXN];
int countsort[MAXN];
vector<int> coord;

struct Q {
	int l, r, t, id;
	Q() {}
	Q(int _l, int _r, int _t, int  _id) {
		l = _l, r = _r, t = _t, id = _id;
	}
};

struct U {
	int pre, nxt, pos;
	U() {}
	U(int c, int a, int b) {
		pos = c, pre = a, nxt = b;
	}
};

vector<U> upd;

void add(int pos) {
	cnt[countsort[pos]]--;
	if (cnt[countsort[pos]] == 0) {
		sqr[(cnt[countsort[pos]]) / 300]++;
	}
	countsort[pos]++;
	cnt[countsort[pos]]++;
	if (cnt[countsort[pos]] == 1) {
		sqr[(cnt[countsort[pos]]) / 300]--;
	}
}

void del(int pos) {
	cnt[countsort[pos]]--;
	if (cnt[countsort[pos]] == 0) {
		sqr[(cnt[countsort[pos]]) / 300]++;
	}
	countsort[pos]--;
	cnt[countsort[pos]]++;
	if (cnt[countsort[pos]] == 1) {
		sqr[(cnt[countsort[pos]]) / 300]--;
	}
}

int query() {
	// for (int i = 0; i < coord.size(); i++) {
	// 	cerr << coord[i] << ' ' << cnt[i] << ' ' << countsort[i] << '\n';
	// }
	int cur = 0;
	for (;;) {
		if (sqr[cur / 300] != 300) {
			while (cnt[cur] != 0) {
				cur++;
			}
			return cur;
		}
		cur += 300;
	}
}

int getid(int x) {
	return lower_bound(coord.begin(), coord.end(), x) - coord.begin();
}

inline void solve() {
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		coord.push_back(val[i]);
		// coord.push_back(val[i] + 1);
		// coord.push_back(i);
	}
	// coord.push_back(n);
	// coord.push_back(n + 1);
	vector<Q> all;
	for (int i = 0; i < m; i++) {
		int t, a, b;
		cin >> t >> a >> b;
		ans[i] = -1;
		if (t == 1) {
			all.emplace_back(a - 1, b - 1, upd.size() - 1, i);
		}
		else {
			coord.push_back(b);
			// coord.push_back(b + 1);
			upd.emplace_back(a - 1, val[a - 1], b);
			val[a - 1] = b;
		}
	}
	sort(coord.begin(), coord.end());
	coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
	for (int i = 0; i < coord.size(); i++) {
		sqr[i] = 300;
		cnt[i] = 0;
	}
	cnt[0] = 1e9;
	sort(all.begin(), all.end(), [&](Q a, Q b){
		return make_tuple(a.l / K, a.t / K, a.r) < make_tuple(b.l / K, b.t / K, b.r);
	});
	for (auto &it : upd) {
		it.nxt = getid(it.nxt);
		it.pre = getid(it.pre);
	}
	for (int i = 0; i < n; i++) {
		val[i] = getid(val[i]);
	}
	int l = 0;
	int r = -1;
	int t = upd.size() - 1;
	for (auto it : all) {
		while (t < it.t) {
			t++;
			if (upd[t].pos >= l && upd[t].pos <= r) {
				del(upd[t].pre);
			}
			val[upd[t].pos] = upd[t].nxt;
			if (upd[t].pos >= l && upd[t].pos <= r) {
				add(upd[t].nxt);
			}
		}
		while (t > it.t) {
			if (upd[t].pos >= l && upd[t].pos <= r) {
				del(upd[t].nxt);
			}
			val[upd[t].pos] = upd[t].pre;
			if (upd[t].pos >= l && upd[t].pos <= r) {
				add(upd[t].pre);
			}
			t--;
		}
		while (r < it.r) {
			r++;
			add(val[r]);
		}
		while (r > it.r) {
			del(val[r]);
			r--;
		}
		while (l < it.l) {
			del(val[l]);
			l++;
		}
		while (l > it.l) {
			l--;
			add(val[l]);
		}
		// cerr << l << ' ' << r << ' ' << t << '\n';
		ans[it.id] = query();
	}
	for (int i = 0; i < m; i++) {
		if (ans[i] != -1) {
			cout << ans[i] << '\n';
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}