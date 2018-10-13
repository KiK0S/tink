#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 5;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
#endif

#define int long long

string s;
int n;

int h[MAXN];
int hr[MAXN];
int tpow[MAXN];
int t = 179;
int p = 1e9 + 9;

int get(int l, int r) {
	return ((h[r] - (((l == 0 ? 0ll : h[l - 1]) * tpow[r - l + 1]) % p)) % p + p) % p;
}

int getr(int l, int r) {
	return ((hr[l] - (((r == n - 1 ? 0ll : hr[r + 1]) * tpow[r - l + 1]) % p)) % p + p) % p;
}

void solve() {
	int n = s.size();
	tpow[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		tpow[i] = tpow[i - 1] * t;
		tpow[i] %= p;
	}
	for (int i = 0; i < n; i++) {
		h[i] = (i == 0 ? 0ll : h[i - 1]) * t + (s[i] - 'a' + 1);
		h[i] %= p;
	}
	for (int i = n - 1; i >= 0; i--) {
		hr[i] = (i == n - 1 ? 0ll : hr[i + 1]) * t + (s[i] - 'a' + 1);
		hr[i] %= p;
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int l = 0;
		int r = n + 1;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (i - mid < 0 || i + mid >= n) {
				r = mid;
				continue;
			}
			if (get(i - mid, i - 1) == getr(i + 1, i + mid)) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		ans += l;
	}
	for (int i = 0; i < n; i++) {
		int l = 0;
		int r = n + 1;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (i - mid + 1 < 0 || i + mid >= n) {
				r = mid;
				continue;
			}
			if (get(i - mid + 1, i) == getr(i + 1, i + mid)) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		ans += l;
	}
	cout << ans << '\n';
}

signed main() {
	#ifdef DEBUG 
		freopen("H.in", "r", stdin);
		freopen("H.out", "w", stdout);
	#else
		freopen("palindrome.in", "r", stdin);
		freopen("palindrome.out", "w", stdout);	
	#endif	
	while (cin >> s)	
		solve();
	return 0;
}