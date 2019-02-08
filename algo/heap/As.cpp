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
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif

int n, m;

vector<pair<int, int>> heaps[MAXN];
int heap_id[MAXN];

const int INF = 2e9;

inline void init() {

}

inline void solve() {
	init();
	int add_id = 1;
	for (int i = 0; i < m; i++) {
		int type;
		cin >> type;
		if (type == 0) {
			int a, b;
			cin >> a >> b;
			swap(a, b);
			b--;
			heap_id[add_id] = b;
			heaps[b].emplace_back(a, add_id++);
			sort(heaps[b].begin(), heaps[b].end());
		}
		if (type == 1) {
			int a, b;
			cin >> a >> b;
			a--, b--;
			swap(a, b);
			for (auto it : heaps[b]) {
				heap_id[it.second] = a;
				heaps[a].push_back(it);
			}
			heaps[b].clear();
			sort(heaps[a].begin(), heaps[a].end());
		}
		if (type == 2) {
			int a;
			cin >> a;
			for (int i = 0; i < heaps[heap_id[a]].size(); i++) {
				if (heaps[heap_id[a]][i].second == a) {
					heaps[heap_id[a]].erase(heaps[heap_id[a]].begin() + i);
					break;
				}
			}
		}
		if (type == 3) {
			int a, b;
			cin >> a >> b;
			for (int i = 0; i < heaps[heap_id[a]].size(); i++) {
				if (heaps[heap_id[a]][i].second == a) {
					heaps[heap_id[a]][i].first = b;
					break;
				}
			}
			sort(heaps[heap_id[a]].begin(), heaps[heap_id[a]].end());
		}
		if (type == 4) {
			int a;
			cin >> a;
			a--;
			if (heaps[a].size()) {
				cout << heaps[a][0].first << '\n';
			}
			else {
				cout << INF << '\n';
			}
		}
		if (type == 5) {
			int a;
			cin >> a;
			a--;
			if (heaps[a].size()) {
				heaps[a].erase(heaps[a].begin());
			}
		}
	}
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