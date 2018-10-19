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
int k;
int val[MAXN][MAXN];
int timer[MAXN][MAXN];
map<deque<pair<int, int>>, int> cur[MAXN][MAXN];
map<deque<pair<int, int>>, int> pre[MAXN][MAXN];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

inline void init() {

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
	deque<pair<int, int>> start;
	start.emplace_back(0, 0);
	pre[0][0][start] = 1e5 + val[0][0];
	for (int i = 1; i < k; i++) {
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				for (auto it : pre[x][y]) {
					int vl = it.second;
					for (int t = 0; t < 4; t++) {
						int nx = x + dx[t];
						int ny = y + dy[t];
						if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
							continue;
						}
						int lft = it.first.size();
						bool ok = 1;
						for (auto kek : it.first) {
							if (kek == make_pair(nx, ny) && lft <= timer[nx][ny]) {
								ok = 0;
							}
							lft--;
						}
						if (ok) {
							deque<pair<int, int>> q = it.first;
							while (q.size() && q.size() > timer[q.front().first][q.front().second]) {
								q.pop_front();
							}
							q.emplace_back(nx, ny);
							cur[nx][ny][q] = max(cur[nx][ny][q], vl + val[nx][ny]);
						}
					}
				}
			}
		}
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				cur[x][y].swap(pre[x][y]);
				cur[x][y].clear();
			}
		}
	}
	int ans = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			for (auto it : pre[x][y]) {
				ans = max(ans, it.second);
			}
		}
	}
	cout <<  ans - 1e5 << '\n';
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
	while (cin >> n >> m >> k)
		solve();
	return 0;
}