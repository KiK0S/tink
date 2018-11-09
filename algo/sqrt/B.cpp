#pragma GCC optimise("Ofast")
#pragma GCC target("sse,sse2,ssse3,sse4")
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
	const int MAXN = 2e5;
#endif

int n, q;
int val[MAXN];
const int K = 300;
int nxt[MAXN];
int cnt[MAXN];

inline void solve() {
	for (int i = 0; i < n; i++) {
		cin >> val[i];
	}
	for (int i = n - 1; i >= 0; i--) {
		if (i + val[i] >= n) {
			nxt[i] = 1e9;
			cnt[i] = 1;
		}
		else if ((i + val[i]) / K > i / K) {
			nxt[i] = i + val[i];
			cnt[i] = 1;
		}
		else {
			nxt[i] = nxt[i + val[i]];
			cnt[i] = cnt[i + val[i]] + 1;
		}
	}
	for (int i = 0; i < q; i++) {
		char c;
		cin >> c;
		if (c == '0') {
			int a, b;
			cin >> a >> b;
			a--;
			val[a] = b;
			for (int j = a; j >= a / K * K; j--) {
				if (j + val[j] >= n) {
					nxt[j] = 1e9;
					cnt[j] = 1;
				}
				else if ((j + val[j]) / K > j / K) {
					nxt[j] = j + val[j];
					cnt[j] = 1;
				}
				else {
					nxt[j] = nxt[j + val[j]];
					cnt[j] = cnt[j + val[j]] + 1;
				}
			}
		}
		else {
			int a;
			cin >> a;
			a--;
			int ans = 0;
			while (nxt[a] < n) {
				ans += cnt[a];
				a = nxt[a];
			}
			while (a + val[a] < n) {
				ans++;
				a += val[a];
			}
			cout << a + 1 << ' ' << ans + 1 << '\n';
		}
	}
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
	while (cin >> n >> q)
		solve();
	return 0;
}