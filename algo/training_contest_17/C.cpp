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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));
#define int ll
const int INF = 1e9;
const int MOD = 1e9 + 7;


struct V {
	int x, y;
	V() {

	}
	V(int a, int b) {
		x = a, y = b;
	}
};

V operator + (V a, V b) {
	return V(a.x + b.x, a.y + b.y);
}

V operator - (V a, V b) {
	return V(a.x - b.x, a.y - b.y);
}

int operator ^ (V a, V b) {
	return a.x * b.y - a.y * b.x;
}

int operator * (V a, V b) {
	return a.x * b.x + a.y * b.y;
}

istream & operator >> (istream &in, V &a) {
	in >> a.x >> a.y;
	return in;
}

ostream & operator << (ostream &out, V a) {
	out << a.x << ' ' << a.y;
	return out;
}

int n, m;

V polygon[MAXN];
V dots[MAXN];
int dist[MAXN];

int D(V a, V b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool check(V a, V b) {
	
}

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		dist[i] = INF;
	}
}

inline void solve() {
	init();
	for (int i = 0; i < m; i++) {
		cin >> dots[i];
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> polygon[i];
	}
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	while (q.size()) {
		int v = q.front();
		q.pop();
		for (int i = 1; i < m; i++) {
			if (dist[i] != INF) {
				continue;
			}
			if (check(dots[v], dots[i]) || check(dots[i], dots[v])) {
				dist[i] = dist[v] + 1;
				q.push(i);
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < m; i++) {
		cerr << dist[i] << ' ';
		if (dist[i] <= 2 && dist[i] > 0) {
			ans++;
		}
	}
	cerr << '\n';
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> m)
		solve();
	return 0;
}