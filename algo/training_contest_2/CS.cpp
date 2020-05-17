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
	const int MAXN = 1e4;
#else
	const int MAXN = 2e5 + 10;
#endif

int n, m;
int val[MAXN];
int nval[MAXN];

inline void init() {

}

void calc_nval() {
	memset(nval, 0, sizeof(nval));
	int cnt = 0;
	for (int i = MAXN - 1; i >= 1; i--) {				
		cnt += val[i];
		if (cnt) {
			nval[cnt]++;
		}
	}
}


inline void solve() {
	init();
	bool easy = (n <= 3e3) && (m <= 3e3);
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		easy &= (a <= 3e3);
		val[a]++;
	}	
	calc_nval();
	int rep = 0;
	// assert(easy);
	for (int i = 0; i < m; i++) {
		char c;
		cin >> c;
		if (c == 't') {
			if (easy) {
				memset(nval, 0, sizeof(nval));
				int cnt = 0;
				for (int i = MAXN - 1; i >= 1; i--) {
					cnt += val[i];
					if (cnt) {
						// cerr << i << ' ' << cnt << '\t';
						nval[cnt]++;
					}
				}
				for (int i = 1; i < MAXN; i++) {
					val[i] = nval[i];
				}
			}
			else {
				rep++;
			}
		}
		if (c == 'c') {
			int a;
			cin >> a;
			if (easy) {
				cout << val[a] << '\n';
			}
			else {
				if (rep % 2) {
					cout << nval[a] << '\n';
				}
				else {
					cout << val[a] << '\n';
				}
			}
		}
		if (c == 'a') {
			int a;
			cin >> a;
			val[a]++;
		}
		if (c == 'r') {
			int a;
			cin >> a;
			if (val[a]) {
				val[a]--;
			}
		}
		calc_nval();
		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < nval[i]; j++) {
				cerr << i << ' ';
			}
		}
		cerr << '\n';
	}
	if (easy || rep % 2 == 0) {
		for (int i = 1; i < MAXN; i++) {
			while (val[i] > 0) {
				cout << i << ' ';
				val[i]--;
			}
		}
	}
	else {
		for (int i = 1; i < MAXN; i++) {
			while (nval[i] > 0) {
				cout << i << ' ';
				nval[i]--;
			}
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("CS.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m)
		solve();
	return 0;
}