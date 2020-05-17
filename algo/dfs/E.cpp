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
	const int MAXN = 30;
#else
	const int MAXN = 5e5;
#endif

int n, m;

struct edge {
	int from, to, c, x;
};

vector<int> g[MAXN];
edge e[MAXN];
int ue[MAXN];
int pnt = 0;
vector<int> eul;
int used[MAXN];

void dfs(int v) {
	used[v] = 1;
	while (g[v].size()) {
		int cur = g[v].back();
		g[v].pop_back();
		if (ue[cur]) {
			continue;
		}
		ue[cur] = 1;
		if (e[cur].from == v) {
			dfs(e[cur].to);
		}
		else {
			dfs(e[cur].from);
		}
		eul.push_back(cur);
	}
}

vector<vector<int>> ans;

void process(vector<int> res) {
	if (res.empty()) {
		return;
	}
	ans.push_back(vector<int>());
	if (res.size() == 1) {
		ans.back().push_back(e[res[0]].from);
		ans.back().push_back(e[res[0]].to);
	}
	else {
		{
			int lst;
			lst = e[res[0]].from;
			ans.back().push_back(lst);
			for (auto x : res) {
				int nxt = e[x].x ^ lst;
				if (e[x].to != nxt && e[x].from != nxt) {
					ans.back().clear();
					break;
				}
				ans.back().push_back(nxt);
				lst = nxt;
			}
		}
		if (ans.back().empty()) {
			int lst;
			lst = e[res[0]].to;
			ans.back().push_back(lst);
			for (auto x : res) {
				int nxt = e[x].x ^ lst;
				if (e[x].to != nxt && e[x].from != nxt) {
					ans.back().clear();
					break;
				}
				ans.back().push_back(nxt);
				lst = nxt;
			}
		}
	}
}

void calc() {
	reverse(eul.begin(), eul.end());
	bool f = 0;
	for (auto it : eul) {
		if (e[it].c == 1) {
			f = 1;
			break;
		}
	}
	if (!f) {
		return;
	}
	int lft = 0;
	for (int i = 0; i < eul.size(); i++) {
		if (e[eul[i]].c == -1) {
			lft = i;
			break;
		}
	}
	vector<int> cur;
	for (int i = lft; ; i = (i + 1) % eul.size()) {
		if (e[eul[i]].c == -1) {
			process(cur);
			cur.clear();
			continue;
		}
		cur.push_back(eul[i]);
		if ((i + 1) % eul.size() == lft) {
			break;
		}
	}
	process(cur);
}

void init() {
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		e[pnt] = (edge) {a, b, c, a ^ b};
		g[a].push_back(pnt);
		g[b].push_back(pnt);
		pnt++;
		if (c == 0) {
			e[pnt] = (edge) {a, b, c, a ^ b};
			g[a].push_back(pnt);
			g[b].push_back(pnt);
			pnt++;
		}
	}
}



inline void solve() {
	init();
	int last = -1;
	for (int i = 0; i < n; i++) {
		if (g[i].size() & 1) {
			if (last == -1) {
				last = i;
			}
			else {
				e[pnt] = (edge) {last, i, -1, last ^ i};
				g[i].push_back(pnt);
				g[last].push_back(pnt);
				pnt++;
				last = -1;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i);
			calc();
			eul.clear();
		}
	}
	cout << ans.size() << '\n';
	// assert(ans.size());
	for (auto it : ans) {
		cout << it.size() << ' ';
		for (auto x : it) {
			cout << x + 1 << ' ';
		}
		cout << '\n';
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