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
	const int MAXN = 1e5;
#endif

int n;

void gen(ofstream &out) {
	int n = 5, m = 5;
	int maxcoord = 10;
	int maxc = 10;
	out << n << ' ' << m << '\n';
	for (int i = 0; i < n; i++) {
		out << rand() % maxcoord << ' ' << rand() % maxc + 1 << '\n';
	}
	for (int i = 0; i < m; i++) {
		out << rand() % maxcoord << ' ' << 0 << '\n';
	}
	out.close();
}

signed main() {
	int maxtest = 100;
	system("g++ -DDEBUG -o B -std=c++11 B.cpp");
	system("g++ -DDEBUG -o Bs -std=c++11 Bs.cpp");
	while (maxtest--) {
		ofstream out("B.in");
		gen(out);
		if (system("./B")) {
			break;
		}
		system("./Bs");
		ifstream in1("B.out"), in2("Bs.out");
		int ans1, ans2;
		while (in1 >> ans1) {
			in2 >> ans2;
			if (ans1 != ans2) {
				cout << "WA";
				return 0;
			}
		}
		cout << "OK\n";
	}
	return 0;
}