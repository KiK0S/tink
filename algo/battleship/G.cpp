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
string s;

bool l(char c) {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

inline void init() {

}

inline void solve() {
	init();
	s.push_back('#');
	string last;
	vector<string> ans;
	for (auto c : s) {
		if (l(c)) {
			last.push_back(c);
		}
		else {
			bool ok = 0;
			for (int i = 1; i < last.size(); i++) {
				for (int j = i + 1; j + 1 < last.size(); j++) {
					if (last[i] != last[j]) {
						ok = 1;
						swap(last[i], last[j]);
						break;
					}
				}
				if (ok) {
					break;
				}
			}
			ans.push_back(last);
			last.clear();
			string st;
			if (c == '#') {
				break;
			}
			st.push_back(c);
			ans.push_back(st);
		}
	}
	for (auto it : ans) {
		cout << it;
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("G.in", "r", stdin);
		freopen("G.out", "w", stdout);
	#else
	
	#endif
	getline(cin, s);
	solve();
	return 0;
}