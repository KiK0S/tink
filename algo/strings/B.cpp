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
	const int MAXN = 10;
#endif
#define int ll
int n;

string s[MAXN];
int h[MAXN][20001];
int tpow[20001];
int p = 179;
int mod = 1e9 + 7;
map<int, int> rev;
map<int, int> mapa;
inline void init() {
	tpow[0] = 1;
	for (int i = 1; i < 20001; i++) {
		tpow[i] = tpow[i - 1] * p;
		tpow[i] %= mod;
	}
}


inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		for (int j = 0; j < s[i].size(); j++) {
			h[i][j] = (j == 0 ? 0 : h[i][j - 1]) * p + s[i][j] - 'a' + 1;
			h[i][j] %= mod;
		}
	}
	int l = 0;
	int r = 20001;
	string ans = "";
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		mapa.clear();
		int hok = -1;
		rev.clear();
		for (int i = 0; i < n; i++) {
			for (int j = mid - 1; j < s[i].size(); j++) {
				int cur = h[i][j] - (j - mid == -1 ? 0 : h[i][j - mid]) * tpow[mid];
				cur %= mod;
				cur += mod;
				cur %= mod;
				// cerr << cur << ' ';
				if (i == 0) {
					rev[cur] = j;
					mapa[cur] = 0;
				}
				else {
					if (!mapa.count(cur) || mapa[cur] + 1 < i) {
						mapa[cur] = -1;
					}
					else {
						// cerr << "here " << i << '\n';
						if (i == n - 1) {
							hok = cur;
							// cerr << "here\n";
						}
						mapa[cur] = i;
					}
				}
			}
			// cerr << '\n';
		}
		// cerr << '\n';
		if (hok == -1) {
			r = mid;
		}
		else {
			l = mid;
			ans = s[0].substr(rev[hok] - mid + 1, mid);
		}
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}