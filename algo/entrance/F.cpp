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
	const int MAXN = 11;
#else
	const int MAXN = 1e5;
#endif

#define int ll

int n;
int val[MAXN];

inline void init() {

}

inline void solve() {
	init();
	int g = 0;
	int mult = 1;
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		val[i] /= __gcd(val[i], mult);
		mult *= val[i];
	}
	cerr << mult << '\n';
	cout << mult / val[0] << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}