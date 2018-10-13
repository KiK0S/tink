#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1000;
#endif

int n;
double g[MAXN][MAXN];

struct E{
	int a, b;
	double cost;
	E() {}
	E(int _a, int _b, double _c) {
		a = _a;
		b = _b;
		cost = _c;
	}
};

vector<E> edges;
int dsu[MAXN];
vector<E> ans;
double res;
int x[MAXN];
int y[MAXN];

int get(int x) {
	if (dsu[x] == x) {
		return x;
	}
	return dsu[x] = get(dsu[x]);
}

void unite(int a, int b, double c) {
	int pa = a;
	int pb = b;
	a = get(a);
	b = get(b);
	if (a == b) return;
	// cerr << c << '\n';
	ans.emplace_back(pa, pb, c);
	dsu[a] = b;
	res += c;
}

void solve() {
	res = 0;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
		dsu[i] = i;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			double c = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
			edges.emplace_back(i, j, c);
		}
	}
	sort(edges.begin(), edges.end(), [](E a, E b) {
		return a.cost < b.cost;
	});
	for (auto e : edges) {
		// cerr << e.a << ' ' << e.b << ' ' << e.cost << '\n';
		unite(e.a, e.b, e.cost);
	}
	cout << fixed << setprecision(6) << res << '\n';
	cout << n - 1 << '\n';
	for (auto e : ans) {
		cout << e.a + 1 << ' ' << e.b + 1 << '\n';
	}
	cout << '\n';
}

int main() {
	#ifdef DEBUG 
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
		freopen("connect.in", "r", stdin);
		freopen("connect.out", "w", stdout);	
	#endif
	while (cin >> n) {
		solve();
	}
}