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
	n = 1000;
	out << n << ' ' << rand() % 100 << ' ' << rand() % 100 << ' ' << rand() % 100 << ' ' << rand() % 100 << ' ' << rand() % 100 << '\n';
	out.close();
}

signed main() {
	int test = 100;
	system("bld A");
	system("bld As");
	for (int i = 0; i < test; i++) {
		ofstream out("A.in");
		gen(out);
		if (system("./A") || system("./As")) {
			break;
		}
		ifstream in1("A.out"), in2("As.out");
		ll a1, a2;
		in1 >> a1;
		in2 >> a2;
		if (a1 != a2) {
			cout << "WA\n";
		}
		else {
			cout << "OK\n";
		}
	}
	return 0;
}