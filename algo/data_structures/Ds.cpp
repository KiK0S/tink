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

#define int ll

int n;
int cur[MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> cur[i];
	}	
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		char c;
		cin >> c;
		if (c == 'C') {
			int a, b;
			cin >> a >> b;
			a--;
			cur[a] = b;
		}
		else {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			a--, c--;
			int s1 = 0, s2 = 0;
			for (int j = a; j <= c; j++) {
				if (cur[j] <= b) {
					s1 += d - b;
				}
				else if (cur[j] >= d) {
					s2 += d - b;
				}
				else {
					s1 += d - cur[j];
					s2 += cur[j] - b;
				}
			}
			if (s1 > s2) {
				cout << "1\n";
			}
			if (s2 > s1) {
				cout << "2\n";
			}
			if (s1 == s2) {
				cout << "0\n";
			}
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("Ds.in", "r", stdin);
		freopen("Ds.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}