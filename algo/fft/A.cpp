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
	const int MAXN = 1 << 3;
#else
	const int MAXN = 1 << 20;
#endif

string a, b;

void fft(vector<complex<double>> &a, vector<complex<double>> &ans, int n, complex<double> z, int abg, int ast, int ansbg) {
	if (n == 1) {
		ans[ansbg] = a[abg];
		return;
	}
	fft(a, ans, n >> 1, z * z, abg, ast * 2, ansbg);
	fft(a, ans, n >> 1, z * z, abg + ast, ast * 2, ansbg + n / 2);
	complex<double> x = 1;
	for (int i = 0; i < (n >> 1); i++) {
		complex<double> ans1 = ans[ansbg + i];		
		complex<double> ans2 = ans[ansbg + i + n / 2];
		ans[ansbg + i] = ans1 + x * ans2;
		ans[ansbg + i + n / 2] = ans1 - x * ans2;
		x *= z;
	}
}

inline void init() {

}

inline void solve() {
	init();
	bool minus = 0;
	if (a[0] == '-') {
		minus ^= 1;
		reverse(a.begin(), a.end());
		a.pop_back();
		reverse(a.begin(), a.end());
	}
	if (b[0] == '-') {
		minus ^= 1;
		reverse(b.begin(), b.end());
		b.pop_back();
		reverse(b.begin(), b.end());
	}
	vector<complex<double>> _a(MAXN), _b(MAXN);
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	while (a.size() < MAXN) a.push_back('0');
	while (b.size() < MAXN) b.push_back('0');
	for (int i = 0; i < MAXN; i++) {
		_a[i] = complex<double>((i < a.size() ? a[i] : '0') - '0');
		_b[i] = complex<double>((i < b.size() ? b[i] : '0') - '0');
	}
	vector<complex<double>> ans_a(MAXN), ans_b(MAXN);
	fft(_a, ans_a, MAXN, complex<double>(cos(2 * atan2(0, -1) / MAXN), sin(2 * atan2(0, -1) / MAXN)), 0, 1, 0);
	fft(_b, ans_b, MAXN, complex<double>(cos(2 * atan2(0, -1) / MAXN), sin(2 * atan2(0, -1) / MAXN)), 0, 1, 0);
	vector<complex<double>> _c(MAXN), ans_c(MAXN);
	for (int i = 0; i < MAXN; i++) {
		_c[i] = ans_a[i] * ans_b[i];
	}
	fft(_c, ans_c, MAXN, complex<double>(cos(-2 * atan2(0, -1) / MAXN), sin(-2 * atan2(0, -1) / MAXN)), 0, 1, 0);
	string ans;
	int cur = 0;
	for (int i = 0; i < MAXN || cur; i++) {
		if (i < MAXN) {
			ans_c[i] /= MAXN;
			cur += (int) (ans_c[i].real() + 0.5);
		}
		ans.push_back(cur % 10 + '0');
		cur /= 10;
	}
	while (ans.size() > 1 && ans.back() == '0') {
		ans.pop_back();
	}
	reverse(ans.begin(), ans.end());
	if (minus) {
		cout << '-';
	}
	cout << ans;
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("A.in", "r", stdin);
		freopen("A.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> a >> b)
		solve();
	return 0;
}