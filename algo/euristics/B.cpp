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
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng((int)('a' + 'f' + 'f' + 't' + 'o' + 'r' + ' ' + 't' + 'i' + ' ' + 'p' + 'i' + 't' + 'u' + 'h'));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, m;

int color[MAXN];
set<int> neig[MAXN];
int max_color = 0;
vector<int> kek;
int cnt[MAXN];

int mex(int id) {
	kek.clear();
	bool ok = 1;
	for (auto to : neig[id]) {
		if (color[to] != -1) {
			kek.push_back(color[to]);
			// if (color[to] == color[id]) {
			// 	ok = 0;
			// }
		}
	}
	// if (ok) {
	// 	return color[id];
	// }
	sort(kek.begin(), kek.end());
	kek.resize(unique(kek.begin(), kek.end()) - kek.begin());
	for (int i = 0; i < kek.size(); i++) {
		if (kek[i] != i) {
			return i;
		}
	}
	return kek.size();
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		neig[a].insert(b);
		neig[b].insert(a);
	}
	memset(color, -1, sizeof(color));
	int max_cnt = 0;	
	vector<int> id(n);
	for (int i = 0; i < n; i++) {
		id[i] = i;
	}
	while (clock() * 2 < 9 * CLOCKS_PER_SEC) {
		for (int i = 0; i < max_color; i++) {
			cnt[i] = 0;
		}
		shuffle(id.begin(), id.end(), rng);
		for (auto i : id) {
			color[i] = mex(i);
		}
		max_color = 0;
		for (int i = 0; i < n; i++) {
			max_color = max(max_color, color[i] + 1);
		}
		for (int i = 0; i < n; i++) {
			if (color[i] == -1) {
				color[i] = max_color++;
			}
			cnt[color[i]]++;
		}
		vector<int> colors;
		for (int i = 0; i < max_color; i++) {
			if (cnt[i] != 0) {
				cnt[i] = 0;
				colors.push_back(i);
			}
		}
		sort(colors.begin(), colors.end());
		for (int i = 0; i < n; i++) {
			color[i] = lower_bound(colors.begin(), colors.end(), color[i]) - colors.begin();
			cnt[color[i]]++;
		}
		int best_id = 0;
		max_cnt = 0;
		for (int i = 0; i < max_color; i++) {
			if (max_cnt < cnt[i]) {
				max_cnt = cnt[i];
				best_id = i;
			}
		}
		for (int i = 0; i < n; i++) {
			if (color[i] == 0) {
				color[i] = best_id;
			}
			else if (color[i] == best_id) {
				color[i] = 0;
			}
		}
	}
	cout << max_color << ' ' << max_cnt << '\n';
	for (int i = 0; i < n; i++) {
		cout << color[i] + 1 << ' ';
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}