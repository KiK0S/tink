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

int tin[MAXN];
int sz[MAXN];
int h[MAXN];
int parent[MAXN];


inline void init() {
	parent[0] = -1;
}

inline void solve() {
	init();
	for (int i = 1; i <= n; i++) {
		cin >> parent[i];
	}
	int ans = 0;
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int t;
		cin >> t;
		int a, b;
		cin >> a >> b;
		a = (a + ans - 1) % n + 1;
		b = (b + ans - 1) % n + 1;
		if (t == 0) {
			vector<int> A, B;
			{
				int cur = a;
				while (cur != -1) {
					A.push_back(cur);
					cur = parent[cur];
				}
			}
			{
				int cur = b;
				while (cur != -1) {
					B.push_back(cur);
					cur = parent[cur];
				}
			}
			reverse(A.begin(), A.end());
			reverse(B.begin(), B.end());
			for (int i = 0; i < min(A.size(), B.size()); i++) {
				if (A[i] == B[i]) {
					ans = A[i];
				}
				else {
					break;
				}
			}
			cout << ans << '\n';
		}
		else {
			parent[a] = b;
		}
	}
}

signed main() {
	#ifdef DEBUG
		freopen("D.in", "r", stdin);
		freopen("Ds.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}