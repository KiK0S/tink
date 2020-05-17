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

int n, k;

int val[MAXN];

inline void init() {

}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		if (c <= '9' && c >= '0') {
			val[i] = c - '0';
		}
		else {
			val[i] = c - 'A' + 10;
		}
	}
	int sum = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (val[i] + 1 < k && sum - 1 >= 0) {
			val[i]++;
			sum--;
			for (int j = n - 1; j > i; j--) {
				val[j] = min(k - 1, sum);
				sum -= val[j];
			}
			break;
		}
		else {
			sum += val[i];
		}
		if (i == 0) {
			cout << "Impossible";
			return;
		}
	}
	for (int i = 0; i < n; i++) {
		if (val[i] < 10) {
			cout << (char)('0' + val[i]);
		}
		else {
			cout << (char)('A' + val[i] - 10);
		}
	}
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
	while (cin >> k >> n)
		solve();
	return 0;
}