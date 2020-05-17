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
	V() {
		x = 0, y = 0;
	}
	V(double a, double b) {
		x = a, y = b;
	}

	double len() {
		return sqrt(x * x + y * y);
	}

	void norm() {
		double l = len();
		x /= l;
		y /= l;
	}

	void resz(double d) {
		norm();
		x *= d;
		y *= d;
	}

};

V operator +(V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

V operator -(V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

V rotate(V v, double alp) {
	return V(v.x * cos(alp) - v.y * sin(alp), v.x * sin(alp) + v.y * cos(alp));
}

istream& operator >>(istream &in, V &v) {
	in >> v.x >> v.y;
	return in;
}

ostream& operator <<(ostream &out, V v) {
	out << fixed << setprecision(10) << v.x << ' ' << v.y << '\n';
	return out;
}

const double PI = atan2(0, -1);

double dist(V a, V b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline void init() {

}

inline void solve() {
	init();
	V A, B, C;
	cin >> A >> B >> C;
	double r1, r2, r3;
	cin >> r1 >> r2 >> r3;
	V AB = B - A;
	if (AB.len() > r1 + r2) {
		cout << "Impossible\n";
		return;
	}
	if (AB.len() == 0) {
		swap(B, C);
		swap(r2, r3);
	}
	AB = B - A;
	if (AB.len() == 0) {
		if (r1 == r2 && r2 == r3) {
			V x = V(1, 0);
			x.resz(r1);
			cout << A + x;
			return;
		}
		cout << "Impossible\n";
		return;
	}
	AB.resz(r1);
	double l = 0;
	double r = PI;
	for (int i = 0; i < 300; i++) {
		double mid = (l + r) / 2;
		V target = A + rotate(AB, mid);
		// cerr << mid << ' ' << dist(target, B) << ' ' << r2 << '\n';
		if (dist(target, B) <= r2) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	V t1 = A + rotate(AB, (l + r) / 2);
	V t2 = A + rotate(AB, -(l + r) / 2);
	cerr << t1 << t2;
	if (abs(dist(t1, C) - r3) < 1e-6) {
		cout << t1;
		return;
	}
	if (abs(dist(t2, C) - r3) < 1e-6) {
		cout << t2;
		return;
	}
	cout << "Impossible\n";
}


signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}