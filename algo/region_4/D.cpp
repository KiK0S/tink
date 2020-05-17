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
	double len() {
		return sqrt(x * x + y * y);
	}
	void resize(double k) {
		double l = len();
		x /= l;
		y /= l;
		x *= k;
		y *= k;
	}
};

V operator + (V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

V operator - (V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

double operator ^ (V a, V b) {
	return a.x * b.y - a.y * b.x;
}

const bool operator < (V a, V b) {
	int ca = 0;
	if (a.y > 0 || a.y == 0 && a.x > 0) {
		ca = 1;
	}
	int cb = 0;
	if (b.y > 0 || b.y == 0 && b.x > 0) {
		cb = 1;
	}
	if (ca != cb) {
		return ca;
	}
	return (a ^ b) > 0;
}

istream & operator >> (istream &in, V &a) {
	in >> a.x >> a.y;
	return in;
}

V centers[MAXN];
double R[MAXN];


inline void solve() {
	for (int i = 0; i < n; i++) {
		cin >> centers[i] >> R[i];
	}
	V O;
	cin >> O;
	double l = 0;
	double r = 1e9;
	int att = 100;
	while (att--) {
		double mid = (l + r) / 2;
		bool ok = 0;
		{
			vector<int> trouble;
			for (int i = 0; i < n; i++) {
				if ((centers[i] - O).len() > R[i] + mid) {
					trouble.push_back(i);
				}
			}
			vector<pair<V, int>> all;
			for (auto id : trouble) {
				double dist = (O - centers[id]).len();
				dist /= (mid + R[id]);
				dist *= mid;
				double side = sqrt(dist * dist - mid * mid);
				double sn = mid / dist;
				double cs = side / dist;
				V A = centers[id] - O;
				A.resize(1);
				V na;
				na.x = A.x * cs - A.y * sn;
				na.y = A.x * sn + A.y * cs;
				na.x *= -1;
				na.y *= -1;
				V nb;
				nb.x = A.x * cs + A.y * sn;
				nb.y = -A.x * sn + A.y * cs;
				nb.x *= -1;
				nb.y *= -1;
				if ((na ^ nb) < 0) {
					swap(na, nb);
				}
				all.push_back(make_pair(na, -1));
				all.push_back(make_pair(nb, 1));
			}
			sort(all.begin(), all.end());
			if (all.empty()) {
				ok = 1;
			}
			for (int i = 0; i < all.size(); i++) {
				if (all[i].second == -1 && all[(i + 1) % all.size()].second == 1) {
					int c = 0;
					while (all[i].second == -1) {
						c++;
						i--;
						if (i == -1) {
							i = all.size() - 1;
						}
					}
					if (c * 2 == all.size()) {
						ok = 1;
					}
					break;
				}
			}
		}
		if (ok) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	cout << fixed << setprecision(10) << r << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}