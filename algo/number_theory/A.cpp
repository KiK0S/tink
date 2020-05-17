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
using namespace std;

typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 1e5;
#endif
	
#define int ll

int n;
int A, B, C;

void calc(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return;
	}
	int next_x, next_y;
	calc(b, a % b, next_x, next_y);
	x = next_y;
	y = next_x - a / b * next_y;
} 

inline void init() {

}

inline void solve() {
	init();
	int g = __gcd(A, B);
	if (C % g != 0) {
		cout << "Impossible\n";
		return;
	}
	C /= g;
	int x = 0, y = 0;
	calc(A, B, x, y);
	x *= C;
	y *= C;
	B /= g;
	A /= g;
	x += 1000000000ll * B;
	y -= 1000000000ll * A;
	int shift = x / B;
	x -= shift * B;
	y += shift * A;
	cout << x << ' ' << y << '\n'; 
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> A >> B >> C)
		solve();
	return 0;
}