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
const double EPS = 1e-9;
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
		// return V(1e3 + EPS, -228);
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
	return abs((l.a * a.x + l.b * a.y + l.c) / sqrtl(l.a * l.a + l.b * l.b));
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

double pnt_ray(V X, V A, V B) {
	L AB(A, B);
	if (same_dir(A, X, B)) {
		return dist(X, AB);
	}
	else {
		return dist(X, A);
	}
}

bool on_line(V X, L A) {
	if (abs(X.x * A.a + X.y * A.b + A.c) < EPS) {
		return 1;
	}
	return 0;
}

bool on_ray(V X, V A, V B) {
	if (abs((X - A) ^ (B - A)) > EPS) {
		return 0;
	}
	return same_dir(A, X, B);
}

bool on_segment(V X, V A, V B) {
	if (abs((X - A) ^ (B - A)) > EPS) {
		return 0;
	}
	return same_dir(A, X, B) && same_dir(B, X, A);
}


inline void init() {

}

V A, B, C, D;

inline void solve() {
	init();
	L AB, CD;
	AB = L(A, B);
	CD = L(C, D);
	cout.precision(20);
	cout << fixed;
	// ====================================
	{
		cout << dist(A, C) << '\n';
	}
	{
		cout << pnt_segment(A, C, D) << '\n';
	}
	{
		cout << pnt_ray(A, C, D) << '\n';
	}
	{
		cout << dist(A, CD) << '\n';
	}
	// ====================================
	{
		cout << pnt_segment(C, A, B) << '\n';
	}
	{
		V cross = AB ^ CD;
		if (on_segment(cross, A, B) && on_segment(cross, C, D)) {
			cout << 0.0 << '\n';
		}
		else {
			cout << min(min(pnt_segment(C, A, B), pnt_segment(D, A, B)), min(pnt_segment(A, C, D), pnt_segment(B, C, D))) << '\n';
		}
	}
	{
		V cross = AB ^ CD;
		if (on_segment(cross, A, B) && on_ray(cross, C, D)) {
			cout << 0.0 << '\n';
		}
		else {
			cout << min(min(pnt_ray(A, C, D), pnt_ray(B, C, D)), pnt_segment(C, A, B)) << '\n';
		}
	}
	{
		V cross = AB ^ CD;
		if (on_segment(cross, A, B) && on_line(cross, CD)) {
			cout << 0.0 << '\n';
		}	
		else {
			cout << min(dist(A, CD), dist(B, CD)) << '\n';
		}
	}
	// ===================================
	{
		cout << pnt_ray(C, A, B) << '\n';
	}
	{
		V cross = AB ^ CD;
		if (on_segment(cross, C, D) && on_ray(cross, A, B)) {
			cout << 0.0 << '\n';
		}
		else {
			cout << min(min(pnt_ray(C, A, B), pnt_ray(D, A, B)), pnt_segment(A, C, D)) << '\n';
		}
	}
	{
		V cross = AB ^ CD;
		if (on_ray(cross, A, B) && on_ray(cross, C, D)) {
			cout << 0.0 << '\n';
		}
		else {
			cout << min(pnt_ray(A, C, D), pnt_ray(C, A, B)) << '\n';
		}
	}
	{
		V cross = AB ^ CD;
		if (on_ray(cross, A, B) && on_line(cross, CD)) {
			cout << 0.0 << '\n';
		}
		else {
			cout << dist(A, CD) << '\n';
		}
	}
	// ==================================
	{
		cout << dist(C, AB) << '\n';
	}
	{
		V cross = AB ^ CD;
		if (on_segment(cross, C, D) && on_line(cross, AB)) {
			cout << 0.0 << '\n';
		}	
		else {
			cout << min(dist(C, AB), dist(D, AB)) << '\n';
		}
	}
	{
		V cross = AB ^ CD;
		if (on_ray(cross, C, D) && on_line(cross, AB)) {
			cout << 0.0 << '\n';
		}
		else {
			cout << dist(C, AB) << '\n';
		}
	}
	{
		V cross = AB ^ CD;
		if (abs(dist(A, CD) - dist(B, CD)) > EPS || dist(cross, AB) == 0 && dist(cross, CD) == 0) {
			cout << 0.0 << '\n';
		}
		else {
			cout << min(dist(A, CD), dist(B, CD)) << '\n';
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
	while (cin >> A >> B >> C >> D)
		solve();
	return 0;
}