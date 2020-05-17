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
ll s;
double INF = 1e18;
double EPS = 1e-9;

int x[MAXN];
int y[MAXN];

struct V {
	double x, y;
	int id;
	V(){}
	V(double a, double b) {x = a, y = b;}
	V(double a, double b, int c) {x = a, y = b, id = c;}
	double len() {
		return sqrtl(x * x + y * y);
	}
};

struct Vd {
	ll x, y;
	Vd(){}
	Vd(int a, int b) {
		x = a, y = b;
	}
};



struct L {
	double a, b, c;
	int id_a, id_b;
	L() {}
	L(V f, V s) {
		b = f.x - s.x;
		a = s.y - f.y;
		c = -1 * (a * f.x + b * f.y);
		if (b < 0) {
			a *= -1;
			b *= -1;
			c *= -1;
		}
	}
	L(V f, V s, int A, int B) {
		b = f.x - s.x;
		a = s.y - f.y;
		c = -1 * (a * f.x + b * f.y);
		if (b < 0) {
			a *= -1;
			b *= -1;
			c *= -1;
		}
		id_a = A, id_b = B;
	}
};

V val[MAXN];
int pos[MAXN];
V sorted[MAXN];

V operator + (V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

V operator - (V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

Vd operator - (Vd a, Vd b) {
	return Vd(a.x - b.x, a.y - b.y);
}

istream & operator >> (istream &in, V &a) {
	in >> a.x >> a.y;
	return in;
}

ostream & operator << (ostream &out, V a) {
	out << x[a.id] << ' ' << y[a.id];
	return out;
}

double get_k(L a) {
	if (abs(a.b) < EPS) {
		return -INF;
	}
	return -a.a / a.b;
}

ll operator ^ (Vd a, Vd b) {
	return a.x * b.y - a.y * b.x;
}

ll S(int a, int b, int c) {
	Vd A(x[a], y[a]);
	Vd B(x[b], y[b]);
	Vd C(x[c], y[c]);
	return abs((C - A) ^ (B - A));
}

double dist(V v, L l) {
	return (v.x * l.a + v.y * l.b + l.c) / sqrtl(l.a * l.a + l.b * l.b);
}

double check(V a, L l, V b, V c) {
	if (S(a.id, b.id, c.id) == 2 * s) {
		cout << "Yes\n";
		cout << a << '\n' << b << '\n' << c << '\n';
		exit(0);
	}
	return abs(dist(a, l));
}

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		val[i].id = i;
		x[i] = val[i].x;
		y[i] = val[i].y;
	}
	vector<L> lines;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			lines.emplace_back(val[i], val[j], i, j);
		}
	}
	sort(lines.begin(), lines.end(), [&](L a, L b) {
		bool va = a.b == 0;
		bool vb = b.b == 0;
		if (va && vb) {
			return false;
		}
		return va > vb || get_k(a) < get_k(b);
	});
	for (int i = 0; i < n; i++) {
		sorted[i] = val[i];
	}
	sort(sorted, sorted + n, [&](V a, V b){
		return dist(a, lines[0]) < dist(b, lines[0]);
	});
	for (int i = 0; i < n; i++) {
		pos[sorted[i].id] = i;
	}
	int pnt = 0;
	for (auto l : lines) {
		while (pnt < lines.size() && get_k(lines[pnt]) <= get_k(l)) {
			int a = lines[pnt].id_a;
			int b = lines[pnt].id_b;
			int id_a = pos[a];
			int id_b = pos[b];
			swap(sorted[id_a], sorted[id_b]);
			swap(pos[a], pos[b]);
			pnt++;
		}
		V pa = val[l.id_a];
		V pb = val[l.id_b];
		V norm(-(pa - pb).y, (pa - pb).x);
		double ln = sqrtl(norm.x * norm.x + norm.y * norm.y);
		norm.x /= ln;
		norm.y /= ln;
		double need_len = 2 * s / (pa - pb).len();
		norm.x *= need_len;
		norm.y *= need_len;
		{
			L need_line(pa + norm, pb + norm);
			int _L = 0;
			int _R = n - 1;
			check(sorted[_L], need_line, pa, pb);
			check(sorted[_R], need_line, pa, pb);
			while (_L + 3 < _R) {
				int mid1 = (2 * _L + _R) / 3;
				int mid2 = (_L + 2 * _R) / 3;
				if (check(sorted[mid1], need_line, pa, pb) < check(sorted[mid2], need_line, pa, pb)) {
					_R = mid2;
				}
				else {
					_L = mid1;
				}
			}
			while (_L + 1 < _R) {
				int mid = _L;
				check(sorted[mid], need_line, pa, pb);
				_L++;
			}
		}
		{
			L need_line(pa - norm, pb - norm);
			int _L = 0;
			int _R = n - 1;
			check(sorted[_L], need_line, pa, pb);
			check(sorted[_R], need_line, pa, pb);
			while (_L + 3 < _R) {
				int mid1 = (2 * _L + _R) / 3;
				int mid2 = (_L + 2 * _R) / 3;
				if (check(sorted[mid1], need_line, pa, pb) < check(sorted[mid2], need_line, pa, pb)) {
					_R = mid2;
				}
				else {
					_L = mid1;
				}
			}
			while (_L + 1 < _R) {
				int mid = _L;
				check(sorted[mid], need_line, pa, pb);
				_L++;
			}
		}
	}
	cout << "No\n";
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
	while (cin >> n >> s)
		solve();
	return 0;
}