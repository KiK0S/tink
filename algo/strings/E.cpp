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
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 1000;
#else
	const int MAXN = 6e5 + 100;
#endif

int n;
int t = 31;
int mod = 1e9 + 9;
string s;
int h[MAXN];
int dp[MAXN];
int tpow[MAXN];
int val[MAXN];
ull hll[MAXN];
ull tpowll[MAXN];
int len[MAXN];
int used[MAXN];
int sum[MAXN];
// string T[MAXN];
unordered_map<ull, int> vertex;
unordered_map<ull, int> vertexll;
vector<int> g[MAXN];

int get_len(int l, int r) {
	if (s[l] == 'a' + 26) {
		return (r - l + 1) / 2;
	}
	return (r - l + 2) / 2;
}

int pnt = 0;
int make_v(int H, ull Hll, int l, int r) {
	Hll *= H;
	if (vertex.count(Hll)) {
		return vertex[Hll];
	}
	vertex[Hll] = pnt++;
	// vertex[Hll] = pnt - 1;
	len[pnt - 1] = get_len(l, r);
	// T[pnt - 1] = s.substr(l, r - l + 1);
	return pnt - 1;
}

int get_hash(int l, int r) {
	if (l == 0) {
		return h[r];
	}
	int ret = h[r] - (1ll * h[l - 1] * tpow[r - l + 1]) % mod;
	ret += mod;
	ret %= mod;
	return ret;//, h[r].second - h[l - 1].second * tpow[r - l + 1].second};
}

ull get_hashll(int l, int r) {
	if (l == 0) {
		return hll[r];
	}
	ull ret = hll[r] - (hll[l - 1] * tpowll[r - l + 1]);
	return ret;//, h[r].second - h[l - 1].second * tpow[r - l + 1].second};
}

ll ans = 0;

void dfs(int v, int _t = 0) {
	used[v] = 1;
	for (auto to : g[v]) {
		if (used[to]) {
			continue;
		}
		dfs(to, _t + 1);
		sum[v] += sum[to];
	}
	// for (int i = 0; i < _t; i++) {
	// 	cerr << '\t';
	// }
	// cerr << T[v] << '\n';
	// cerr << len[v] << ' ' << sum[v] << '\n';
	if (v != 27) {
		ans = max(ans, 1ll * len[v] * sum[v]);
	}
}

inline void init() {
	// assert(s.size() < 3e5);
	string ns(2 * s.size() + 1, 'a');
	for (int i = 0; i < s.size(); i++) {
		ns[2 * i] = 'a' + 26;
		ns[2 * i + 1] = s[i];
	}
	ns[2 * s.size()] = 'a' + 26;
	// for (auto c : s) {
	// 	ns.push_back('a' + 26);
	// 	ns.push_back(c);
	// }
	// ns.push_back('a' + 26);
	s.swap(ns);
	n = s.size();
	tpow[0] = 1;
	tpowll[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		tpow[i] = (1ll * tpow[i - 1] * t) % mod;
		tpowll[i] = tpowll[i - 1] * t;
	}
	for (int i = 0; i < n; i++) {
		h[i] = ((1ll * (i == 0 ? 0 : h[i - 1]) * t) % mod + s[i] - 'a' + 1) % mod;
		hll[i] = (i == 0 ? 0 : hll[i - 1]) * t + s[i] - 'a' + 1;
	}
}


inline void solve() {
	init();
	int l = 0;
	int r = -1;
	make_v(0, 0, 0, 0);
	for (int i = 1; i <= 27; i++) {
		vertex[i * i] = pnt++;
		// vertexll[i] = pnt - 1;
		len[pnt - 1] = 1;
		g[0].push_back(pnt - 1);
	}
	for (int i = 0; i < n; i++) {
		int k = (i > r ? 0 : min(dp[l + r - i], r - i));
		int lastv = make_v(get_hash(i - k, i + k), get_hashll(i - k, i + k), i - k, i + k);
		while (i + k + 1 < n && i - k - 1 >= 0 && s[i + k + 1] == s[i - k - 1]) {
			int p1 = pnt;
			int hn = make_v(get_hash(i - k - 1, i + k + 1), get_hashll(i - k - 1, i + k + 1), i - k - 1, i + k + 1);
			int p2 = pnt;
			if (p1 != p2) {
				g[lastv].push_back(hn);
			}
			lastv = hn;
			k++;
		}
		dp[i] = k;
		sum[lastv]++;
		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}
	// cerr << s << '\n';
	// for (int i = 0; i < n; i++) {
	// 	cerr << dp[i] << ' ';
	// }
	// cerr << '\n';
	dfs(0);
	cout << ans << '\n';
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
	while (cin >> s)
		solve();
	return 0;
}