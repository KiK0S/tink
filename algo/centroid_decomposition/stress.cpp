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
	n = rand() % 5 + 2;
	out << n << '\n';
	map<int, set<char>> pre;
	for (int i = 2; i <= n; i++) {
		int p = rand() % (i - 1) + 1;
		char c = rand() % 6 + 'a';
		while (pre[p].count(c)) {
			c++;
		}
		pre[p].insert(c);
		out << p << ' ' << i << ' ' << c << '\n';
	}
	out.close();
}

signed main() {
	int test = 100;
	for (int i = 0; i < test; i++) {
		ofstream out("F.in");
		gen(out);
		system("./F");
		system("./Fs");
		ifstream in1("F.out"), in2("Fs.out");
		int a1, a2, b1, b2;
		in1 >> a1 >> a2;
		in2 >> b1 >> b2;
		in1.close();
		in2.close();
		if (a1 != b1 || a2 != b2) {
			cout << "WA\n";
			return 1;
		}
		cout << "OK\n";
	}
	return 0;
}