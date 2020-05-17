#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();
    for (int i = 0; i < n; i++) {
    	inf.readToken("-?[1-9][0-9]*");
    	inf.readEoln();
    }
    inf.readEof();
}

