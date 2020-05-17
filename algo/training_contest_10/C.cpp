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
	const int MAXN = 1000;
#endif

int n, m;
int g[MAXN][MAXN];
int cur[MAXN][MAXN];
int ans[MAXN][MAXN];
int used[MAXN][MAXN];

int get_ans() {
	if (ans[0][0] == -1) {
		return 1e9;
	}
	int s = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ans[i][j] == 1) {
				s += g[i][j];
			}
			else {
				s -= g[i][j];
			}
		}
	}
	return abs(s);
}

int get_cur() {
	int s = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (cur[i][j] == 1) {
				s += g[i][j];
			}
			else {
				s -= g[i][j];
			}
		}
	}
	return abs(s);
}
void dfs(int x, int y, int cl) {
	if (x < 0 || x == n) {
		return;
	}
	if (y < 0 || y == m) {
		return;
	}
	if (cur[x][y] != cl) {
		return;
	}
	if (used[x][y]) {
		return;
	}
	used[x][y] = 1;
	dfs(x + 1, y, cl);
	dfs(x - 1, y, cl);
	dfs(x, y + 1, cl);
	dfs(x, y - 1, cl);
}

bool is_ok() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int nx = n - 1 - i;
			int ny = m - 1 - j;
			if (cur[i][j] == cur[nx][ny]) {
				return 0;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			used[i][j] = 0;
		}
	}
	dfs(0, 0, cur[0][0]);
	int nx, ny;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (cur[i][j] == cur[0][0] && !used[i][j]) {
				return 0;
			}
			if (cur[i][j] != cur[0][0]) {
				nx = i;
				ny = j;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			used[i][j] = 0;
		}
	}
	dfs(nx, ny, cur[nx][ny]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (cur[i][j] == cur[nx][ny] && !used[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

void relax() {
	if (get_cur() < get_ans()) {
		if (!is_ok()) return;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				ans[i][j] = cur[i][j];
			}
		}
	}
}

inline void init() {
	memset(ans, -1, sizeof(ans));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			if (c == '.') {
				g[i][j] = 0;
			}
			else {
				g[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i * m + j + 1) * 2 <= n * m) {
				cur[i][j] = 2;
			}
			else {
				cur[i][j] = 1;
			}
		}
	}
	relax();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m / 2; j++) {
			cur[i][j] = 1;
		}
		for (int j = m / 2; j < m; j++) {
			cur[i][j] = 2;
		}
	}
	relax();
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = m - 1; j >= 0; j--) {
			cnt++;
			if (cnt * 2 <= n * m) {
				cur[i][j] = 2;
			}
			else {
				cur[i][j] = 1;
			}
		}
	}
	relax();
	while (clock() * 1.0 / CLOCKS_PER_SEC < 0.3) {
		for (int i = 0; i < m / 2; i++) {
			int w = rand() % (n + 1);
			for (int j = 0; j < w; j++) {
				cur[j][i] = 1;
				cur[j][i + m / 2] = 2;
			}
			for (int j = w; j < n; j++) {
				cur[j][i] = 2;
				cur[j][i + m / 2] = 1;
			}
		}
		relax();
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << ans[i][j];
		}
		cout << '\n';
	}
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
	while (cin >> n >> m)
		solve();
	return 0;
}