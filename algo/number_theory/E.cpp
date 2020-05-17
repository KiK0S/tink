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
	const int MAXN = 1e5;
#else
	const int MAXN = 1e5;
#endif

#define int ll

int n, k;

int phi[MAXN];
int f[MAXN];
int g[MAXN];
int lp[MAXN];
vector<int> p;
int MOD = 1e8 + 7;

void erat() {
	for (int i = 2; i < MAXN; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			p.push_back(i);
		}
		for (int j = 0; j < p.size() && p[j] <= lp[i] && i * p[j] < MAXN; j++) {
			lp[i * p[j]] = p[j];
		}
	}
}

int F(int x) {
	if (x < MAXN) {
		return f[x];
	}
	int q = x;
	int res = x;
	for (int i = 2; i * i <= x; i++) {
		int cnt = 0;
		while (q % i == 0) {
			q /= i;
			cnt++;
		}
		if (cnt != 0) {
			res -= res / i;
		}
	}
	if (q != 1) {
		res -= res / q;
	}
	return res;
}

void gen(vector<pair<int, int>> &all, int &res, int pos, int cur) {
	if (pos == all.size()) {
		res += F(cur);
		return;
	}
	for (int i = 0; i <= all[pos].second; i++) {
		gen(all, res, pos + 1, cur);
		cur *= all[pos].first;
	}
}

int G(int x) {
	if (x < MAXN) {
		return g[x];
	}
	int cur = 0;
	vector<pair<int, int>> all;
	int q = x;
	for (int i = 2; i * i <= x; i++) {
		if (q % i == 0) {
			all.push_back({i, 0});
		}
		while (q % i == 0) {
			all.back().second++;
			q /= i;
		}
	}
	if (q != 1) {
		all.push_back({q, 1});
	}
	gen(all, cur, 0, 1);
	return cur;
}

void calc_phi() {
	f[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		int cur = i;
		phi[i] = i;
		int last = -1;
		int cnt = 0;
		while (cur > 1) {
			int nxt = lp[cur];
			if (nxt == last) {
				cnt++;
			}
			else {
				phi[i] -= phi[i] / nxt;
				cnt = 1;
				last = nxt;
			}
			cur /= nxt;
		}
		if (cur != 1)
			phi[i] -= phi[i] / cur;
		f[i] = phi[i];
	}
}

void calc_g() {
	for (int i = 1; i < MAXN; i++) {
		g[i] = 1;
	}
	for (int i = 2; i < MAXN; i++) {
		for (int j = 1; i * j < MAXN; j++) {
			g[i * j] += f[i];
		}
	}
}

inline void init() {
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));
	memset(lp, 0, sizeof(lp));
}

inline void solve() {
	init();
	erat();
	calc_phi();	
	calc_g();
	int cur = F(G(n));
	for (int i = 0; i < k - 1; i++) {
		if (i & 1) {
			cur = F(cur);
		}
		else {
			cur = G(cur);
		}
		if (cur == 1) {
			break;
		}
	}
	cout << cur % MOD << '\n';
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
	while (cin >> n >> k)
		solve();
	return 0;
}