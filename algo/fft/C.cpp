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
	const int MAXN = 1 << 16;
#else
	const int MAXN = 1 << 16;
#endif


typedef int cx;

const cx mod = 786433;
int g, gr;


int mm(int a) {
	if (a < mod) {
		return a;
	}
	if (a < (mod << 1)) {
		return a - mod;
	}
	return a % mod;
}

int mm(ll a) {
	if (a < 0) {
		a += mod;
	}
	if (a < mod) {
		return a;
	}
	if (a < (mod << 1)) {
		return a - mod;
	}
	return a % mod;
}

cx bp(cx a, int N) {
	if (N == 0) {
		return 1;
	}
	if (N % 2 == 1) {
		return mm(1ll * a * (bp(a, N - 1)));
	}
	return bp(mm(1ll * a * a), N / 2);
}


inline void fft(vector<cx> &a, vector<cx> &ans, int n, cx z, int abg, int ast, int ansbg) {
	if (n == 1) {
		ans[ansbg] = a[abg];
		return;
	}
	fft(a, ans, n / 2, mm(1ll * z * z), abg, ast * 2, ansbg);
	fft(a, ans, n / 2, mm(1ll * z * z), abg + ast, ast * 2, ansbg + n / 2);
	cx x = 1;
	for (int i = 0; i < n / 2; i++) {
		cx ans1 = ans[ansbg + i];
		cx ans2 = ans[ansbg + i + n / 2];
		ans[ansbg + i] = mm(ans1 + 1ll * x * ans2);
		ans[ansbg + i + n / 2] = mm(ans1 - (1ll * x * ans2) % mod);
		x = mm(1ll * x * z);
	}
}

vector<cx> a_res, b_res, c;

void multiply(vector<cx> &a, vector<cx> &b, vector<cx> &ans) {
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << a[i] << ' ';
	// }
	// cerr << '\n';
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << b[i] << ' ';
	// }
	// cerr << '\n';
	fft(a, a_res, MAXN, cx(g), 0, 1, 0);
	fft(b, b_res, MAXN, cx(g), 0, 1, 0);
	for (int i = 0; i < MAXN; i++) {
		c[i] = mm(1ll * a_res[i] * b_res[i]);
	}
	fft(c, ans, MAXN, gr, 0, 1, 0);
	int mp = bp(MAXN, mod - 2);
	for (int i = 0; i < MAXN; i++) {
		ans[i] = mm(1ll * ans[i] * mp);
	}
	// for (int i = 0; i < MAXN; i++) {
	// 	cerr << ans[i] << ' ';
	// }
	// cerr << '\n';
}

const int MAXH = 17;
vector<cx> q[MAXH];
vector<int> divisors;

inline void init() {
	for (int i = 0; i < MAXH; i++) {
		q[i].resize(MAXN, cx(0));
	}
	a_res.resize(MAXN), b_res.resize(MAXN), c.resize(MAXN);
	q[0][0] = cx(1);
	// for (int i = 0; i < 16; i++) {
	// 		// divisors.push_back(3 * bp(2, i));
	// 	divisors.push_back(bp(2, i));
	// }
}
int n, h;

bool check() {
	for (auto it : divisors) {
		if (bp(g, it) == 1) {
			return 0;
		}
	}
	if (bp(g, MAXN) != 1) {
		return 0;
	}
	return 1;
}


inline void solve() {
	init();
	// for (g = 2; g < mod; g++) {
	// 	if (check()) {
	// 		break;
	// 	}
	// }
	g = 3;
	gr = bp(g, mod - 2);
	// cerr << g << '\n';
	// cerr << "here\n";
	// g = bp(5, 4);
	vector<cx> similar(MAXN), diff(MAXN);
	for (int i = 1; i < MAXH; i++) {
		multiply(q[i - 1], q[i - 1], similar);
		if (i > 1) multiply(q[i - 1], q[i - 2], diff);
		for (int j = 0; j + 1 < MAXN; j++) {
			q[i][j + 1] = mm(similar[j] + diff[j] + diff[j]);
		}
		// for (int j = 0; j < MAXN; j++) {
		// 	cerr << q[i][j] << ' ';
		// }
		// cerr << '\n';
	}
	cout << q[h + 1][n] << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("C.in", "r", stdin);
		freopen("C.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> h)
		solve();
	return 0;
}