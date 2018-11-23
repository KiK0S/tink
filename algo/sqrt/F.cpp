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

#ifdef DEBUG
	const int MAXN = 10;
#else
	const int MAXN = 5e5;
#endif

int n;

const int K = 2500;

struct Block {
	int l, r;
	bool rev = 0;
	bool srt = 0;
	int push = -1;
	vector<int> sorted;
	vector<int> val;
};

typedef Block * block; 

vector<block> a;

void push(block v, bool r = 1, bool s = 1) {
	if (v->push != -1) {
		fill(v->val.begin(), v->val.end(), v->push);
		v->push = -1;
	}
	if (r && v->rev == 1) {
		reverse(v->val.begin(), v->val.end());
		v->rev = 0;
	}
	if (s && v->srt == 0) {
		v->sorted = v->val;
		sort(v->sorted.begin(), v->sorted.end());
		v->srt = 1;
	}
}

int get(int l, int r, int x) {
	int ans = 0;
	// cerr << l << ' ' << r << '\n';
	for (auto it : a) {
		// push(it);
		// cerr << "block " << it->l << ' ' << it->r << '\n';
		// for (auto c : it->val) {
		// 	cerr << c << ' ';
		// }
		// cerr << '\n';
		if (l <= it->l && it->r <= r) {
			if (it->push != -1) {
				if (it->push >= x) {
					ans += it->r - it->l + 1;
				}
			}
			else {
				push(it, 0, 1);
				ans += it->sorted.end() - upper_bound(it->sorted.begin(), it->sorted.end(), x - 1);
			}
			continue;
		}
		// cerr << it->l << ' ' << it->r << ' ' << l << ' ' << r << '\n';

		if (max(it->l, l) <= min(it->r, r) || it->l <= l && r <= it->r) {
			// cerr << it->l << ' ' << it->r << ' ' << l << ' ' << r << '\n';
			push(it, 1, 0);
			int cur = it->l;
			for (auto c : it->val) {
				if (l <= cur && cur <= r) {
					if (c >= x) {
						ans++;
					}
				}
				cur++;
			}
		}
	}
	// cerr << '\n';
	return ans;
}

void updidx() {
	int cur = 0;
	for (auto it : a) {
		// push(it);
		it->l = cur;
		it->r = it->l + it->val.size() - 1;
		cur = it->r + 1;
	}
}

void reverse(int l, int r) {
	block A = new Block(), B = new Block();
	vector<block> nw;
	int _l = -1;
	int _r = -1;
	for (auto it : a) {
		// push(it);
		if (it->l <= l && r <= it->r) {
			// cerr << "1 " << it->l << ' ' << it->r << '\n';
			push(it, 1, 0);
			A->l = it->l;
			A->r = l - 1;
			A->val.resize(A->r - A->l + 1);
			copy(it->val.begin(), it->val.begin() + A->val.size(), A->val.begin());
			B->l = r + 1;
			B->r = it->r;
			B->val.resize(B->r - B->l + 1);
			copy(it->val.end() - B->val.size(), it->val.end(), B->val.begin());
			vector<int> tmp(r - l + 1);
			copy(it->val.begin() + A->val.size(), it->val.end() - B->val.size(), tmp.begin());
			it->l = l;
			it->r = r;
			it->val = tmp;
			A->srt = 0;
			B->srt = 0;
			it->srt = 0;
			it->rev ^= 1;
			nw.push_back(A);
			_l = nw.size();
			_r = nw.size();
			nw.push_back(it);
			nw.push_back(B);
			continue;
		}
		if (l <= it->l && it->r <= r) {
			// cerr << "2 " << it->l << ' ' << it->r << '\n';
			// push(it);
			it->rev ^= 1;
			if (_l == -1) {
				_l = nw.size();
			}
			_r = nw.size();
		}
		else if (l <= it->l && it->l <= r) {
			// cerr << "3 " << it->l << ' ' << it->r << '\n';
			push(it, 1, 0);
			A->l = it->l;
			A->r = r;
			A->val.resize(A->r - A->l + 1);
			copy(it->val.begin(), it->val.begin() + A->val.size(), A->val.begin());
			vector<int> tmp(it->r - A->r);
			copy(it->val.begin() + A->val.size(), it->val.end(), tmp.begin());
			it->val = tmp;
			it->l = r + 1;
			A->rev ^= 1;
			it->srt = 0;
			A->srt = 0;
			if (_l == -1) {
				_l = nw.size();
			}
			_r = nw.size();
			nw.push_back(A);
		}
		else if (l <= it->r && it->r <= r) {
			// cerr << "4 " << it->l << ' ' << it->r << '\n';
			push(it, 1, 0);
			B->l = l;
			B->r = it->r;
			B->val.resize(B->r - B->l + 1);
			copy(it->val.end() - B->val.size(), it->val.end(), B->val.begin());
			vector<int> tmp(B->l - it->l);
			copy(it->val.begin(), it->val.end() - B->val.size(), tmp.begin());
			it->r = l - 1;
			it->val = tmp;
			B->rev ^= 1;
			it->srt = 0;
			B->srt = 0;
			nw.push_back(it);
			if (_l == -1) {
				_l = nw.size();
			}
			_r = nw.size();
			nw.push_back(B);
			continue;
		}
		nw.push_back(it);
	}
	a.swap(nw);
	reverse(a.begin() + _l, a.begin() + _r + 1);
	// for (auto it : a) {
	// 	push(it);
	// 	cerr << "block " << it->l << ' ' << it->r << '\n';
	// 	for (auto c : it->val) {
	// 		cerr << c << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	// cerr << '\n';
	updidx();
}

