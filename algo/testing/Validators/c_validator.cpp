#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{1,100000}");
    inf.readEoln();
    inf.readEof();

    return 0;
}

