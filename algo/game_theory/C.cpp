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
	const int MAXN = 1e7;
#endif

#define int ll

int n;

inline void init() {

}

map<int, int> id;
bitset<MAXN> p;

inline void solve() {
	init();
	// cerr << "here\n";
	// cout << n << ' ';
	int cnt = 1;
	for (int i = 2; i < MAXN; i++) {
		if (!p[i]) {
			id[i] = cnt++;
			for (int j = i * i; j < MAXN; j += i) {
				p[j] = 1;
			}
		}
	}
	vector<int> divisors;
	int q = n;
	for (int i = 2; i * i <= n; i++) {
		while (q % i == 0) {
			q /= i;
			divisors.push_back(id[i]);
		}
	}
	if (q != 1) {
		cout << "David\n";
		return;
	}
	int ans = 0;
	for (auto it : divisors) {
		ans ^= it;
		// cerr << it << ' ';
	}
	// ans ^= id[q];
	if (ans) {
		cout << "David\n";
	}
	else {
		cout << "Vasya\n";
	}
	// cout << endl;
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
	// for (n = 1; n < 100; n++)
	while (cin >> n) 
		solve();
	return 0;
}