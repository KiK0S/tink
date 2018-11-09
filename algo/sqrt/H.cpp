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

int K = 300;
int n, q;
vector<int> eul;
int tin[MAXN];
int tout[MAXN];
vector<pair<int, int>> g[MAXN];
int cnt[MAXN];
int val[MAXN];
int mod2[MAXN];
int sqr[MAXN];
int ans[MAXN];

struct Q{
	int l, r, id;
};

vector<Q> all;

void dfs(int v, int p = -1, int id = -1) {
	tin[v] = eul.size();
	eul.push_back(id);
	for (auto to : g[v]) {
		if (to.first == p) {
			continue;
		}
		dfs(to.first, v, to.second);
	}
	tout[v] = eul.size();
	eul.push_back(id);
}

void add(int x) {
	x = eul[x];
	if (x < 0) {
		return;
	}
	// cerr << "+ " << x << '\n';
	mod2[x]++;
	if (mod2[x] % 2 == 1) {
		if (val[x] < MAXN) {
			cnt[val[x]]++;
			if (cnt[val[x]] == 1) {
				sqr[val[x] / K]--;
			}
		}	
	}
	else {
		if (val[x] < MAXN) {
			cnt[val[x]]--;
			if (cnt[val[x]] == 0) {
				sqr[val[x] / K]++;
			}	
		}
	}
}

void del(int x) {
	x = eul[x];
	if (x < 0) {
		return;
	}
	// cerr << "- " << x << '\n';
	mod2[x]--;
	if (mod2[x] % 2 == 1) {
		if (val[x] < MAXN) {
			cnt[val[x]]++;
			if (cnt[val[x]] == 1) {
				sqr[val[x] / K]--;
			}
		}	
	}
	else {
		if (val[x] < MAXN) {
			cnt[val[x]]--;
			if (cnt[val[x]] == 0) {
				sqr[val[x] / K]++;
			}	
		}
	}
}

int query() {
	int cur = 0;
	for (;;) {
		if (sqr[cur / K] != 0) {
			while (cnt[cur] != 0) {
				cur++;
			}
			return cur;
		}
		cur += K;
	}
}

int mex(vector<int> &a) {
	sort(a.begin(), a.end());
	a.resize(unique(a.begin(), a.end()) - a.begin());
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != i) {
			return i;
		}
	}
	return a.size();
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n - 1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		val[i] = c;
		g[a].push_back({b, i});
		g[b].push_back({a, i});
	}
	for (int i = 0; i < n; i++) {
		sqr[i] = K;
	}
	dfs(0);
	// for (auto it : eul) {
	// 	cerr << it << ' ';
	// }
	// cerr << '\n';
	// for (int i = 0; i < n; i++) {
	// 	cerr << tin[i] << ' ' << tout[i] << '\n';
	// }
	// cerr << '\n';
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--; 
		// cerr << a << ' ' << b << '\n';
		if (a == b) {
			ans[i] = 0;
			continue;
		}
		if (tin[a] >= tin[b]) {
			swap(a, b);
		}
		int l, r;
		if (tout[a] >= tout[b]) {
			l = tin[a] + 1;
			r = tin[b];
		}
		else {
			l = tout[a];
			r = tin[b];
		}
		assert(l <= r);
		// cerr << l << ' ' << r << '\n';
		all.push_back({l, r, i});
	}
	sort(all.begin(), all.end(), [](Q a, Q b){
		return make_pair(a.l / K, a.r) < make_pair(b.l / K, b.r);
	});
	// for (auto it : all) {
	// 	memset(mod2, 0, sizeof(mod2));
	// 	vector<int> cur;
	// 	for (int i = it.l; i <= it.r; i++) {
	// 		if (eul[i] != -1) {
	// 			mod2[eul[i]]++;
	// 		}
	// 	}
	// 	for (int i = 0; i < n - 1; i++) {
	// 		if (mod2[i] == 1) {
	// 			cur.push_back(val[i]);
	// 		}
	// 	}
	// 	ans[it.id] = mex(cur);
	// }
	int l = 0, r = -1;
	for (auto it : all) {
		// cerr << it.l << ' ' << it.r << '\n';
		while (r < it.r) {
			r++;
			add(r);
		}
		while (r > it.r) {
			del(r);
			r--;
		}
		while (l < it.l) {
			del(l);
			l++;
		}
		while (l > it.l) {
			l--;
			add(l);
		}
		// for (int i = 0; i < n; i++) {
		// 	cerr << mod2[i] << ' ';
		// }
		// cerr << '\n';
		// for (int i = 0; i < n; i++) {
		// 	cerr << cnt[i] << ' ';
		// }
		// cerr << '\n';
		ans[it.id] = query();
	}
	for (int i = 0; i < q; i++) {
		cout << ans[i] << '\n';
	}
}

signed main() {
	#ifdef DEBUG
		freopen("H.in", "r", stdin);
		freopen("H.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> q)
		solve();
	return 0;
}