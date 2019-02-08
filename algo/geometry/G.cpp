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
	const int MAXN = 5201;
#endif

int n;


struct V {
	int x, y;
	int id;
	V() {}
	V(ll a, ll b) {
		x = a, y = b;
	}
	V(int a, int b, int c) {
		x = a, y = b, id = c;	
	}
};

pair<int, int> cnt[MAXN][MAXN];

pair<int, int> heh(V a) {
	if (a.x < 0 || a.x == 0 && a.y <= 0) {
		a.x *= -1;
		a.y *= -1;
	}
	ll g = __gcd(a.x, a.y);
	if (g == 0) {
		return make_pair(-1, -1);
	}
	return make_pair(a.x / g, a.y / g);
}

struct L {
	int a, b;
	ll c;
	L() {}
	L(V f, V s) {
		b = f.x - s.x;
		a = s.y - f.y;
		c = -1 * (1ll * a * f.x + 1ll * b * f.y);
	}
};

V operator + (V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

V operator - (V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

istream & operator >> (istream &in, V &a) {
	in >> a.x >> a.y;
	return in;
}


int cnt_timer = 0;

void check_timer() {
	cnt_timer++;
	if (cnt_timer == 10) {
		cnt_timer = 0;
		if (clock() * 100ll >= 5 * 95ll * CLOCKS_PER_SEC) {
			cout << "No\n";     // ca - chao
			exit(0);
		}
	}
}

V points[MAXN];

int get_cnt(int pos, pair<int, int> lel) {
	return upper_bound(cnt[pos], cnt[pos] + n - 1, lel) - lower_bound(cnt[pos], cnt[pos] + n - 1, lel);
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < 2 * n; i++) {
		cin >> points[i];
		points[i].id = i;
	}
	n *= 2;
	for (int i = 0; i < n; i++) {
		int pnt = 0;
		for (int j = 0; j < n; j++) {
			if (i == j) {
				continue;
			}
			cnt[i][pnt++] = heh(points[i] - points[j]);
		}
		sort(cnt[i], cnt[i] + pnt);
	}
	while (1) {
		check_timer();
		random_shuffle(points, points + n);
		for (int i = 2; i < n; i++) {
			for (int j = 2; j < n; j++) {
				if (i == j) {
					continue;
				}
				check_timer();
				L a(points[0], points[i]);
				L b(points[1], points[j]);
				ll znam = 1ll * a.a * b.b - 1ll * a.b * b.a;
				ll px = 1ll * a.b * b.c - 1ll * a.c * b.b;
				ll py = -1 * (1ll * a.a * b.c - 1ll * a.c * b.a);
				if (znam == 0 || px % znam != 0 || py % znam != 0) {
					continue;
				}
				if (abs(px / znam) > 1e6 || abs(py / znam) > 1e6) {
					continue;
				}
				V O(px / znam, py / znam);
				bool ok = 1;
				for (int k = 0; k < n; k++) {
					if (get_cnt(points[k].id, heh(points[k] - O)) != 1) {
						ok = 0;
						break;
					}
				}
				if (ok) {
					cout << "Yes\n";
					cout << O.x << ' ' << O.y << '\n';
					return;
				}
			}
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);
	#else
	
	#endif
	srand(time(0));
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}