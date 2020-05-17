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

int p, h;

int len = 33;
int mod = 1e9 + 7;
inline void init() {

}

inline void solve() {
	init();
	while (clock() * 1.0 / CLOCKS_PER_SEC < 0.49) {
		string s(len, 'a');
		for (int i = 0; i < len; i++) {
			s[i] = 'a' + rand() % 26;
		}
		cerr << s << '\n';
		int cur = 0;
		for (int i = 0; i < len; i++) {
			cur += s[i] - 'a' + 1;
			if (cur > mod) {
				cur -= mod;
			}
			if (cur == h) {
				cout << s.substr(0, i + 1) << '\n';
				return;
			}
			cur = (1ll * cur * p) % mod;
		}
	}
}

signed main() {
	srand(time(0));
	#ifdef DEBUG
		freopen("8B.in", "r", stdin);
		freopen("8B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> p >> h)
		solve();
	return 0;
}