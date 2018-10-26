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

int n;

inline void init(ofstream &out) {
	n = 15;
	vector<int> a(n, -1);
	for (int i = 1; i < n; i++) {
		a[i] = rand() % i;
	}
	out << n << '\n';
	vector<vector<int>> nxt(n);
	for (int i = 0; i < n; i++) {
		if (a[i] != -1) {
			nxt[a[i]].push_back(i);
		}
	}
	for (int i = 0; i < n; i++) {
		out << nxt[i].size() << ' ';
		for (auto it : nxt[i]) {
			out << it + 1 << ' ';
		}
		out << '\n';
	}
	out.close();
}

signed main() {
	system("g++ -DDEBUG -std=c++14 -fsanitize=undefined -fsanitize=bounds -fsanitize=address -o A A.cpp");
	system("g++ -DDEBUG -std=c++14 -fsanitize=undefined -fsanitize=bounds -fsanitize=address -o As As.cpp");
	for (int i = 0; i < 100; i++) {
		ofstream out("A.in");
		init(out);
		system("./As");
		system("./A");
		ifstream in1("A.out");
		ifstream in2("As.out");
		for (int j = 0; j < n; j++) {
			int a1, a2;
			in1 >> a1, in2 >> a2;
			if (a1 != a2) {
				cout << "WA" << endl;
				return 0;
			}
		}
		cout << "OK" << endl;
	}

	return 0;
}