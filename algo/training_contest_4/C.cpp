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
	const int MAXN = 11;
#endif

int n, m;
int all;
int val[MAXN][MAXN];
int timer[MAXN][MAXN];
int cur[MAXN][MAXN][1 << 14];
int pre[MAXN][MAXN][1 << 14];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

inline void init() {
	all--;
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> val[i][j];
			for (int l = 0; l < 10; l++) {
				if ((1 << l) >= val[i][j]) {
					timer[i][j] = l + 1;
					break;
				}
			}
		}
	}
	for (int i = 0; i < (1 << 14); i++) {
		pre[0][0][i] = 1e5 + val[0][0];
	}
	for (int mv = 0; mv < all; mv++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k];
					int y = j + dy[k];
					// cerr << x << ' ' << y << '\n';
					if (x < 0 || y < 0 || x >= n || y >= m) {
						continue;
					}
					for (int mask = 0; mask < (1 << min(2 * mv, 14)); mask++) {
						if (pre[i][j][mask] < 1e5) {
							continue;
						}
						// cerr << mv << ' ' << i << ' ' << j << ' ' << mask << '\n';
						int cr = mask;
						int _dx = 0, _dy = 0;
						bool ok = 1;
						for (int l = 0; l < min(mv, 7); l++) {
							int c = cr % 4;
							// cerr << c << '\n';
							_dx -= dx[c];
							_dy -= dy[c];
							int nx = i + _dx;
							int ny = j + _dy;
							if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
								ok = 0;
								break;
							}
							// cerr << '\t' << nx << ' ' << ny << ' ' << timer[nx][ny] << '\n';
							if (nx == x && ny == y && timer[nx][ny] > l + 1) { // mb l + 1
								ok = 0;
								break;
							}
							cr /= 4;
						}
						if (ok) {
							// cerr << mv << ' ' << i << ' ' << j << ' ' << x << ' ' << y << ' ' << mask << ' ' << (((mask << 2) + k) & ((1 << 16) - 1)) << '\n';
							cur[x][y][((mask << 2) + k) & ((1 << 14) - 1)] = max(cur[x][y][((mask << 2) + k) & ((1 << 14) - 1)], pre[i][j][mask] + val[x][y]);
						}
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int mask = 0; mask < (1 << 14); mask++) {
					swap(cur[i][j][mask], pre[i][j][mask]);
					cur[i][j][mask] = 0;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int mask = 0; mask < (1 << 14); mask++) {
				ans = max(ans, pre[i][j][mask]);
			}
		}
	}
	cout << ans - 1e5 << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m >> all)
		solve();
	return 0;
}