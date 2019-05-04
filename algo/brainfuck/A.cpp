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
const int BLOCK_SIZE = 8;

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
void clear_block();
void multiplication();
void division();

void read() {
    ans += ">>+[>,>>++++++++++[-<<->>]<<<->[<+>>>]>>+<<<<[-------------------------------------->>]>>[-<<]<[->++++++++++<]>[-<+>]<<[->+<]<]>>>>[-<<<<+>>>>]<<[-]>>>-<<<<<";
}

void clear_block() {
    for (int i = 1; i < BLOCK_SIZE; i++) {
        go_right(1);
        start_cycle();
        single_substraction(1);
        end_cycle();
    }
    go_left(BLOCK_SIZE - 1);
}

void print() {
    ans += ">>>>++++++++++<<<<[->+>>+>-[<-]<[->>+<<<<[->>>+<<<]>]<<]>[-<+>]>>>[-]>[-<<<<+>>>>]<<<<>>>>++++++++++<<<<[->+>>+>-[<-]<[->>+<<<<[->>>+<<<]>]<<]>[-<+>]>>>[-]>[-<<<<+>>>>]<<<<[->+<]<[->+<]<[->+<]>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]<++++++++++++++++++++++++++++++++++++++++++++++++.[-]<++++++++++++++++++++++++++++++++++++++++++++++++.[-]<+>>>]<[++++++++++++++++++++++++++++++++++++++++++++++++.[-]<++++++++++++++++++++++++++++++++++++++++++++++++.[-]<+>>]<[++++++++++++++++++++++++++++++++++++++++++++++++.[-]<+>]<>+<[>-<-]>[+++++++++++++++++++++++++++++++++++++++++++++++.[-]]<";
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

void multiplication(){
    ans += "[->>+>+<<<]>[->[-<<+>>]>[->+<]>[-<+<+>>]<<<]>[-]>[-]<<<";
}

void division(){
    ans += ">[->>>+<<<]<[->+>>+>-[<-]<[->>+<<<<[->>>+<<<]>]<<]>[-<+>]>>>[-]>[-<<<<+>>>>]<<<<";
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
    //clear_block();
    copy_segment(4);
    go_right(1);
    copy_single(2 * BLOCK_SIZE - 1);
    go_right(1);
    copy_single(3 * BLOCK_SIZE - 2);
    go_right(1);
    copy_single(4 * BLOCK_SIZE - 3);
    go_right(1);
    copy_single(5 * BLOCK_SIZE - 4);
    go_left(4);
    //clear_block();
    next_block();
    read();
    //clear_block();
    copy_segment(4);
    go_right(1);
    copy_single(1 * BLOCK_SIZE - 0);
    go_right(1);
    copy_single(2 * BLOCK_SIZE - 1);
    go_right(1);
    copy_single(3 * BLOCK_SIZE - 2);
    go_right(1);
    copy_single(4 * BLOCK_SIZE - 3);
    go_left(4);
    //clear_block();
    next_block();
    addition(1);
    ans += ">";
    print();
    ans += "<";
    single_addition(' ');
    ans.push_back('.');
    single_substraction(' ');
    next_block();
    go_right(1);
    substraction(-1);
    go_left(1);
    print();
    single_addition(' ');
    ans.push_back('.');
    single_substraction(' ');
    next_block();
    multiplication();
    print();
    single_addition(' ');
    ans.push_back('.');
    single_substraction(' ');
    next_block();
    division();
    print();
    single_addition(' ');
    ans.push_back('.');
    single_substraction(' ');
    ans += "<";
    print();
}

string optimize(string prog) {
    map<string, string> m = {{"+-", ""},
                             {"-+", ""},
                             {"><", ""},
                             {"<>", ""},
                             {"+[-]", "[-]"},
                             {"-[-]", "[-]"}};
    bool f2 = true;
    while (f2) {
        f2 = 0;
        string p1 = "";
        for (int j = 0; j < prog.size(); ++j) {
            bool flag = false;
            for (auto u: m) {
                if (j + u.first.size() > prog.size()) {
                    continue;
                }
                if (prog.substr(j, u.first.size()) == u.first) {
                    p1 += u.second;
                    j += u.first.size() - 1;
                    flag = true;
                    f2 = 1;
                    break;
                }
            }
            if (!flag) {
                p1 += prog[j];
            }
        }
        prog = p1;
    }
    return prog;
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
    ans = optimize(ans);
    cout << ans;
    return 0;
}