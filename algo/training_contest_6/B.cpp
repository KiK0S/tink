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
#define int ll

ll n;
const int MAXN = 1e6 + 100;

inline void solve() {
	if (n == 1) {
		cout << "2\n";
		return;
	}
	if (n == 2) {
		cout << "3\n";
		return;
	}
	for (int i = 2; i <= MAXN; i++) {
		int cur = 0;
		int pw = 1;
		for (int j = 0; cur < n; j++) {
			cur += pw;
			pw *= i;
			if (n % cur == 0 && n / cur < i) {
				cout << i << '\n';
				return;
			}
		}
	}
	vector<int> q;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			q.push_back(n / i);
			q.push_back(i);
		}
	}
	sort(q.rbegin(), q.rend());
	for (auto it : q) {
		// cerr << it << ' ';
		if (n / it - 1 > it) {
			cout << n / it - 1 << '\n';
			return;
		}
	}
	cout << n - 1 << '\n';
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
	while (cin >> n)
		solve();
	return 0;
}