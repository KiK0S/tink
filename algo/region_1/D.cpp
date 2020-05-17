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
	const int MAXN = 1e3;
#else
	const int MAXN = 6e5 + 10;
#endif

int n, m;
string val[MAXN];
int tpow[10];

string a, b;

inline ll get(int a_pnt, int b_pnt, int tp) {
	if (a_pnt == a.size()) {
		return 0;
	}
	if (a[a_pnt] != '?') {
		if (a[a_pnt] < b[b_pnt]) {
			return tpow[tp];
		}
		if (a[a_pnt] == b[b_pnt]) {
			if (a_pnt + 1 == a.size()) {
				return 1;
			}
			return get(a_pnt + 1, b_pnt + 1, tp);
		}
		else {
			return 0;
		}
	}
	if (a_pnt + 1 == a.size()) {
		return b[b_pnt] - '0' + 1;
	}
	ll kek = b[b_pnt] - '0';
	return kek * tpow[tp - 1] + get(a_pnt + 1, b_pnt + 1, tp - 1);
}

struct node {
	vector<int> term;
	int go[10];
	node () {
		memset(go, -1, sizeof(go));
	}
};

node g[MAXN];
int pnt = 1;
string s;

inline void add(int s_pnt, int v, int id) {
	g[v].term.push_back(id);
	if (s_pnt == s.size()) {
		return;
	}
	if (g[v].go[s[s_pnt] - '0'] == -1) {
		g[v].go[s[s_pnt] - '0'] = pnt++;
	}
	// pref.push_back(s[0]);
	add(s_pnt + 1, g[v].go[s[s_pnt] - '0'], id);
}

const int K = 10;


inline ll dfs(int s_pnt, int v, int tp) {
	if (v == -1 || s_pnt == s.size()) {
		return 0;	
	}
	if (s[s_pnt] != '?') {
		ll also = 0;
		for (int i = (s.size() - s_pnt > 1 ? s[s_pnt] - '0' + 1 : s[s_pnt] - '0'); i <= 9; i++) {
			if (g[v].go[i] != -1) {
				also += g[g[v].go[i]].term.size();
			}
		}
		return also * tpow[tp] + dfs(s_pnt + 1, g[v].go[s[s_pnt] - '0'], tp);
	}
	if (g[v].term.size() < K || s_pnt + 1 == s.size()) {
		ll ans = 0;
		for (auto it : g[v].term) {
			a = s;
			b = val[it];
			ans += get(s_pnt, s_pnt, tp);
		}
		return ans;
	}
	ll res = 0;
	ll cur = 0;
	for (int i = 0; i < 10; i++) {
		if (g[v].go[i] != -1) {
			cur += i * g[g[v].go[i]].term.size();
		}
	}
	res += cur * tpow[tp - 1];
	for (int i = 0; i < 10; i++) {
		res += dfs(s_pnt + 1, g[v].go[i], tp - 1);
	}
	return res;
}

inline void init() {
	for (int i = 0; i < n; i++) {
		cin >> val[i]; 
		reverse(val[i].begin(), val[i].end());
		while (val[i].size() < 9) {
			val[i].push_back('0');
		}
		reverse(val[i].begin(), val[i].end());
		s = val[i];
		add(0, 0, i);
	}
	tpow[0] = 1;
	for (int i = 1; i < 10; i++) {
		tpow[i] = 10 * tpow[i - 1];
	}
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		cin >> s;
		reverse(s.begin(), s.end());
		while (s.size() < 9) {
			s.push_back('0');
		}
		reverse(s.begin(), s.end());
		int cnt = 0;
		for (auto c : s) {
			if (c == '?') {
				cnt++;
			}
		}
		cout << dfs(0, 0, cnt) << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}