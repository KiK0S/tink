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
	const int MAXN = 10;
#else
	const int MAXN = 200;
#endif

string a, b;
string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string dp[MAXN][MAXN];
string INF;

inline void init() {
	for (int i = 0; i < MAXN; i++) {
		INF += "Z";
	}
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = INF;
		}
	}
}

void relax(int x_from, int y_from, int x_to, int y_to, char c) {
	string s = dp[x_from][y_from];
	if (c != ' ')
		s.push_back(c);
	if (dp[x_to][y_to].size() > s.size()) {
		dp[x_to][y_to] = s;
	}
}

inline void solve() {
	init();
	dp[0][0] = "";
	int n = a.size();
	int m = b.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			// cerr << i << ' ' << j << ' ' << dp[i][j] << '\n';
			if (a[i] == '*') {
				relax(i, j, i + 1, j, ' ');
			}
			if (b[j] == '*') {
				relax(i, j, i, j + 1, ' ');
			}
			if (a[i] == '*' && b[j] == '*') {
				relax(i, j, i + 1, j + 1, ' ');
			}
			for (auto c : alph) {
				if ((a[i] == c || a[i] == '?') && (b[j] == c || b[j] == '?')) {
					relax(i, j, i + 1, j + 1, c);
				}
				if (a[i] == '*' && (b[j] == c || b[j] == '?')) {
					relax(i, j, i + 1, j + 1, c);
					relax(i, j, i, j + 1, c);
				}
				if (b[j] == '*' && (a[i] == c || a[i] == '?')) {
					relax(i, j, i + 1, j + 1, c);
					relax(i, j, i + 1, j, c);
				}
				if (a[i] == '*' && b[j] == '*') {
					relax(i, j, i + 1, j + 1, c);
					relax(i, j, i, j + 1, c);
					relax(i, j, i + 1, j, c);
					relax(i, j, i, j, c);
				}
			}
		}
		// cerr << '\n';
	}
	if (dp[n][m] == INF) {
		cout << "No solution!\n";
		return;
	}
	cout << dp[n][m] << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("I.in", "r", stdin);
		freopen("I.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> a >> b)
		solve();
	return 0;
}