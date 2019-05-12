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

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
string s;

string t = "heidi";

inline void init() {

}

inline void solve() {
	init();
	int pnt = 0;
	for (auto c : s) {
		if (pnt < t.size() && c == t[pnt]) {
			pnt++;
		}
	}
	if (pnt == 5) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
}

signed main() {
	#ifdef DEBUG
		freopen("J.in", "r", stdin);
		freopen("J.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> s)
		solve();
	return 0;
}