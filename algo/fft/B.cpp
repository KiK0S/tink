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
	const int MAXN = 1 << 5;
#else
	const int MAXN = 1 << 21;
#endif
typedef complex<double> cx;
string s, t;



void fft(vector<cx> &a, vector<cx> &ans, int n, cx z, int abg, int ast, int ansbg) {
	if (n == 1) {
		ans[ansbg] = a[abg];
		return;
	}
	fft(a, ans, n / 2, z * z, abg, ast * 2, ansbg);
	fft(a, ans, n / 2, z * z, abg + ast, ast * 2, ansbg + n / 2);
	cx x = 1;
	for (int i = 0; i < n / 2; i++) {
		cx ans1 = ans[ansbg + i];
		cx ans2 = ans[ansbg + i + n / 2];
		ans[ansbg + i] = ans1 + x * ans2;
		ans[ansbg + i + n / 2] = ans1 - x * ans2;
		x *= z;
	}
}

void multiply(vector<cx> &a, vector<cx> &b, vector<cx> &ans) {
	vector<cx> a_res(MAXN), b_res(MAXN);
	fft(a, a_res, MAXN, cx(cos(2 * atan2(0, -1) / MAXN), sin(2 * atan2(0, -1) / MAXN)), 0, 1, 0);
	fft(b, b_res, MAXN, cx(cos(2 * atan2(0, -1) / MAXN), sin(2 * atan2(0, -1) / MAXN)), 0, 1, 0);
	vector<cx> c(MAXN);
	for (int i = 0; i < MAXN; i++) {
		c[i] = a_res[i] * b_res[i];
	}
	fft(c, ans, MAXN, cx(cos(-2 * atan2(0, -1) / MAXN), sin(-2 * atan2(0, -1) / MAXN)), 0, 1, 0);
	for (int i = 0; i < MAXN; i++) {
		ans[i] /= MAXN;
	}
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << round(a[i].real()) << '\t';
	// }
	// cerr << '\n';
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << round(b[i].real()) << '\t';
	// }
	// cerr << '\n';
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << round(ans[i].real()) << '\t';
	// }
	// cerr << '\n';
	// cerr << '\n';
}


inline void init() {

}

map<char, string> dct = {
	{'0', "0000"},
	{'1', "0001"},
	{'2', "0010"},
	{'3', "0011"},
	{'4', "0100"},
	{'5', "0101"},
	{'6', "0110"},
	{'7', "0111"},
	{'8', "1000"},
	{'9', "1001"},
	{'A', "1010"},
	{'B', "1011"},
	{'C', "1100"},
	{'D', "1101"},
	{'E', "1110"},
	{'F', "1111"},
};

inline void solve() {
	init();
	string ns = "";
	int n = s.size(), k = t.size();
	for (auto c : s) {
		ns += dct[c];
	}
	// cerr << t << '\n' << ns << '\n';
	// reverse(t.begin(), t.end());
	vector<cx> a(MAXN);
	vector<cx> b(MAXN);
	for (int i = 0; i < ns.size(); i++) {
		a[i] = cx(ns[i] == '0' ? -1 : 1);
	}
	int cz = 0;
	for (int i = 0; i < t.size(); i++) {
		int x;
		if (t[i] == '1') {
			x = 1;
		}
		if (t[i] == '0') {
			x = -1;
		}
		if (t[i] == '?') {
			x = 0;
			cz++;
		}
		// cerr << x << ' ' <<  round(cx(x).real()) << '\n';
		b[MAXN / 2 - 1 - i] = cx(x);
	}
	vector<cx> ans_1(MAXN);
	// vector<cx> ans_2(MAXN);
	// vector<cx> ans_3(MAXN);
	multiply(a, b, ans_1);
	// for (int i = 0; i < t.size(); i++) {
	// 	int x;
	// 	if (t[i] == '1') {
	// 		x = 1;
	// 	}
	// 	if (t[i] == '0') {
	// 		x = -1;
	// 	}
	// 	if (t[i] == '?') {
	// 		x = 1;
	// 	}
	// 	b[MAXN / 2 - 1 - i] = cx(x);
	// }
	// multiply(a, b, ans_2);
	// for (int i = 0; i < t.size(); i++) {
	// 	int x;
	// 	if (t[i] == '1') {
	// 		x = 1;
	// 	}
	// 	if (t[i] == '0') {
	// 		x = -1;
	// 	}
	// 	if (t[i] == '?') {
	// 		x = -1;
	// 	}
	// 	b[MAXN / 2 - 1 - i] = cx(x);
	// }
	// multiply(a, b, ans_3);
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << (int)(ans_1[i].real() + 0.5) << ' ';
	// }
	// cerr << '\n';
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << (int)(ans_2[i].real() + 0.5) << ' ';
	// }
	// cerr << '\n';
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << (int)(ans_3[i].real() + 0.5) << ' ';
	// }
	// cerr << '\n';
	int cur = MAXN / 2 - 1;
	for (int i = 0; i < (n / 2 - k / 8 + 1); i++) {
		// cerr << k << ' ' << round(ans_1[cur].real()) << ' ' << cz << '\n'; 
		int pos = (k + round(ans_1[cur].real()) - cz) / 2;
		cout << pos + cz << ' ';
		cur += 8;
	}
}

signed main() {
	#ifdef DEBUG
		freopen("B.in", "r", stdin);
		freopen("B.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> s >> t)
		solve();
	return 0;
}