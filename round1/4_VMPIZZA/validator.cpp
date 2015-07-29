#include "lib/testlib.h"

int main() {
    registerValidation();
    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int b = inf.readInt(1, 100000, "B");
    inf.readEoln();
    for(int i = 0; i < n; ++i) {
        int t = inf.readInt(1, 100000);
        inf.readSpace();
        int a = inf.readInt(1, 100000);
        inf.readSpace();
        int b = inf.readInt(1, 100000);
        inf.readEoln();
    }
    inf.readEof();
}
