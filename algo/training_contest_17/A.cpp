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

mt19937 rng(time(0));

const int INF = 2e9;
const int MOD = 1e9 + 7;

int n, k;

int mn[MAXN];
int mx[MAXN];
vector<int> a[MAXN];

int f[MAXN];

void upd(int pos, int x) {
	for (int i = pos + 1; i < MAXN; i += i & -i) {
		f[i] += x;
	}
}

int get(int pos) {
	int ans = 0;
	for (int i = pos + 1; i > 0; i -= i & -i) {
		ans += f[i];
	}
	return ans;
}

inline void init() {
	for (int i = 0; i < n; i++) {
		mn[i] = INF;
		mx[i] = 0;
	}
}

inline void solve() {
	init();
	vector<int> coords;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		while (x--) {
			int c;
			cin >> c;
			mx[i] = max(mx[i], c);
			mn[i] = min(mn[i], c);
		}
		coords.push_back(mx[i]);
		cerr << mn[i] << ' ' << mx[i] << '\n';
	}
	sort(coords.begin(), coords.end());
	coords.resize(unique(coords.begin(), coords.end()) - coords.begin());
	vector<pair<int, int>> kek;
	for (int i = 0; i < n; i++) {
		kek.emplace_back(mn[i], mx[i]);
	}
	sort(kek.begin(), kek.end());
	for (int i = 0; i < n; i++) {
		upd(lower_bound(coords.begin(), coords.end(), kek[i].second) - coords.begin(), 1);
	}
	for (int i = 0; i < n; i++) {
		cerr << kek[i].first << ' ' << kek[i].second << '\t';
	}
	cerr << '\n';
	
	int ans = INF;
	for (int i = 0; i + k <= n; i++) {
		int l = -1;
		int r = (int)coords.size() - 1;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (get(mid) >= k) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
		ans = min(ans, coords[r] - kek[i].first);
		upd(lower_bound(coords.begin(), coords.end(), kek[i].second) - coords.begin(), -1);
	}
	cout << ans << '\n';
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
	while (cin >> n >> k)
		solve();
	return 0;
}