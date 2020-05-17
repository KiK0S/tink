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

#define int ll
#define double long double

int n;
const double EPS = 1e-5;
struct V {
	double x, y;
	V() {}
	V(double a, double b) {
		x = a, y = b;
	}
};

struct L {
	double a, b, c;
	V f, s;
	L() {}
	L(V _f, V _s) {
		f = _f;
		s = _s;
		b = f.x - s.x;
		a = s.y - f.y;
		c = -1 * (a * f.x + b * f.y);
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

V operator ^ (L f, L s) {
	if (f.a * s.b == s.a * f.b) {
		return f.f;
	}
	return V((f.b * s.c - f.c * s.b) / (f.a * s.b - f.b * s.a), 
			 (f.a * s.c - f.c * s.a) / (f.b * s.a - f.a * s.b));
}

istream & operator >> (istream &in, V &a) {
	in >> a.x >> a.y;
	return in;
}

ostream & operator << (ostream &out, V a) {
	out << a.x << ' ' << a.y;
	return out;
}

bool same_dir(V o, V a, V b) {
	return (a - o) * (b - o) >= -EPS;
}

double dist(V a, V b) {
	return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dist(V a, L l) {
	return abs(a.x * l.a + a.y * l.b + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

double pnt_segment(V X, V A, V B) {
	L AB = L(A, B);
	if (same_dir(A, X, B) && same_dir(B, X, A)) {
		return dist(X, AB);
	}
	else {
		return min(dist(X, A), dist(X, B));
	}
}

bool on_segment(V X, V A, V B) {
	if (abs((X - A) ^ (B - A)) > EPS) {
		return 0;
	}
	return same_dir(A, X, B) && same_dir(B, X, A);
}

double dist_segments(V A, V B, V C, V D) {
	L AB, CD;
	AB = L(A, B);
	CD = L(C, D);
	{
		V cross = AB ^ CD;
		if (on_segment(cross, A, B) && on_segment(cross, C, D)) {
			return 0;
		}
		else {
			return min(min(pnt_segment(C, A, B), pnt_segment(D, A, B)), min(pnt_segment(A, C, D), pnt_segment(B, C, D)));
		}
	}
}

inline void init() {

}

V A, B, C, D;
V d1, d2;

double gd(double x) {
	V a1(d1.x * x, d1.y * x);
	V a2(d2.x * x, d2.y * x);
	return dist_segments(A + a1, B + a1, C + a2, D + a2);
}

inline void solve() {
	init();
	double l = 0;
	double r = 1e9;
	for (int i = 0; i < 100000; i++) {
		double m1 = (2 * l + r) / 3;
		double m2 = (l + r * 2) / 3;
		if (gd(m1) <= gd(m2)) {
			r = m2;
		}
		else {
			l = m1;
		}
	}
	double res = (l + r) / 2;
	if (gd(res) > EPS) {
		cout << "-1\n";
		return;
	}
	cout << fixed << setprecision(10) << res << '\n';
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
	while (cin >> A >> B >> C >> D >> d1 >> d2)
		solve();
	return 0;
}