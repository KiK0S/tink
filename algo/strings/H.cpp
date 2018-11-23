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
	const int MAXN = 20;
#else
	const int MAXN = 2e6 + 10;
#endif

const int MAXLOG = 24;

int n;

struct node {
	int to[26];
	int p;
	int mx;
	int sum;
	int pch;
	int link;
	int glink;
	int term;
};

node t[MAXN];
vector<int> g[MAXN];
int tin[MAXN];
int f[MAXN];
int sz = 0;

int make(int p = 0, int pc = 0) {
	memset(t[sz].to, -1, sizeof(t[sz].to));
	t[sz].p = p;
	t[sz].pch = pc;
	t[sz].link = -1;
	t[sz].glink = -1;
	t[sz].sum = 0;
	t[sz].mx = -1;
	t[sz].term = 0;
	return sz++;
}

int add(string s) {
	int v = 0;
	for (int i = 0; i < s.size(); i++) {
		if (t[v].to[s[i] - 'a'] == -1) {
			t[v].to[s[i] - 'a'] = make(v, s[i] - 'a');
		}
		v = t[v].to[s[i] - 'a'];
	}
	t[v].term = 1;
	return v;
}

void bfs() {
	queue<int> q;
	// queue<string> tmp;
	// tmp.push("");
	q.push(0);
	while (!q.empty()) {
		int v = q.front();
		// string cur = tmp.front();
		q.pop();
		// tmp.pop();
		// cerr << v << ' ' << cur << '\n';
		if (t[v].p == 0) {
			t[v].link = 0;
		}
		else {
			t[v].link = t[t[t[v].p].link].to[t[v].pch];
		}
		if (t[v].term != 0) {
			t[v].glink = v;
		}
		else {
			if (v == 0) {
				t[v].glink = 0;
			}
			else {
				t[v].glink = t[t[v].link].glink;
			}
		}
		// cerr << "link " << t[v].link << '\n';
		// cerr << "parent " << t[v].p << ' ' << t[v].pch << '\n';
		if (v != 0) {	
			g[t[v].link].push_back(v);
		}
		for (int i = 0; i < 26; i++) {
			if (t[v].to[i] != -1) {
				q.push(t[v].to[i]);
				// cur.push_back('a' + i);
				// tmp.push(cur);
				// cur.pop_back();
			}
			else {
				if (v == 0) {
					t[v].to[i] = 0;
				}
				else {
					t[v].to[i] = t[t[v].link].to[i];
				}
			}
			// cerr << t[v].to[i] << ' ';
		}
		// cerr << '\n';
	}
	// cerr << '\n';
}

int parent[MAXN][MAXLOG];
int siz[MAXN];
int rev[MAXN];
int timer = 0;

void dfs(int v, int p = 0) {
	siz[v] = 1;
	rev[timer] = v;
	tin[v] = timer++;
	parent[v][0] = p;
	for (int i = 1; i < MAXLOG; i++) {
		parent[v][i] = parent[parent[v][i - 1]][i - 1];
	}
	for (auto to : g[v]) {
		dfs(to, v);
		siz[v] += siz[to];
	}
}

int isp(int v, int u) {
	return tin[v] <= tin[u] && tin[v] + siz[v] - 1 >= tin[u];
}

int lca(int v, int u) {
	if (isp(v, u)) {
		return v;
	}
	if (isp(u, v)) {
		return u;
	}
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!isp(parent[v][i], u)) {
			v = parent[v][i];
		}
	}
	return parent[v][0];
}

void add(int id, int x) {
	for (int i = id + 1; i < MAXN; i += i & -i) {
		f[i] += x;
	}
}

int get(int id) {
	int cur = 0;
	for (int i = id + 1; i > 0; i -= i & -i) {
		cur += f[i];
	}
	return cur;
}

inline void init() {

}

int sv[MAXN];

inline void solve() {
	init();
	make();
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		sv[i] = add(s);
	}
	bfs();
	dfs(0);
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		// cerr << "query " << i << '\n';
		int type;
		cin >> type;
		if (type == 1) {
			string s;
			cin >> s;
			int v = 0;
			vector<int> row;
			for (auto c : s) {
				v = t[v].to[c - 'a'];
				add(tin[v], 1);
				row.push_back(tin[v]);
			}
			sort(row.begin(), row.end());
			for (int i = 1; i < row.size(); i++) {
				add(tin[lca(rev[row[i]], rev[row[i - 1]])], -1);
			}
		}
		else {
			int x;
			cin >> x;
			x--;
			// cerr << sv[x] << '\n';
			cout << get(tin[sv[x]] + siz[sv[x]] - 1) - get(tin[sv[x]] - 1) << '\n';
		}
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
	while (cin >> n)
		solve();
	return 0;
}