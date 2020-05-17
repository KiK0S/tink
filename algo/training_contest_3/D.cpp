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
	const int MAXN = 15;
#else
	const int MAXN = 2e6;
#endif

int n, m;
deque<deque<int>> v;

inline void init() {

}

void merge(deque<int> &a, deque<int> &b) { // b -> a
	if (a.size() >= b.size()) {
		while (b.size()) {
			cerr << "! " << b.back() << '\n';
			a.push_back(b.back());
			b.pop_back();
		}
	}
	else {
		while(a.size()) {
			cerr << "? " << a.back() << '\n';
			b.push_front(a.back());
			a.pop_back();
		}
	}
}

inline void solve() {
	init();
	for (int i = 0; i < n; i++) {
		int a = i + 1;
		v.push_back(deque<int>());
		v.back().push_back(a);
	}
	bool rev = 0;
	while (m--) {
		if (!rev) {
			auto it = v.begin();
			while (it != v.end()) {
				for (auto val : *it) {
					cerr << val << ' ';
				}
				cerr << '\n';
				it++;
			}
		}
		else {
			auto it = v.rbegin();
			while (it != v.rend()) {
				for (auto val : *it) {
					cerr << val << ' ';
				} 
				cerr << '\n';
				it++;
			}
		}
		cerr << '\n';
		int a;
		cin >> a;
		if (a * 2 <= v.size()) {
			if (!rev) {
				cerr << "a\n";
				auto itl = v.begin();
				auto itr = v.begin();
				for (int i = 0; i < a; i++) {
					itl++;
					itr++;
				}
				itl--;
				for (int i = 0; i < a; i++) {
					merge(*itl, *itr);
					// (*itr).swap(*itl);
					itl--;
					itr++;
				}
				for (int i = 0; i < a; i++) {
					v.pop_front();
				}
				rev = 1;
			}
			else {
				cerr << "b\n";
				auto itl = v.rbegin();
				auto itr = v.rbegin();
				for (int i = 0; i < a; i++) {
					itl++;
					itr++;
				}
				itr--;
				for (int i = 0; i < a; i++) {
					merge(*itl, *itr);
					itl++;
					itr--;
				}
				for (int i = 0; i < a; i++) {
					v.pop_back();
				}
				rev = 0;
			}
		}
		else {
			a = v.size() - a;
			cerr << a << '\n';
			rev ^= 1;
			if (!rev) {
				cerr << "c\n";
				auto itl = v.begin();
				auto itr = v.begin();
				for (int i = 0; i < a; i++) {
					itl++;
					itr++;
				}
				itl--;
				for (int i = 0; i < a; i++) {
					merge(*itr, *itl);
					itl--;
					itr++;
				}
				for (int i = 0; i < a; i++) {
					v.pop_front();
				}
				rev = 1;
			}
			else {
				cerr << "d\n";
				auto itl = v.rbegin();
				auto itr = v.rbegin();
				for (int i = 0; i < a; i++) {
					itl++;
					itr++;
				}
				itr--;
				for (int i = 0; i < a; i++) {
					merge(*itl, *itr);
					itl++;
					itr--;
				}
				for (int i = 0; i < a; i++) {
					v.pop_back();
				}
				rev = 0;
			}
		}
	}
	if (!rev) {
			auto it = v.begin();
			while (it != v.end()) {
				for (auto val : *it) {
					cerr << val << ' ';
				}
				cerr << '\n';
				it++;
			}
		}
		else {
			auto it = v.rbegin();
			while (it != v.rend()) {
				for (auto val : *it) {
					cerr << val << ' ';
				} 
				cerr << '\n';
				it++;
			}
		}
		cerr << '\n';
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
	while (cin >> n >> m)
		solve();
	return 0;
}