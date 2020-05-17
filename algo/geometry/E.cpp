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
	const int MAXN = 100;
#endif

int Q, n;
#define double long double

struct V {
	double x, y;
	V() {}
	V(double a, double b) {
		x = a, y = b;
	}
};

V operator + (V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

V operator - (V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

double operator * (V a, V b) {
	return a.x * b.x + a.y * b.y;
}

double operator ^ (V a, V b) {
	return a.x * b.y - a.y * b.x;
}

istream & operator >> (istream &in, V &a) {
	in >> a.x >> a.y;
	return in;
}

struct L {
	double a, b, c;
	V f, s;
	L() {}
	L(V _f, V _s) {
		f = _f, s = _s;
		b = f.x - s.x;
		a = s.y - f.y;
		c = -1 * (a * f.x + b * f.y);
	}
};


V operator ^ (L f, L s) {
	if (f.a * s.b == s.a * f.b) {
		return f.f;
	}
	return V((f.b * s.c - f.c * s.b) / (f.a * s.b - f.b * s.a), 
		(f.a * s.c - f.c * s.a) / (f.b * s.a - f.a * s.b));
}

double dist(V v, L l) {
	return abs(v.x * l.a + v.y * l.b + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

bool in(V p, L l) {
	return dist(p, l) <= 50;
}

void resize(V &a, double k) {
	double len = sqrtl(a.x * a.x + a.y * a.y);
	a.x /= len;
	a.y /= len;
	a.x *= k;
	a.y *= k;
}

V q[MAXN][2];
L ln[MAXN];

void check(V x) {
	if (x.x < 0 || x.x > Q || x.y < 0 || x.y > Q) {
		return;
	}
	double mn = 1e9;
	for (int i = 0; i < n; i++) {
		mn = min(dist(x, ln[i]), mn);
	}
	// cerr << mn << ' ' << '\n';
	if (mn > 50 + 1e-10) {
		cout << "NO\n";
		cout << fixed << setprecision(10) << x.x << ' ' << x.y << '\n';
		exit(0);
	}
}

inline void solve() {
	vector<L> lines;
	for (int i = 0; i < n; i++) {
		cin >> q[i][0] >> q[i][1];
		ln[i] = L(q[i][0], q[i][1]);
		V napr = q[i][0] - q[i][1];
		V norm(-napr.y, napr.x);
		resize(norm, 50 + 1e-8);
		lines.emplace_back(q[i][0] + norm, q[i][1] + norm);
		lines.emplace_back(q[i][0] - norm, q[i][1] - norm);
	}
	lines.emplace_back(V(0, 0), V(0, Q));
	lines.emplace_back(V(0, 0), V(Q, 0));
	lines.emplace_back(V(0, Q), V(Q, Q));
	lines.emplace_back(V(Q, 0), V(Q, Q));
	vector<V> points;
	for (int i = 0; i < lines.size(); i++) {
		for (int j = i + 1; j < lines.size(); j++) {
			points.push_back(lines[i] ^ lines[j]);
		}
	}
	for (auto x : points) {
		check(x);
	}
	int k = 1e5;
	for (int i = 0; i <= k; i++) {
		check(V(0, Q * 1.0 / k * i));
		check(V(Q, Q * 1.0 / k * i));
		check(V(Q * 1.0 / k * i, 0));
		check(V(Q * 1.0 / k * i, Q));
	}
	while (clock() * 1.0 < CLOCKS_PER_SEC * 0.8) {
		int C = Q * 1000;
		V rnd(rand() % C, rand() % C);
		rnd.x /= 1000;
		rnd.y /= 1000;
		check(rnd);
	}
	cout << "YES\n";
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	srand(time(0));
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> Q >> n)
		solve();
	return 0;
}