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
	const int MAXN = 1e5;
#endif

int n;
int a[MAXN];
int b[MAXN];
int in[MAXN];

inline void init() {
	memset(in, 0, sizeof(in));
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
	}
	if (n == 1) {
		cout << "0\n";
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				continue;
			}
			if (a[i] >= a[j] && b[i] >= b[j]) {
				in[j]++;
			}
		}
	}
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		if (in[i] == 0) {
			ans.push_back(i);
		}
	}
	if (ans.empty()) {
		cout << "-1\n";
	}
	else {
		for (auto it : ans) {
			cout << it << ' ';
		}
		cout << '\n';
	}
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
	while (cin >> n)
		solve();
	return 0;
}