#define set SET
void set(int l, int r, int x) {
	block A = new Block(), B = new Block();
	vector<block> nw;
	for (auto it : a) {
		// push(it);
		if (it->l <= l && r <= it->r) {
			// cerr << it->l << ' ' << it->r << '\n';
			push(it, 1, 0);
			A->l = it->l;
			A->r = l - 1;
			A->val.resize(A->r - A->l + 1);
			copy(it->val.begin(), it->val.begin() + A->val.size(), A->val.begin());
			B->l = r + 1;
			B->r = it->r;
			B->val.resize(B->r - B->l + 1);
			copy(it->val.end() - B->val.size(), it->val.end(), B->val.begin());
			it->l = l;
			it->r = r;
			it->val.resize(it->r - it->l + 1);
			fill(it->val.begin(), it->val.end(), x);
			A->srt = 0;
			B->srt = 0;
			it->srt = 0;
			nw.push_back(A);
			nw.push_back(it);
			nw.push_back(B);
			continue;
		}
		if (l <= it->l && it->r <= r) {
			// cerr << it->l << ' ' << it->r << '\n';
			// push(it);
			it->push = x;
			// it->val.assign(it->r - it->l + 1, x);
			it->srt = 0;
		}
		else if (l <= it->l && it->l <= r) {
			// cerr << it->l << ' ' << it->r << '\n';
			push(it, 1, 0);
			A->l = it->l;
			A->r = r;
			A->val.assign(A->r - A->l + 1, x);
			A->srt = 0;
			vector<int> tmp(it->r - A->r);
			copy(it->val.begin() + A->val.size(), it->val.end(), tmp.begin());
			it->val = tmp;
			it->l = r + 1;
			it->srt = 0;
			nw.push_back(A);
		}
		else if (l <= it->r && it->r <= r) {
			// cerr << it->l << ' ' << it->r << '\n';
			push(it, 1, 0);
			B->l = l;
			B->r = it->r;
			B->val.assign(B->r - B->l + 1, x);
			vector<int> tmp(B->l - it->l);
			copy(it->val.begin(), it->val.end() - B->val.size(), tmp.begin());
			it->r = l - 1;
			it->srt = 0;
			B->srt = 0;
			it->val = tmp;
			nw.push_back(it);
			nw.push_back(B);
			continue;
		}
		nw.push_back(it);
	}
	a.swap(nw);
	// for (auto it : a) {
	// 	cerr << "!block " << it->l << ' ' << it->r << '\n';
	// 	for (auto c : it->val) {
	// 		cerr << c << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	// cerr << '\n';
	updidx();
	// for (auto it : a) {
	// 	cerr << "!block " << it->l << ' ' << it->r << '\n';
	// 	for (auto c : it->val) {
	// 		cerr << c << ' ';
	// 	}
	// 	cerr << '\n';
	// }
	// cerr << '\n';
}

vector<int> start;

void rebuild(bool have = 0) {
	if (!have) {
		int pnt = 0;
		for (auto it : a) {
			push(it, 1, 0);
			for (auto c : it->val) {
				start[pnt++] = c;
			}
			delete it;
			// it->val.clear();
			// it->sorted.clear();
		}
		// for (auto it : a) {
		// 	delete it;
		// }
		a.clear();
	}
	for (int i = 0; i < n; i++) {
		if (i % K == 0) {
			// int l = (a.size() == 0 ? 0 : a.back()->r + 1);
			a.push_back(new Block());
			// a.back()->l = l;
			// a.back()->r = l - 1;
		}
		// a.back()->r++;
		// a.back()->srt = 0;
		a.back()->val.push_back(start[i]);
	}
	updidx();
}

inline void solve() {
	// assert(n < 4e5);
	start.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> start[i];
	}
	rebuild(1);
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		// cerr << "query " << i << '\n';
		if (i % K == 0) {
			rebuild();
		}
		string a;
		cin >> a;
		if (a == "get") {
			int l, r, c;
			cin >> l >> r >> c;
			l--, r--;
			cout << get(l, r, c) << '\n';
		}
		if (a == "set") {
			int l, r, c;
			cin >> l >> r >> c;
			l--, r--;
			set(l, r, c);	
		}
		if (a == "reverse") {
			int l, r;
			cin >> l >> r;
			l--, r--;
			reverse(l, r);
		}
	}
	// rebuild();
	// for (auto it : a) {
	// 	for (auto c : it->val) {
	// 		cout << c << ' ';
	// 	}
	// }
	// cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n)
		solve();
	return 0;
}