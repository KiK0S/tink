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
	const int MAXN = 1e6;
#else
	const int MAXN = 1e6;
#endif

string s;
int N, n;
int prev_white[MAXN];
int next_black[MAXN];

inline void init() {
	memset(prev_white, -1, sizeof(prev_white));
	for (int i = 0; i < MAXN; i++) {
		next_black[i] = 1e9;
	}
}

int get(int block_size) {
	n = s.size() / block_size * (block_size + 1);
	int min_right = 1e9;
	int max_left = -1;
	for (int i = 0; i < n; i+= block_size) {
		int l = i;
		int r = i + block_size - 1;
		int left_black = next_black[l];
		left_black = min(left_black, r + 1);
		int right_white = prev_white[r];
		right_white = max(right_white, l);
		if (left_black < right_white) {
			return -1;
		}
		min_right = min(min_right, left_black - i + 1);
		max_left = max(max_left, right_white - i + 1);
	}
	if (min_right <= max_left) {
		return -1;
	}
	return block_size - max_left;
}

inline void solve() {
	init();
	N = s.size();
	int ans = -1;
	int block_size = 0;
	for (int i = 0; i < MAXN; i++) {
		if (i >= N) {
			prev_white[i] = prev_white[i - 1];
			continue;
		}
		if (s[i] == '0') {
			prev_white[i] = i;
		}
		else if (i != 0) {
			prev_white[i] = prev_white[i - 1];
		}
	}
	for (int i = N - 1; i >= 0; i--) {
		if (s[i] == '1') {
			next_black[i] = i;
		}
		else if (i != N - 1) {
			next_black[i] = next_black[i + 1];
		}
	}
	for (int i = 1; i <= N; i++) {
		int res = get(i);
		if (res == -1) {
			continue;
		}
		int cur = N / i * res;
		cur += max(0, N % i - i + res); 
		if (ans < cur) {
			ans = cur;
			block_size = i;
		}
	}
	if (ans == -1) {
		cout << "-1\n";
		return;
	}
	int cntwhite = block_size - get(block_size);
	for (int i = 0; i < N; i++) {
		if (i % block_size < cntwhite) {
			cout << '0';
		}
		else {
			cout << '1';
		}
	}
	cout << '\n';
}

signed main() {
	#ifdef DEBUG
		freopen("F.in", "r", stdin);
		freopen("F.out", "w", stdout);
	#else
	
	#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> s)
		solve();
	return 0;
}