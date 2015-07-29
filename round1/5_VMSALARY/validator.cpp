#include "lib/testlib.h"

int main() {
    registerValidation();
    int n = inf.readInt(1, 100000);
    inf.readEoln();
    for(int i = 0; i < n; ++i) {
        if (i > 0) {
            int father = inf.readInt(1, i);
            inf.readSpace();
        }
        int c = inf.readInt(1, 1e9);
        inf.readEoln();
    }
    inf.readEof();
}
