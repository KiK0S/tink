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

int gcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int g = gcd(b, a % b, x, y);
	int tmp = x;
	x = y;
	y = tmp - y * (a / b);
	return g;
}
int a, b;

int get(int x, int y, int cnt, int a, int b, int g) {
	x += cnt * (b / g);
	y -= cnt * (a / g);
	return abs(x) + abs(y);
}

void solve() {
	bool sw = 0;
	if (a < b) {
		swap(a, b);
		sw = 1;
	}
	int x = 0, y = 0;
	int g = gcd(a, b, x, y);
	int l = -1e9;
	int r = 1e9;
	while (l + 10 < r) {
		int mid1 = (2 * l + r) / 3;
		int mid2 = (l + 2 * r) / 3;
		if (get(x, y, mid1, a, b, g) > get(x, y, mid2, a, b, g)) {
			l = mid1;
		}
		else {
			r = mid2;
		}
	}
	for (int i = l - 100; i <= r + 100; i++) {
		if (get(x, y, l, a, b, g) > get(x, y, i, a, b, g)) {
			l = i;
		}	
	}
	x += l * (b / g);
	y -= l * (a / g);
	if (sw) {
		swap(x, y);
	}
	cout << x << ' ' << y << ' ' << g << '\n';
}

signed main() {
	#ifdef DEBUG 
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);
	#else
		// freopen("distance5.in", "r", stdin);
		// freopen("distance5.out", "w", stdout);	
	#endif	
	while (cin >> a >> b)	
		solve();
	return 0;
}