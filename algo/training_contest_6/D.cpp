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

int A[MAXN];
int B[MAXN];

double query(int a, int b) {
	double res = -1;
	for (int i = 0; i < n; i++) {
		if (A[i] - a == 0) {
			continue;
		}
		res = max(res, (B[i] - b) * 1.0 / (a - A[i]));
	}
	return res;
}

inline void solve() {
	for (int i = 0; i < n; i++) {
		cin >> A[i] >> B[i];
	}	
	int q;
	cin >> q;
	int last = 1;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		if (!last) {
			a ^= ((1 << 29) - 1);
			b ^= ((1 << 29) - 1);
		}
		double cur = query(a, b);
		if (cur < 0) {
			last = 0;
			cout << "No cross\n";
		}	
		else {
			last = 1;
			cout << fixed << setprecision(10) << cur << '\n';
		}
	}
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