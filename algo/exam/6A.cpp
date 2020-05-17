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
	const int MAXK = 5;
#else
	const int MAXN = 1e5 + 10;
	const int MAXK = 205;
#endif
int n, k;

const int INF = 1e9 + 10;

struct Line {
	int k = 0;
	ll b = 0;
	int id = -1;
	Line(){}
	Line(int _a, ll _b, int _c) {
		k = _a, b = _b, id = _c;
	}
	inline pair<ll, int> get(int x) {
		return make_pair(1ll * k * x + b, id);
	}
};


ll cross(Line a, Line b) {
	if (a.k < b.k) {
		swap(a, b);
	}
	int x = (b.b - a.b) / (a.k - b.k);		
	if (b.b < a.b) {
		x--;
	}
	return x;
}

struct CHT {
	vector<Line> lines;
	vector<int> dots;
	void upd(Line x) {
		while (lines.size() && lines.back().get(dots.back()) < x.get(dots.back())) {
			lines.pop_back();
			dots.pop_back();
		}
		if (lines.size() == 0) {
			dots.push_back(-INF);
		}
		else {
			if (lines.back().k == x.k) {
				lines.pop_back();
			}
			else {
				dots.push_back(cross(lines.back(), x));
			}
		}
		lines.push_back(x);
	}

	pair<ll, int> get(int x) {
		int idx = lower_bound(dots.begin(), dots.end(), x) - dots.begin() - 1;
		return lines[idx].get(x);
	}
};

CHT roots[2];
int pre[MAXN][MAXK];
ll pref[MAXN];
int val[MAXN];
Line push[MAXN];

inline void init() {
	for (int i = 0; i < 2; i++) {
		roots[i].upd(Line(0, -1, -1));
	}
	for (int i = 0; i <= n; i++) {
		push[i] = Line(0, -1, -1);
	}
}

inline void solve() {
	init();
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
		pref[i] = pref[i - 1] + val[i];
		// cerr << pref[i] << ' ';
	}
	if (pref[n] == 0) {
		cout << "0\n";
		for (int i = 0; i < k; i++) {
			cout << i + 1 << ' ';
		}
		cout << '\n';
		return;
	}
	ll res = 0;
	for (int i = 0; i <= k; i++) {
		roots[i & 1].dots.clear();
		roots[i & 1].lines.clear();
		roots[i & 1].upd(Line(0, -1, -1));
		for (int j = 1; j <= n; j++) {
			if (i != 0) {
				pair<ll, int> gt = roots[(i & 1) ^ 1].get(pref[j]);
				roots[(i & 1) ^ 1].upd(push[j]);
				pre[j][i] = gt.second;
				Line nl = Line(pref[j], -1ll * pref[j] * pref[j] + gt.first, j);
				push[j] = nl;
				if (i == k && j == n) {
					res = gt.first;
				}
			}
			else {
				Line nl = Line(pref[j], -1ll * pref[j] * pref[j], j);
				push[j] = nl;
			}
		}
	}
	cout << res << '\n';
	int fin = n;
	int ca = 0;
	vector<int> ret;
	for (int i = k; i > 0; i--) {
		fin = pre[fin][i];
		ret.push_back(fin);
	}
	for (auto it : ret) {
		if (it > 0 && it < n) {
			cout << it << ' ';
			ca++;
		}
	}
	// for (int i = 1; i <= n; i++) {
	// 	if (ca == k) {
	// 		break;
	// 	}
	// 	if (val[i] == 0) {
	// 		cout << i << ' ';
	// 		ca++;
	// 	}
	// }
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("6A.in", "r", stdin);
		freopen("6A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
		solve();
	return 0;
}