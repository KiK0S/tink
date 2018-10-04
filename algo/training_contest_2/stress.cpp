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

void gen(ofstream &out) {
	int n = 10, m = 10;
	out << n << ' ' << m << '\n';
	for (int i = 0; i < n; i++) {
		out << rand() % 10 + 1 << ' ';
	}
	out << '\n';
	for (int i = 0; i < m; i++) {
		int x = rand() % 4;
		if (!x) {
			out << "t\n";
		}
		else {
			if (x == 1) {
				out << "c ";
			}
			if (x == 2) {
				out << "a ";
			}
			if (x == 3) {
				out << "r ";
			}
			out << rand() % 10 + 1 << '\n';
		}
	}
	out.close();
}

signed main() {
	int tests = 10000;
	system("bld C");
	system("bld CS");
	for (int i = 0; i < tests; i++) {
		ofstream out("C.in");
		gen(out);
		system("./C");
		system("./CS");
		ifstream in1("C.out"), in2("CS.out");
		int a, b;
		while (in1 >> a) {
			in2 >> b;
			if (a != b) {
				cout << "WA\n";
				return 0;
			}
		}
		cout << "OK\n";
	}
	return 0;
}