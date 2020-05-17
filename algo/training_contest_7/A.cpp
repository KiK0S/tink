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
	const int MAXN = 100;
#endif

int n, m, k;
int g[MAXN][MAXN];

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			g[i][j] = 1e9;
		}
	}
}

int dx[2][4] = {
	{-1, 0, 1, 0},
	{-1, 0, 1, 0}
};


int dy[2][4] = {
	{0, 1, 0, -1},
	{0, -1, 0, 1}
};

inline void solve() {
	init();
	for (int i = 0; i < k; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
			int cnt = 0;
			int cur = 1;
			for (int i = 1; i <= 100; i++) {
				for (int j = 0; j < i; j++) {
					if (a >= 0 && b >= 0 && a < n && b < m)
						g[a][b] = min(g[a][b], cur);
					cur++;
					a += dx[c][cnt], b += dy[c][cnt];
				}
				cnt++;
				cnt %= 4;
				for (int j = 0; j < i; j++) {
					if (a >= 0 && b >= 0 && a < n && b < m)
						g[a][b] = min(g[a][b], cur);
					a += dx[c][cnt], b += dy[c][cnt];
					cur++;
				}
				cnt++;
				cnt %= 4;
			}
	}	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << g[i][j] << ' ';
		}
		cout << '\n';
	}
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
	while (cin >> n >> m >> k)
		solve();
	return 0;
}