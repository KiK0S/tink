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


string a;
string b;

inline void init() {

}

inline void solve() {
	init();
	deque<char> str;
	str.push_back(a[0]);
	for (auto c : b) {
		if (c <= str.front()) {
			str.push_front(c);
		}
		else {
			str.push_back(c);
		}
	}
	for (auto c : str) {
		cout << c;
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> a >> b)
		solve();
	return 0;
}