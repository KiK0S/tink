#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 200;
#endif

#define int ll

int n, m, s;

int dp[MAXN][MAXN];

int mex(vector<int> &a) {
	sort(a.begin(), a.end());
	a.resize(unique(a.begin(), a.end()) - a.begin());
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != i) {
			return i;
		}
	}
	return a.size();
}

int get(int a, int b) {
	if (a > b) {
		swap(a, b);
	}
	if (dp[a][b] != -1) {
		return dp[a][b];
	}
	if (a == 1 && b <= s) {
		return dp[a][b] = 0;
	}
	vector<int> q;
	for (int i = 1; i < a; i++) {
		q.push_back(get(i, b) ^ get(a - i, b));
	}
	for (int i = 1; i < b; i++) {
		q.push_back(get(a, i) ^ get(a, b - i));
	}
	return dp[a][b] = mex(q);
}

void solve() {
	memset(dp, -1, sizeof(dp));
	cout << (get(n, m) ? 1 : 2) << '\n';
}

signed main() {
	#ifdef DEBUG 
		freopen("D.in", "r", stdin);
		freopen("D.out", "w", stdout);
	#else
		freopen("choco.in", "r", stdin);
		freopen("choco.out", "w", stdout);	
	#endif
	while (cin >> n >> m >> s) {
		solve();
	}
	return 0;
}