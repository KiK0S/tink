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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXALP = 5;
	const int MAXSQRT = 4;
#else
	const int MAXN = 1e5 + 10;
	const int MAXALP = 26;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
string a, b;
int pref[10 * MAXN][MAXALP];
int nxt[10 * MAXN][MAXALP];

inline void init() {
	n = b.size();
	memset(pref, 0, sizeof(pref));
	for (int i = 0; i < 10 * MAXN; i++) {
		for (int j = 0; j < MAXALP; j++) {
			nxt[i][j] = INF;
		}
	}
}

int get(int pos, int l, int r) {
	if (l == 0) {
		return pref[r][pos];
	}
	return pref[r][pos] - pref[l - 1][pos];
}

bool can(vector<int> &cnt, int c) {
	for (int i = 0; i < MAXALP; i++) {
		if (get(i, c, a.size() - 1) < cnt[i]) {
			return 0;
		}
	}
	return 1;
}

inline void solve() {
	init();
	for (int i = 0; i < a.size(); i++) {
		pref[i][a[i] - 'a']++;
		nxt[i][a[i] - 'a'] = i;
	}
	for (int i = 1; i < a.size(); i++) {
		for (int j = 0; j < MAXALP; j++) {
			pref[i][j] += pref[i - 1][j];
		}
	}
	for (int i = (int)a.size() - 2; i >= 0; i--) {
		for (int j = 0; j < MAXALP; j++) {
			nxt[i][j] = min(nxt[i][j], nxt[i + 1][j]);
		}
	}
	vector<int> cnt(26);
	for (auto to : b) {
		cnt[to - 'a']++;
	}
	string res;
	int pos = 0;
	if (!can(cnt, pos)) {
		cout << "impossible\n";
		return;
	}
	pos = -1;
	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < 26; j++) {
			if (cnt[j] == 0) {
				continue;
			}
			cnt[j]--;
			int np = nxt[pos + 1][j];
			if (np != INF) {
				if (can(cnt, np + 1)) {
					res.push_back('a' + j);
					pos = np;
					break;
				}
				else {
					cnt[j]++;
				}
			}
			else {
				cnt[j]++;
			}
		}
	}
	cout << res << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> a >> b)
		solve();
	return 0;
}