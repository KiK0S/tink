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
	const int MAXN = 100;
#endif

int n;

inline void init() {

}

inline void solve() {
	init();
	n = 3650;
	cout << 0 << endl;
	int ans = 0;
	int cnt_a = 48;////
	int cnt_b = MAXN;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int x = rand() % MAXN;
		int q;
		if (i + 1 == n && sum >= 3) {
			cout << 1 << endl;
			cin >> x;
			break;
		}
		// heh 4`213weds;l
		if (x < cnt_a) {
			q = 1;
		}
		else {
			q = 2;
		}
		cout << q << endl;	
		cin >> x;
		// if (x == 1) {
		// 	cnt_a++;
		// }
		// else {
		// 	cnt_b++;
		// }
		if ((q + x) % 2 == 1) {
			sum -= (q + x);
		}
		else {
			sum += (q + x);
		}
		// heh #3 / / /
		if (4 * (n - i) < -sum) {
			assert(0);
		}
	}
	cin >> ans;
}

signed main() {
	srand(time(0));
	solve();
	return 0;
}