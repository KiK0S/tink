#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 5;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
#endif

#define int long long

struct V {
	double x, y;
	V() {}
	V(double a, double b) {
		x = a, y = b;
	}
};

V operator -(V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

V operator +(V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

double operator ^(V a, V b) {
	return a.x * b.y - a.y * b.x;
}

double operator *(V a, V b) {
	return a.x * b.x + a.y * b.y;
}

double len(V a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

void resize(V &a, double k) {
	double l = len(a);
	a.x /= l;
	a.y /= l;
	a.x *= k;
	a.y *= k;
}

double f(V p, V A, V B, double k) {
	V a = B - A;
	resize(a, k);
	V v = (A + a) - p;
	return len(v);
}

double get(V p, V A, V B) {
	V AB = B - A;
	double l = 0;
	double r = len(AB);
	for (int i = 0; i < 100; i++) {
		double m1 = (l * 2 + r) / 3;
		double m2 = (l + r * 2) / 3;
		if (f(p, A, B, m1) > f(p, A, B, m2)) {
			l = m1;
		}
		else {
			r = m2;
		}
	}
	return f(p, A, B, (l + r) / 2);
}

double g(V A, V B, V C, V D, double k) {
	V a = B - A;
	resize(a, k);
	V v = (A + a);
	return get(v, C, D);
}

void solve() {
	vector<V> q;
	for (int i = 0; i < 4; i++) {
		int x, y;
		cin >> x >> y;
		q.emplace_back(x, y);
	}
	V A = q[0], B = q[1], C = q[2], D = q[3];
	V AB = B - A;
	V CD = D - C;
	double l = 0;
	double r = len(AB);
	for (int i = 0; i < 100; i++) {
		double m1 = (2 * l + r) / 3;
		double m2 = (l + 2 * r) / 3;
		if (g(A, B, C, D, m1) > g(A, B, C, D, m2)) {
			l = m1;
		}
		else {
			r = m2;
		}
	}
	cout << fixed << setprecision(10) << g(A, B, C, D, (l + r) / 2) << '\n';
}

signed main() {
	#ifdef DEBUG 
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
		freopen("distance5.in", "r", stdin);
		freopen("distance5.out", "w", stdout);	
	#endif		
	solve();
	return 0;
}