#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <deque>
#include <ctime>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

string read() {
    //return ",,";
	return ">>+[>,>>++++++++++[-<<->>]<<<->[<+>>>]>>+<<<<[-------------------------------------->>]>>[-<<]<[->++++++++++<]>[-<+>]<<[->+<]<]>>>>[-<<<<+>>>>]<<[-]>>>-<<<<<";
}

string print() {
    //return ".";
	return ">>>>++++++++++<<<<[->+>>+>-[<-]<[->>+<<<<[->>>+<<<]>]<<]>[-<+>]>>>[-]>[-<<<<+>>>>]<<<<>>>>++++++++++<<<<[->+>>+>-[<-]<[->>+<<<<[->>>+<<<]>]<<]>[-<+>]>>>[-]>[-<<<<+>>>>]<<<<[->+<]<[->+<]<[->+<]>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]<++++++++++++++++++++++++++++++++++++++++++++++++.[-]<++++++++++++++++++++++++++++++++++++++++++++++++.[-]<+>>>]<[++++++++++++++++++++++++++++++++++++++++++++++++.[-]<++++++++++++++++++++++++++++++++++++++++++++++++.[-]<+>>]<[++++++++++++++++++++++++++++++++++++++++++++++++.[-]<+>]<>+<[>-<-]>[+++++++++++++++++++++++++++++++++++++++++++++++.[-]]<";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string ans = read();
    ans += "[->>[>]";
    ans += read();
    ans += "[<]<]>>[>]+[<[-<]>[>]>[<-[[>]>]<<[->+>+<<]>[-<+>]>";
    ans += print();
    ans += "[-]>++++++++++++++++++++++++++++++++.--------------------------------<]<<+]";
    //ofstream cout("jija.txt");
    cout << ans;

    return 0;
}
/*
4
1 2
3 4
4 3
2 1
*/