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

int n;

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


V A, B, C, D, va, vb;

inline void init() {

}

inline void solve() {
	init();
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
	while (cin >> A >> B >> C >> D >> va >> vb)
		solve();
	return 0;
}