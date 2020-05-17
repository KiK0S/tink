#include "testlib.h"
#include <iostream>

using namespace std;

const int N = 100000;
const int C = 1000000000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s = 0;
    int n = inf.readInt(1, N, "n");
    inf.readEoln();
    bool ok = false;
    for (int i = 0; i < n; i++) {
        int k = inf.readInt(0, N, "k");
        ok |= (k >= 2);
        s += k;
        ensuref(s <= N, "Sum should be less than %d", N);
        if (k != 0) {
            inf.readSpace();
        }
        for (int j = 0; j < k; j++) {
            inf.readInt(-C, C, "a");
            if (j != k - 1) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }
    inf.readEof();
    ensuref(s >= 1, "Sum should be >= 1!");
    ensuref(ok, "There should be l_i >= 2!");

    return 0;
}

