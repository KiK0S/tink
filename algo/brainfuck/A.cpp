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
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#ifdef DEBUG
	const int MAXN = 10;
	const int MAXLOG = 4;
	const int MAXSQRT = 4;
#else
	const int MAXN = 3e5;
	const int MAXLOG = 20;
	const int MAXSQRT = 400;
	#define cerr if (false) cerr
#endif

mt19937 rng(time(0));

const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;

string ans;
const int BLOCK_SIZE = 10;

void read();
void go_left(int cnt);
void go_right(int cnt);
void copy_single(int cnt);
void copy_segment(int cnt);
void addition(int delta);
void substraction(int delta);
void start_cycle();
void end_cycle();
void single_substraction(int cnt);
void single_addition(int cnt);
void print();
void next_block();
void prev_block();

void read() {
	ans += ">";
	ans += ",";
	ans += ">>++++++++++";
	ans += "[-<<->>]";
	ans += "<<<->";
	ans += "[<+>>>]";
	ans += "<<";
	ans += "--------------------------------------";
	ans += ">";
	ans += "[->++++++++++<]";
	ans += ">";
	ans += "[-<+>]";
	ans += "<<";
	ans += "[->+<]";
	ans += "<";
}

void print() {
	ans.push_back('.');
}

void go_left(int cnt) {
	while (cnt--) {
		ans.push_back('<');
	}
}

void go_right(int cnt) {
	while (cnt--) {
		ans.push_back('>');
	}
}

void single_addition(int cnt) {
	while (cnt--) {
		ans.push_back('+');
	}
}

void single_substraction(int cnt) {
	while (cnt--) {
		ans.push_back('-');
	}
}

void copy_single(int cnt) {
	start_cycle();
	if (cnt > 0) {
		go_right(cnt);
	}
	else {
		go_left(-cnt);
	}
	single_addition(1);
	if (cnt > 0) {
		go_left(cnt);
	}
	else {
		go_right(-cnt);
	}
	single_substraction(1);
	end_cycle();
}

void copy_segment(int cnt) {
	start_cycle();
	if (cnt > 0) {
		for (int i = 0; i < cnt; i++) {
			go_right(1);
			single_addition(1);
		}
		go_left(cnt);
	}
	else {
		for (int i = 0; i < -cnt; i++) {
			go_left(1);
			single_addition(1);
		}
		go_right(-cnt);	
	}
	single_substraction(1);
	end_cycle();
}

void addition(int delta) {
	start_cycle();
	if (delta > 0) {
		go_right(delta);
	}
	else {
		go_left(-delta);
	}
	single_addition(1);
	if (delta > 0) {
		go_left(delta);
	}
	else {
		go_right(-delta);
	}
	single_substraction(1);
	end_cycle();
}

void substraction(int delta) {
	start_cycle();
	if (delta > 0) {
		go_right(delta);
	}
	else {
		go_left(-delta);
	}
	single_substraction(1);
	if (delta > 0) {
		go_left(delta);
	}
	else {
		go_right(-delta);
	}
	single_substraction(1);
	end_cycle();
}

void next_block() {
	go_right(BLOCK_SIZE);
}

void prev_block() {
	go_left(BLOCK_SIZE);
}

void start_cycle() {
	ans.push_back('[');
}

void end_cycle() {
	ans.push_back(']');
}

inline void init() {

}

inline void solve() {
	init();
	read();
	next_block();
	read();
	prev_block();
	copy_segment(2);
	go_right(2);
	copy_single(-2);
	go_left(1);
	copy_single(BLOCK_SIZE);
	go_left(1);
	next_block();
	addition(1);
	go_right(1);
	copy_single(-1);
	go_left(-1);
	print();
	cout << ans << '\n';
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
	solve();
	return 0;
}