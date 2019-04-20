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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e6 + 1;
	#define cerr if (false) cerr
#endif

mt19937 rng((int)('a' + 'f' + 'f' + 't' + 'o' + 'r' + ' ' + 't' + 'i' + ' ' + 'p' + 'i' + 't' + 'u' + 'h'));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m;

struct E {
	int from, to, cost, s_id;
	E(){}
	E(int a, int b, int c, int d) {
		from = a, to = b, cost = c, s_id = d;
	}
};

vector<E> edges;
vector<int> g[MAXN];
int used[MAXN];
vector<int> idx;
pair<int, ll> ans = make_pair(0, 0ll);
vector<int> res;
int start;

int last_clock;

inline void init() {

}

void dfs(int v, pair<int, ll> s = make_pair(0, 0ll)) {
	if ((clock() - last_clock) * 10 > CLOCKS_PER_SEC) {
		return;
	}
	used[v] = 1;
	for (auto id : g[v]) {
		int nxt = v;
		nxt ^= edges[id].from;
		nxt ^= edges[id].to;
		if (nxt == start) {
			pair<int, ll> cur;
			cur.first = s.first + 1;
			cur.second = s.second + edges[id].cost;
			if (cur > ans) {
				ans = cur;
				res = idx;
				res.push_back(id);
			}
		}
		if (used[nxt]) {
			continue;
		}
		idx.push_back(edges[id].s_id);
		dfs(nxt, make_pair(s.first + 1, edges[id].cost + s.second));
		if ((clock() - last_clock) * 10 > CLOCKS_PER_SEC) {
			return;
		}	
		idx.pop_back();
	}
	used[v] = 0;
}

inline void solve() {
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		edges.emplace_back(a, b, c, i);
		g[a].push_back(i);
		g[b].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		shuffle(g[i].begin(), g[i].end(), rng);
	}
	vector<int> I(n);
	for (int i = 0; i < n; i++) {
		I[i] = i;
	}
	shuffle(I.begin(), I.end(), rng);
	for (int j = 0; j < n; j++) {
		last_clock = clock();
		start = I[j];
		dfs(start);
	}
	cout << ans.first << ' ' << ans.second << '\n';
	for (auto id : res) {
		cout << id + 1 << ' ';
	}
	cout << '\n';


}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}