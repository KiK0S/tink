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
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, t;
int a, b;

char query(vector<int> A, vector<int> B) {
	t--;
	if (t < 0) {
		assert(0);
	}
	cout << A.size() << ' ';
	for (auto it : A) {
		cout << it << ' ';
	}
	cout << endl;
	cout << B.size() << ' ';
	for (auto it : B) {
		cout << it << ' ';
	}
	cout << endl;
	char x;
	cin >> x;
	return x;
}

inline void init() {
	t--;
}

inline void solve1() {
	init();
	vector<int> id;
	for (int i = 1; i <= a + b; i++) {
		id.push_back(i);
	}
	while (id.size() > 1) {
		shuffle(id.begin(), id.end(), rng);	
		if (id.size() > 3) {
			vector<int> tmp;
			while (id.size() % 3 != 0) {
				tmp.push_back(id.back());
				id.pop_back();
			}
			vector<int> A, B, C;
			for (int i = 0; i < id.size() / 3; i++) {
				A.push_back(id[i]);
			}
			for (int i = id.size() / 3; i < 2 * id.size() / 3; i++) {
				B.push_back(id[i]);
			}
			for (int i = 2 * id.size() / 3; i < id.size(); i++) {
				C.push_back(id[i]);
			}
			id.clear();
			char c = query(A, B);
			if (c == '=') {
				for (auto it : C) {
					id.push_back(it);
				}
				for (auto it : tmp) {
					id.push_back(it);
				}
				continue;
			}
			for (auto it : A) {
				if (c == '>' && it > a || c == '<' && it <= a) {
					id.push_back(it);
				}
			}
			for (auto it : B) {
				if (c == '<' && it > a || c == '>' && it <= a) { 
					id.push_back(it);
				}
			}
			for (auto it : tmp) {
				id.push_back(it);
			}
		}
		else if (id.size() == 3) {
			sort(id.begin(), id.end());
			if (id[1] <= a) {
				char c = query({id[0]}, {id[1]});
				if (c == '=') {
					id = {id[2]};
				}
				else if (c == '>') {
					id = {id[1]};
				}
				else {
					id = {id[0]};
				}
			}
			else {
				char c = query({id[1]}, {id[2]});
				if (c == '=') {
					id = {id[0]};
				}
				else if (c == '>') {
					id = {id[1]};
				}
				else {
					id = {id[2]};
				}
			}
		}
		else {
			bool A = id[0] <= a;
			bool B = id[1] <= b;
			if ((A ^ B) == 0) {
				char c = query({id[0]}, {id[1]});
				if (c == '>' && A || c == '<' && !A) {
					id = {id[1]};
				}
				else {
					id = {id[0]};
				}
				continue;
			}
			int kek = 1;
			while (count(id.begin(), id.end(), kek) > 0) {
				kek++;
			}
			if (kek <= a) {
				if (A) {
					char c = query({kek}, {id[0]});
					if (c == '=') {
						id = {id[1]};
					}
					else {
						id = {id[0]};
					}
				}
				else {
					char c = query({kek}, {id[1]});
					if (c == '=') {
						id = {id[0]};
					}
					else {
						id = {id[1]};
					}
				}
			}
			else {
				if (!A) {
					char c = query({kek}, {id[0]});
					if (c == '=') {
						id = {id[1]};
					}
					else {
						id = {id[0]};
					}
				}
				else {
					char c = query({kek}, {id[1]});
					if (c == '=') {
						id = {id[0]};
					}
					else {
						id = {id[1]};
					}
				}	
			}
		}
	}
	cout << "0 " << id[0] << endl;
}

inline void solve() {
	init();
	vector<int> id;
	for (int i = 1; i <= a + b; i++) {
		id.push_back(i);
	}
	while (id.size() > 1) {
		// shuffle(id.begin(), id.end(), rng);
		sort(id.begin(), id.end());
		if (id.size() > 3) {
			vector<int> tmp;
			while (id.size() % 3 != 0) {
				tmp.push_back(id.back());
				id.pop_back();
			}
			vector<int> A, B, C;
			assert(id.size() % 3 == 0);
			for (int i = 0; i + 2 < id.size(); i += 3) {
				A.push_back(id[i]);
				B.push_back(id[i + 1]);
				C.push_back(id[i + 2]);
			}
			assert(A.size() + B.size() + C.size() == id.size());
			id.clear();
			char c = query(A, B);
			if (c == '=') {
				for (auto it : C) {
					id.push_back(it);
				}
				for (auto it : tmp) {
					id.push_back(it);
				}
				continue;
			}
			for (auto it : A) {
				if (c == '>' && it > a || c == '<' && it <= a) {
					id.push_back(it);
				}
			}
			for (auto it : B) {
				if (c == '<' && it > a || c == '>' && it <= a) { 
					id.push_back(it);
				}
			}
		}
		else if (id.size() == 3) {
			if (id[1] <= a) {
				char c = query({id[0]}, {id[1]});
				if (c == '=') {
					id = {id[2]};
				}
				else if (c == '>') {
					id = {id[1]};
				}
				else {
					id = {id[0]};
				}
			}
			else {
				char c = query({id[1]}, {id[2]});
				if (c == '=') {
					id = {id[0]};
				}
				else if (c == '>') {
					id = {id[1]};
				}
				else {
					id = {id[2]};
				}
			}
		}
		else {
			bool A = id[0] <= a;
			bool B = id[1] <= b;
			if ((A ^ B) == 0) {
				char c = query({id[0]}, {id[1]});
				if (c == '>' && A || c == '<' && !A) {
					id = {id[1]};
				}
				else {
					id = {id[0]};
				}
				continue;
			}
			int kek = 1;
			while (count(id.begin(), id.end(), kek) > 0) {
				kek++;
			}
			if (kek <= a) {
				if (A) {
					char c = query({kek}, {id[0]});
					if (c == '=') {
						id = {id[1]};
					}
					else {
						id = {id[0]};
					}
				}
				else {
					char c = query({kek}, {id[1]});
					if (c == '=') {
						id = {id[0]};
					}
					else {
						id = {id[1]};
					}
				}
			}
			else {
				if (!A) {
					char c = query({kek}, {id[0]});
					if (c == '=') {
						id = {id[1]};
					}
					else {
						id = {id[0]};
					}
				}
				else {
					char c = query({kek}, {id[1]});
					if (c == '=') {
						id = {id[0]};
					}
					else {
						id = {id[1]};
					}
				}	
			}
		}
	}
	cout << "0 " << id[0] << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b >> t;
	if (pow(3, t) == a + b)
		solve();
	else {
		solve1();
	}
	return 0;
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//