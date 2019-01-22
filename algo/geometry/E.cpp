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

int Q, n;


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

int cross(L f, L s) {
	if (f.a * s.b == s.a * f.b) {
		return 0;
	}
	return 1;
}

double dist(V v, L l) {
	return abs(v.x * l.a + v.y * l.b + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

bool in(V p, L l) {
	return dist(p, l) <= 50;
}

bool intersect_1(double a, double b, double c, double d) {
	if (a > b) {
		swap(a, b);
	}
	if (c > d) {
		swap(c, d);
	}
	return min(b, d) <= max(a, c);
}

double s(V A, V B, V C) {
	return (B - A) ^ (C - A);
}

bool intersect(V A, V B, V C, V D) {
	return intersect_1(A.x, B.x, C.x, D.x) && intersect_1(A.y, B.y, C.y, D.y) &&
			s(A, B, C) * s(A, B, D) <= 0 && s(C, D, A) * s(C, D, B) <= 0;
}

void resize(V &a, double k) {
	double len = sqrt(a.x * a.x + a.y * a.y);
	a.x /= len;
	a.y /= len;
	a.x *= k;
	a.y *= k;
}

V q[MAXN][2];
V top[MAXN][2];
V bot[MAXN][2];
L ln[MAXN];

inline void init() {

}

void get(V &lb, V &lt, V &rb, V &rt, vector<int> &idx, int level = 0) {
	if (level > 20) {
		return;
	}
	if (clock() * 1.0 >= CLOCKS_PER_SEC * 3.8) {
		cout << "YES\n";
		exit(0);
	}
	bool sm = 0;
	vector<int> nxt;
	for (auto i : idx) {
		if (in(lb, ln[i])) {
			nxt.push_back(i);
			sm = 1;
		}
		if (in(lt, ln[i])) {
			nxt.push_back(i);
			sm = 1;
		}
		if (in(rb, ln[i])) {
			nxt.push_back(i);
			sm = 1;
		}
		if (in(rt, ln[i])) {
			nxt.push_back(i);
			sm = 1;
		}
		if (in(lb, ln[i]) && in(lt, ln[i]) && in(rb, ln[i]) && in(rt, ln[i])) {
			// exit(1);
			return;
		}
	}
	for (auto i : idx) {
		{
			V cross = L(lb, lt) ^ ln[i];
			if ((lt - cross) * (lb - cross) <= 0) {
				sm = 1;
				nxt.push_back(i);
			}
		}
		{
			V cross = L(lb, rb) ^ ln[i];
			if ((lb - cross) * (rb - cross) <= 0) {
				sm = 1;
				nxt.push_back(i);
			}
		}
		{
			V cross = L(rt, lt) ^ ln[i];
			if ((rt - cross) * (lt - cross) <= 0) {
				sm = 1;
				nxt.push_back(i);
			}
		}
		{
			V cross = L(rb, rt) ^ ln[i];
			if ((rt - cross) * (rb - cross) <= 0) {
				sm = 1;
				nxt.push_back(i);
			}
		}
	}
	sort(nxt.begin(), nxt.end());
	V lm(lb.x, (lb.y + lt.y) / 2);
	V rm(rb.x, (rb.y + rt.y) / 2);
	V mt((lt.x + rt.x) / 2, lt.y);
	V mb((lb.x + rb.x) / 2, lb.y);
	V mm((lb.x + rb.x) / 2, (lb.y + lt.y) / 2);
	if (!sm) {
		cout << "NO\n";
		cout << mm.x << ' ' << mm.y << '\n';
		exit(0);
	}
	nxt.resize(unique(nxt.begin(), nxt.end()) - nxt.begin());
	get(lb, lm, mb, mm, nxt, level + 1);
	get(mb, mm, rb, rm, nxt, level + 1);
	get(lm, lt, mm, mt, nxt, level + 1);
	get(mm, mt, rm, rt, nxt, level + 1);
}

inline void solve() {
	init();
	vector<int> f;
	for (int i = 0; i < n; i++) {
		cin >> q[i][0] >> q[i][1];
		ln[i] = L(q[i][0], q[i][1]);
		f.push_back(i);
	}
	V A(0, 0);
	V B(0, Q);
	V C(Q, 0);
	V D(Q, Q);
	get(A, B, C, D, f);
	cout << "YES\n";
}

signed main() {
	#ifdef DEBUG
		freopen("E.in", "r", stdin);
		freopen("E.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> Q >> n)
		solve();
	return 0;
}